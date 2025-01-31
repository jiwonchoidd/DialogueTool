#include "DD_DialogueEditorSummoner.h"

#include "DD_Dialogue/Dialogue/DD_DialogueData.h"
#include "DD_DialogueEditor/Editor/DD_Define.h"
#include "DD_DialogueEditor/Editor/DD_DialogueGraphEditor.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

#define LOCTEXT_NAMESPACE "FDD_DialogueEditor"

FDD_DialogueEditorSummoner::FDD_DialogueEditorSummoner(const TSharedPtr<FDD_DialogueGraphEditor>& _DialogueEditor,
                                                       const FOnCreateGraphEditorWidget& _CreateCallback) :
	FDocumentTabFactoryForObjects<UEdGraph>(FDialogueEditorTabs::GraphEditorID, _DialogueEditor)
	, DialogueEditorPtr(_DialogueEditor)
	, OnCreateGraphEditorWidget(_CreateCallback)
{
}

void FDD_DialogueEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(DialogueEditorPtr.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	//DialogueEditorPtr.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FDD_DialogueEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TSharedRef<SWidget> FDD_DialogueEditorSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return FDocumentTabFactoryForObjects<UEdGraph>::CreateTabBody(Info);
}

TAttribute<FText> FDD_DialogueEditorSummoner::ConstructTabNameForObject(UEdGraph* Graph) const
{
	return TAttribute<FText>(FText::FromString(Graph->GetName()));
}

TSharedRef<SWidget> FDD_DialogueEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FDD_DialogueEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return FAppStyle::GetBrush("NoBrush");
}

void FDD_DialogueEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{
	check(DialogueEditorPtr.IsValid());
	check(DialogueEditorPtr.Pin()->GetGraphData());

	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());

	FVector2D ViewLocation;
	float ZoomAmount;
	GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);

	UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	DialogueEditorPtr.Pin()->GetGraphData()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}

bool FDD_DialogueEditorSummoner::SupportsObjectType(UObject* DocumentID) const
{
	return FDocumentTabFactoryForObjects<UEdGraph>::SupportsObjectType(DocumentID);
}

#undef LOCTEXT_NAMESPACE
