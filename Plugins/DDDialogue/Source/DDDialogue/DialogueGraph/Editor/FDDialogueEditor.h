
#pragma once
#include "Misc/NotifyHook.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
/**
 * 
 */
class FDDialogueEditor : public FWorkflowCentricApplication, public FNotifyHook
{
public:
	FDDialogueEditor();
	virtual ~FDDialogueEditor() override;
	
	void OpenDialogueEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost>& EditWithinLevelEditor);
	class UDDDialogueDataAsset* GetDialogueGraphObj() const;

private:
	virtual FName GetToolkitFName() const override { return FName("DDDialogueEditor"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("DD Dialogue Editor"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DDDialogueEditor"); }
private:
	/** Input Events */
	void OnSelectedNodesChanged(const FGraphPanelSelectionSet& _SelectionSet);
	void OnNodeDoubleClicked(class UEdGraphNode* _GraphNode);
	void OnNodeTitleCommitted(const FText& _Text, ETextCommit::Type _Type, UEdGraphNode* _GraphNode);
private:
	/** Create widget for graph editing */
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
private:
	FGraphAppearanceInfo GetGraphAppearance() const;
	bool InEditingMode(bool bGraphIsEditable) const;
private:
	class UDDDialogueDataAsset* DataAsset = nullptr;
};

