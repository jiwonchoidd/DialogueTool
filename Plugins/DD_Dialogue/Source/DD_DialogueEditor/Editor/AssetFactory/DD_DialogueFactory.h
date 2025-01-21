// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DD_DialogueFactory.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUEEDITOR_API UDD_DialogueFactory : public UFactory
{
	GENERATED_BODY()

protected:
	UDD_DialogueFactory();
private:
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual FText GetDisplayName() const override;
	virtual FText GetToolTip() const override;
};

