// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "DDDialogueFactory.generated.h"

/**
 * 
 */
UCLASS()
class DDDIALOGUE_API UDDDialogueFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDDDialogueFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};


class FDDDialogue_AssetTypeActions : public FAssetTypeActions_Base
{
public:
	virtual uint32 GetCategories() override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
};
