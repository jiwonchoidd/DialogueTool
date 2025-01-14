// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DDDialogueGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DDDIALOGUE_API UDDDialogueGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
