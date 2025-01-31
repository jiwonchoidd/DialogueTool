// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_DialogueGraph.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUE_API UDD_DialogueGraph : public UEdGraph
{
	GENERATED_BODY()
	class UDD_DialogueData* GetDialogueData() const;
};
