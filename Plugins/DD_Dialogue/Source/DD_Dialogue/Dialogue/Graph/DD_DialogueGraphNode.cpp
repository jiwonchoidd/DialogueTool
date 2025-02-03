// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraphNode.h"

#include "DD_DialogueGraphSchema.h"

void UDD_DialogueGraphNode_Base::AllocateDefaultPins()
{
	check(Pins.Num() == 0);

	CreatePin(EGPD_Output, TEXT("DialogueNode"), TEXT("Output"));
}

void UDD_DialogueGraphNode_Base::ReconstructNode()
{
	for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
	{
		UEdGraphPin* Pin = Pins[PinIndex];
		TArray<class UEdGraphPin*>& LinkedToRef = Pin->LinkedTo;
		for (int32 LinkIdx = 0; LinkIdx < LinkedToRef.Num(); LinkIdx++)
		{
			UEdGraphPin* OtherPin = LinkedToRef[LinkIdx];
			if (!OtherPin->GetOwningNode()->Pins.Contains(OtherPin))
			{
				Pin->LinkedTo.Remove(OtherPin);
			}
		}
	}

	TArray<UEdGraphPin*> OldPins(Pins);
	Pins.Reset();

	AllocateDefaultPins();

	TArray<UEdGraphPin*> NewPins(Pins);


	for (int32 PinIndex = 0; PinIndex < OldPins.Num(); PinIndex++)
	{
		if (PinIndex < NewPins.Num())
		{
			NewPins[PinIndex]->MovePersistentDataFromOldPin(*OldPins[PinIndex]);
		}
	}

	for (UEdGraphPin* OldPin : OldPins)
	{
		OldPin->Modify();
		UEdGraphNode::DestroyPin(OldPin);
	}
}

void UDD_DialogueGraphNode_Base::AutowireNewNode(UEdGraphPin* FromPin)
{
	if (FromPin != NULL)
	{
		const UDD_DialogueGraphSchema* Schema = CastChecked<UDD_DialogueGraphSchema>(GetSchema());

		TSet<UEdGraphNode*> NodeList;

		// auto-connect from dragged pin to first compatible pin on the new node
		for (int32 i = 0; i < Pins.Num(); i++)
		{
			UEdGraphPin* Pin = Pins[i];
			check(Pin);
			FPinConnectionResponse Response = Schema->CanCreateConnection(FromPin, Pin);
			if (ECanCreateConnectionResponse::CONNECT_RESPONSE_MAKE == Response.Response) //-V1051
			{
				if (Schema->TryCreateConnection(FromPin, Pin))
				{
					NodeList.Add(FromPin->GetOwningNode());
					NodeList.Add(this);
				}
				break;
			}
			else if (ECanCreateConnectionResponse::CONNECT_RESPONSE_BREAK_OTHERS_A == Response.Response)
			{
				//InsertNewNode(FromPin, Pin, NodeList);
				break;
			}
		}

		// Send all nodes that received a new pin connection a notification
		for (auto It = NodeList.CreateConstIterator(); It; ++It)
		{
			UEdGraphNode* Node = (*It);
			Node->NodeConnectionListChanged();
		}
	}
}

bool UDD_DialogueGraphNode_Base::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const
{
	return Schema->IsA(UDD_DialogueGraphSchema::StaticClass());
}

FString UDD_DialogueGraphNode_Base::GetDocumentationLink() const
{
	return Super::GetDocumentationLink();
}

//-----------------------------------------------------------------

void UDD_TalkGraphNode::AllocateDefaultPins()
{
	check(Pins.Num() == 0);

	CreatePin(EGPD_Input, TEXT("DialogueNode"), TEXT("Input"));
	CreatePin(EGPD_Output, TEXT("DialogueNode"), TEXT("Output"));
}

//-----------------------------------------------------------------
