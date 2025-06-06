// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraph.h"

#include "DD_Dialogue/Dialogue/DD_DialogueData.h"
#include "Node/DD_TalkNode.h"

void UDD_DialogueGraph::GetDialogueInfo(TArray<FString>& _Test) const
{
	_Test.Empty();
	for (UEdGraphNode* Node : Nodes)
	{
		if (!Node)
		{
			continue;
		}

		FString NodeTitle = Node->GetNodeTitle(ENodeTitleType::FullTitle).ToString();
		UE_LOG(LogTemp, Log, TEXT("Node: %s"), *NodeTitle);

		for (UEdGraphPin* Pin : Node->Pins)
		{
			FString PinName = Pin->GetName();
			UE_LOG(LogTemp, Log, TEXT("  Pin: %s"), *PinName);
		}

		if (UDD_TalkNode* TalkNode = Cast<UDD_TalkNode>(Node))
		{
			_Test.Add(TalkNode->DialogueText);
		}
	}
}
