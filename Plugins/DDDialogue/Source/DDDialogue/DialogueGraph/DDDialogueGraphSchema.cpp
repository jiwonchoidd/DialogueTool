// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueGraphSchema.h"

void UDDDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	Super::CreateDefaultNodesForGraph(Graph);
}

void UDDDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
}

void UDDDialogueGraphSchema::GetContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UDDDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A,
                                                                         const UEdGraphPin* B) const
{
	return Super::CanCreateConnection(A, B);
}

const FPinConnectionResponse UDDDialogueGraphSchema::CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const
{
	return Super::CanMergeNodes(A, B);
}

FLinearColor UDDDialogueGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return Super::GetPinTypeColor(PinType);
}

int32 UDDDialogueGraphSchema::GetNodeSelectionCount(const UEdGraph* Graph) const
{
	return Super::GetNodeSelectionCount(Graph);
}

bool UDDDialogueGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return Super::IsCacheVisualizationOutOfDate(InVisualizationCacheID);
}

int32 UDDDialogueGraphSchema::GetCurrentVisualizationCacheID() const
{
	return Super::GetCurrentVisualizationCacheID();
}

void UDDDialogueGraphSchema::ForceVisualizationCacheClear() const
{
	Super::ForceVisualizationCacheClear();
}

TSharedPtr<FEdGraphSchemaAction> UDDDialogueGraphSchema::GetCreateCommentAction() const
{
	return Super::GetCreateCommentAction();
}
