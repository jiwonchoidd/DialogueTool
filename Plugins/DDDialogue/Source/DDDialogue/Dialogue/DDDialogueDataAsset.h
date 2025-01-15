// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DDDialogueDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DDDIALOGUE_API UDDDialogueDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "TestValue")
	TArray<UDDDialogueDataAsset*> Children;
	
};
