// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueGraphSchema.h"

void UDDDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
}

const FPinConnectionResponse UDDDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	return Super::CanCreateConnection(A, B);
}
