#include "FDDialogueGraphEditorSummoner.h"

#include "FDDialogueEditor.h"


FDDialogueGraphEditorSummoner::FDDialogueGraphEditorSummoner(const TSharedPtr<FDDialogueEditor>& InToolkit,
                                                             const FOnCreateGraphEditorWidget& _CreateCallback) :
	FDocumentTabFactoryForObjects<UEdGraph>(TEXT("DDialogueGraph"), InToolkit->AsShared())
, DialogueEditorPtr(InToolkit)
, OnCreateGraphEditorWidget(_CreateCallback)
{
	
}

void FDDialogueGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	FDocumentTabFactoryForObjects<UEdGraph>::OnTabActivated(Tab);
}

void FDDialogueGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	FDocumentTabFactoryForObjects<UEdGraph>::OnTabRefreshed(Tab);
}

TAttribute<FText> FDDialogueGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* Graph) const
{
	return FText::FromString(Graph->GetName());
}

TSharedRef<SWidget> FDDialogueGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FDDialogueGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return FAppStyle::GetBrush("NoBrush");
}

void FDDialogueGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{
	check(DialogueEditorPtr.IsValid());
	check(DialogueEditorPtr.Pin()->GetDialogueGraphObj());

	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());

	FVector2D ViewLocation;
	float ZoomAmount;
	GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);

	UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	//DialogueEditorPtr.Pin()->GetDialogueGraphObj()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}
