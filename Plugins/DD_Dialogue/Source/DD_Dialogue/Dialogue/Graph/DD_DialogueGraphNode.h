// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DD_DialogueGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUE_API UDD_DialogueGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
