#pragma once
#include "WorkflowOrientedApp/WorkflowUObjectDocuments.h"
#include "EdGraph/EdGraph.h"

struct FDD_DialogueGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>
{
public:
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);
public:
	FDD_DialogueGraphEditorSummoner(const TSharedPtr<class FDD_DialogueGraphEditor>& _EditorPtr, const FOnCreateGraphEditorWidget& CreateGraphEditorWidgetCallback);

	virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;
	virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;
	
private:
	virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* Graph) const override;
	virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;
	virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;

	virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;
	virtual bool SupportsObjectType(UObject* DocumentID) const override;
private:
	TWeakPtr<class FDD_DialogueGraphEditor> DialogueEditorPtr = nullptr;
	FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;
};
