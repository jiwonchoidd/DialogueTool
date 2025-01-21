#include "DD_DialogueGraphEditorSummoner.h"

#include "DD_DialogueGraphEditor.h"


FDD_DialogueGraphEditorSummoner::FDD_DialogueGraphEditorSummoner(const TSharedPtr<FDD_DialogueGraphEditor>& InToolkit,
                                                                 const FOnCreateGraphEditorWidget& _CreateCallback) :
	FDocumentTabFactoryForObjects<UEdGraph>(TEXT("DD_DialogueGraph"), InToolkit->AsShared())
, DialogueEditorPtr(InToolkit)
, OnCreateGraphEditorWidget(_CreateCallback)
{
	
}

void FDD_DialogueGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	FDocumentTabFactoryForObjects<UEdGraph>::OnTabActivated(Tab);
}

void FDD_DialogueGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	FDocumentTabFactoryForObjects<UEdGraph>::OnTabRefreshed(Tab);
}

TAttribute<FText> FDD_DialogueGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* Graph) const
{
	return TAttribute<FText>(FText::FromString(Graph->GetName()));
}

TSharedRef<SWidget> FDD_DialogueGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FDD_DialogueGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info,
	UEdGraph* DocumentID) const
{
	return FAppStyle::GetBrush("NoBrush");
}

void FDD_DialogueGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
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

bool FDD_DialogueGraphEditorSummoner::SupportsObjectType(UObject* DocumentID) const
{
	return FDocumentTabFactoryForObjects<UEdGraph>::SupportsObjectType(DocumentID);
}
