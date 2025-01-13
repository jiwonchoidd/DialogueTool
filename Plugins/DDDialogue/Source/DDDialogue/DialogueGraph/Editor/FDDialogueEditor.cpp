#include "FDDialogueEditor.h"

#include "FDDialogueGraphEditorSummoner.h"
#include "DDDialogue/DDDialogue.h"
#include "DDDialogue/AssetFactory/DDDialogueDataAsset.h"

const FName AppIdentifier("DDDialogueEditorApp");

FDDialogueEditor::FDDialogueEditor()
{
}

FDDialogueEditor::~FDDialogueEditor()
{
}

void FDDialogueEditor::OpenDialogueEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost>& EditWithinLevelEditor)
{
	DataAsset = Cast<UDDDialogueDataAsset>(InObjects[0]);

	if (!IsValid(DataAsset))
	{
		UE_LOG(DDDialogue, Warning, TEXT("FDDialogueEditor::OpenDialogueEditor Graph Object is Null.."));
		return;
	}

	TSharedPtr<FDDialogueEditor> ThisPtr(SharedThis(this));
	TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FDDialogueGraphEditorSummoner(ThisPtr,
		FDDialogueGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(
			this, &FDDialogueEditor::CreateGraphEditorWidget)
	));

	const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(
		FTabManager::NewPrimaryArea());
	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(DataAsset);

	InitAssetEditor(EToolkitMode::Standalone, EditWithinLevelEditor, AppIdentifier, DummyLayout,
	                bCreateDefaultStandaloneMenu,
	                bCreateDefaultToolbar, ObjectsToEdit);
}

//-------------------------------------------------------------------------------------

class UDDDialogueDataAsset* FDDialogueEditor::GetDialogueGraphObj() const
{
	return GetEditingObjects().Num() == 1 ? Cast<UDDDialogueDataAsset>(GetEditingObjects()[0]) : nullptr;
}

//-------------------------------------------------------------------------------------

void FDDialogueEditor::OnSelectedNodesChanged(const FGraphPanelSelectionSet& _SelectionSet)
{
}
void FDDialogueEditor::OnNodeDoubleClicked(class UEdGraphNode* _GraphNode)
{
}

void FDDialogueEditor::OnNodeTitleCommitted(const FText& _Text, ETextCommit::Type _Type, UEdGraphNode* _GraphNode)
{
}

//-------------------------------------------------------------------------------------

TSharedRef<SGraphEditor> FDDialogueEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);
	
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FDDialogueEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FDDialogueEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FDDialogueEditor::OnNodeTitleCommitted);
	
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.FillWidth(1.f)
		[
			SNew(STextBlock)
			.Text(TEXT("Dialogue Editor"))
		.TextStyle(FAppStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
		]
		];
	
	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
	//.AdditionalCommands(GraphEditorCommands)
	.IsEditable(this, &FDDialogueEditor::InEditingMode, bGraphIsEditable)
	.Appearance(this, &FDDialogueEditor::GetGraphAppearance)
	.TitleBar(TitleBarWidget)
	.GraphToEdit(InGraph)
	.GraphEvents(InEvents);
}

//-------------------------------------------------------------------------------------

FGraphAppearanceInfo FDDialogueEditor::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	//AppearanceInfo.CornerText = FText::FromString("Test");

	/*
	const int32 StepIdx = Debugger.IsValid() ? Debugger->GetShownStateIndex() : 0;
	if (Debugger.IsValid() && !Debugger->IsDebuggerRunning())
	{
		AppearanceInfo.PIENotifyText = LOCTEXT("InactiveLabel", "INACTIVE");
	}
	else if (StepIdx)
	{
		AppearanceInfo.PIENotifyText = FText::Format(LOCTEXT("StepsBackLabelFmt", "STEPS BACK: {0}"), FText::AsNumber(StepIdx));
	}
	else if (FDDialogueEditor::IsPlaySessionPaused())
	{
		AppearanceInfo.PIENotifyText = LOCTEXT("PausedLabel", "PAUSED");
	}
	*/
	
	return AppearanceInfo;
}

bool FDDialogueEditor::InEditingMode(bool bGraphIsEditable) const
{
	return bGraphIsEditable && FDDDialogueModule::IsPIENotSimulating();
}