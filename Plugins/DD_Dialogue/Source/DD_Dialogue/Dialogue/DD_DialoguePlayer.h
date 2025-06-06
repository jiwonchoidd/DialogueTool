// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_DialoguePlayer.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUE_API UDD_DialoguePlayer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static void PlayDialogue(class UDD_DialogueData* _Data);
};
