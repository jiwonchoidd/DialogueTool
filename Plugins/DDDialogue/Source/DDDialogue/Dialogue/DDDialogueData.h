// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DDDialogueData.generated.h"

/**
 * 
 */
UCLASS()
class DDDIALOGUE_API UDDDialogueData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "TestValue")
	class UEdGraph*	TestGraph;
};
