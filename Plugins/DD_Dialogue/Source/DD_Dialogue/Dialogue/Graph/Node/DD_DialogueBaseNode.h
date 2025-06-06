﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DD_DialogueBaseNode.generated.h"

/**
 * 
 */
UCLASS(Hidden)
class DD_DIALOGUE_API UDD_DialogueBaseNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual void ReconstructNode() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;
	virtual FString GetDocumentationLink() const override;
	// End of UEdGraphNode interface.
};

//----------------------------------------------------------------------------------------

