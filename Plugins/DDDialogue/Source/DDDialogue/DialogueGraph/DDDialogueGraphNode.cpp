// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueGraphNode.h"

void UDDDialogueGraphNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

FText UDDDialogueGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}
