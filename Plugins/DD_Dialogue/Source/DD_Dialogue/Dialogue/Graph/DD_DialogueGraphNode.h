// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DD_DialogueGraphNode.generated.h"

/**
 * 
 */
UCLASS(Hidden)
class DD_DIALOGUE_API UDD_DialogueGraphNode_Base : public UEdGraphNode
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

UCLASS()
class DD_DIALOGUE_API UDD_TalkGraphNode : public UDD_DialogueGraphNode_Base
{
	GENERATED_BODY()
	
public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	// End of UEdGraphNode interface.
};
