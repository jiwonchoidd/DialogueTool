// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TObjectPtr<class UDD_DialogueGraph>	Graph;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TArray<FEditedDocumentInfo> LastEditedDocuments;
#endif
};
