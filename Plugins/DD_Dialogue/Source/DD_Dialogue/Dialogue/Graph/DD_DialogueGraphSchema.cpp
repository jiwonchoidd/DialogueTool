// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_DialogueGraphSchema.h"

void UDD_DialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	Super::CreateDefaultNodesForGraph(Graph);
}

void UDD_DialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
}

void UDD_DialogueGraphSchema::GetContextMenuActions(class UToolMenu* Menu,
	class UGraphNodeContextMenuContext* Context) const
{
	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UDD_DialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A,
                                                                         const UEdGraphPin* B) const
{
	return Super::CanCreateConnection(A, B);
}

const FPinConnectionResponse UDD_DialogueGraphSchema::CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const
{
	return Super::CanMergeNodes(A, B);
}

FLinearColor UDD_DialogueGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return Super::GetPinTypeColor(PinType);
}

int32 UDD_DialogueGraphSchema::GetNodeSelectionCount(const UEdGraph* Graph) const
{
	return Super::GetNodeSelectionCount(Graph);
}

bool UDD_DialogueGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return Super::IsCacheVisualizationOutOfDate(InVisualizationCacheID);
}

int32 UDD_DialogueGraphSchema::GetCurrentVisualizationCacheID() const
{
	return Super::GetCurrentVisualizationCacheID();
}

void UDD_DialogueGraphSchema::ForceVisualizationCacheClear() const
{
	Super::ForceVisualizationCacheClear();
}

TSharedPtr<FEdGraphSchemaAction> UDD_DialogueGraphSchema::GetCreateCommentAction() const
{
	return Super::GetCreateCommentAction();
}
