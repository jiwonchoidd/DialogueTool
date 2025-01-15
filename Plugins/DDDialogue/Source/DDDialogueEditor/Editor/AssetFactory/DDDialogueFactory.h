// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DDDialogueFactory.generated.h"

/**
 * 
 */
UCLASS()
class DDDIALOGUEEDITOR_API UDDDialogueFactory : public UFactory
{
	GENERATED_BODY()

protected:
	UDDDialogueFactory();
private:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
	virtual FText GetToolTip() const override;
};

