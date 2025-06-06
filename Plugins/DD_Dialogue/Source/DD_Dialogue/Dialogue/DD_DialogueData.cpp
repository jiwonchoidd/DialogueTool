// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueData.h"

#include "Graph/DD_DialogueGraph.h"

TArray<FString> UDD_DialogueData::GetDialogueInfo() const
{
	TArray<FString> Test;
	if(Graph)
	{
		Graph->GetDialogueInfo(Test);
	}
	return Test;
}
