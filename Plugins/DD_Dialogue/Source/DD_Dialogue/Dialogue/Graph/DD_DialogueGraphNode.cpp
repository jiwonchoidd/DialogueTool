// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraphNode.h"

void UDD_DialogueGraphNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

FText UDD_DialogueGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}
