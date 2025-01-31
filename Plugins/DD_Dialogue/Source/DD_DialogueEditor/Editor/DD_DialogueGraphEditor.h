
#pragma once
#include "Misc/NotifyHook.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
/**
 * 
 */

class FDocumentTracker;

class DD_DIALOGUEEDITOR_API FDD_DialogueGraphEditor : public FWorkflowCentricApplication, public FNotifyHook
{
public:
	FDD_DialogueGraphEditor();
	virtual ~FDD_DialogueGraphEditor() override;
public:
	void InitDialogueEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost>& EditWithinLevelEditor);
public:
	TSharedRef<SWidget> SpawnEditor() const;
public:
	class UDD_DialogueData*		  GetGraphData() const;
private:
	virtual FName GetToolkitFName() const override { return FName("DD_DialogueEditor"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("DD Dialogue Editor"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor::White; }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DD_DialogueEditor"); }
	virtual const FSlateBrush* GetDefaultTabIcon() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& _TabManager) override;
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
	void CommonInitialization();
	void OpenInternalWidget();
private:
	TSharedRef<SDockTab> SpawnPropertiesTab( const FSpawnTabArgs& _Args) const;
	TSharedRef<SDockTab> SpawnGraphTab( const FSpawnTabArgs& _Args) const;
private:
	class UDD_DialogueData*		DialogueData = nullptr;
	
	TSharedPtr< class IDetailsView > DetailsView;
	TSharedPtr<class SGraphEditor>   GraphEditor;
};