// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraphSchema.h"

#include "DD_DialogueGraphNode.h"

#define LOCTEXT_NAMESPACE "DialogueGraphSchema"

void UDD_DialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	const int32 RootNodeHeightOffset = -58;

	// TODO : 임시
	FGraphNodeCreator<UDD_DialogueGraphNode_Base> NodeCreator(Graph);
	UDD_DialogueGraphNode_Base* ResultRootNode = NodeCreator.CreateNode();
	ResultRootNode->NodePosY = RootNodeHeightOffset;
	NodeCreator.Finalize();
	SetNodeMetaData(ResultRootNode, FNodeMetadata::DefaultGraphNode);
}

void UDD_DialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	/*GetAllSoundNodeActions(ContextMenuBuilder, true);

	GetCommentAction(ContextMenuBuilder, ContextMenuBuilder.CurrentGraph);

	if (!ContextMenuBuilder.FromPin && FSoundCueEditorUtilities::CanPasteNodes(ContextMenuBuilder.CurrentGraph))
	{
		TSharedPtr<FSoundCueGraphSchemaAction_Paste> NewAction( new FSoundCueGraphSchemaAction_Paste(FText::GetEmpty(), LOCTEXT("PasteHereAction", "Paste here"), FText::GetEmpty(), 0) );
		ContextMenuBuilder.AddAction( NewAction );
	}*/
}

void UDD_DialogueGraphSchema::GetContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	/*if (Context->Node)
	{
		const USoundCueGraphNode* SoundGraphNode = Cast<const USoundCueGraphNode>(Context->Node);
		{
			FToolMenuSection& Section = Menu->AddSection("SoundCueGraphSchemaNodeActions", LOCTEXT("NodeActionsMenuHeader", "Node Actions"));
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
		}
	}*/

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UDD_DialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A,const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionSameNode", "Both are on the same node"));
	}

	// Compare the directions
	const UEdGraphPin* InputPin = NULL;
	const UEdGraphPin* OutputPin = NULL;

	if (!CategorizePinsByDirection(A, B, /*out*/ InputPin, /*out*/ OutputPin))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionIncompatible", "Directions are not compatible"));
	}

	/*if (ConnectionCausesLoop(InputPin, OutputPin))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionLoop", "Connection would cause loop"));
	}*/

	// Break existing connections on inputs only - multiple output connections are acceptable
	if (InputPin->LinkedTo.Num() > 0)
	{
		ECanCreateConnectionResponse ReplyBreakOutputs;
		if (InputPin == A)
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_A;
		}
		else
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_B;
		}
		return FPinConnectionResponse(ReplyBreakOutputs, LOCTEXT("ConnectionReplace", "Replace existing connections"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UDD_DialogueGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	bool bModified = UEdGraphSchema::TryCreateConnection(A, B);

	return bModified;
}

bool UDD_DialogueGraphSchema::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const
{
	return true;
}

FLinearColor UDD_DialogueGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White;
}

void UDD_DialogueGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	Super::BreakNodeLinks(TargetNode);
}

void UDD_DialogueGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UDD_DialogueGraphSchema::GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph,
	FString& OutTooltipText, bool& OutOkIcon) const
{
	Super::GetAssetsGraphHoverMessage(Assets, HoverGraph, OutTooltipText, OutOkIcon);
}

void UDD_DialogueGraphSchema::DroppedAssetsOnGraph(const TArray<struct FAssetData>& Assets,
	const FVector2D& GraphPosition, UEdGraph* Graph) const
{
	Super::DroppedAssetsOnGraph(Assets, GraphPosition, Graph);
}

void UDD_DialogueGraphSchema::DroppedAssetsOnNode(const TArray<FAssetData>& Assets, const FVector2D& GraphPosition,
	UEdGraphNode* Node) const
{
	Super::DroppedAssetsOnNode(Assets, GraphPosition, Node);
}

int32 UDD_DialogueGraphSchema::GetNodeSelectionCount(const UEdGraph* Graph) const
{
	return Super::GetNodeSelectionCount(Graph);
}

TSharedPtr<FEdGraphSchemaAction> UDD_DialogueGraphSchema::GetCreateCommentAction() const
{
	return Super::GetCreateCommentAction();
}

#undef LOCTEXT_NAMESPACE