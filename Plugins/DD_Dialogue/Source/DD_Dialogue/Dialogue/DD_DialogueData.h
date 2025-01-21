// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DD_DialogueData.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUE_API UDD_DialogueData : public UObject
{
	GENERATED_BODY()

public:
	UDD_DialogueData();
public:
	UPROPERTY(EditAnywhere, Category = "TestValue")
	class UEdGraph*	TestGraph;

private:
};
