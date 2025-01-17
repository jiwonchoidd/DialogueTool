#include "FDDialogueEditor.h"

#include "FDDialogueEditorStyle.h"
#include "FDDialogueGraphEditorSummoner.h"
#include "DDDialogue/DDDialogue.h"
#include "DDDialogue/Dialogue/DDDialogueData.h"
#include "DDDialogue/Dialogue/Graph/DDDialogueGraph.h"
#include "DDDialogue/Dialogue/Graph/DDDialogueGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

const FName AppIdentifier("DDDialogueEditorApp");

#define LOCTEXT_NAMESPACE "FDDialogueEditor"

FDDialogueEditor::FDDialogueEditor()
{
}

FDDialogueEditor::~FDDialogueEditor()
{
	if(DocumentTracker)
	{
		delete DocumentTracker;
		DocumentTracker = nullptr;
	}
}

void FDDialogueEditor::Initialize()
{
	if(DocumentTracker == nullptr)
	{
		DocumentTracker = new FDocumentTracker();
		TSharedPtr<FDDialogueEditor> ThisPtr(SharedThis(this));
		DocumentTracker->Initialize(ThisPtr);
		TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FDDialogueGraphEditorSummoner(ThisPtr,
			FDDialogueGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &FDDialogueEditor::CreateGraphEditorWidget)
		));
		DocumentTracker->RegisterDocumentFactory(GraphEditorFactory);	
	}
}

void FDDialogueEditor::OpenDialogueEditor(const TArray<UObject*>& InObjects,
                                          const TSharedPtr<IToolkitHost>& EditWithinLevelEditor)
{
	DialogueData = Cast<UDDDialogueData>(InObjects[0]);

	if (!IsValid(DialogueData))
	{
		UE_LOG(DDDialogue, Warning, TEXT("FDDialogueEditor::OpenDialogueEditor Graph Object is Null.."));
		return;
	}

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(DialogueData);

	const bool bNewGraph = DialogueData->TestGraph == nullptr;
	if(bNewGraph)
	{
		UEdGraph* pNewGraph = FBlueprintEditorUtils::CreateNewGraph(DialogueData, TEXT("Test111"), UDDDialogueGraph::StaticClass(), UDDDialogueGraphSchema::StaticClass());
		const UEdGraphSchema* Schema = pNewGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*pNewGraph);
		DialogueData->TestGraph = pNewGraph;
	}
	
	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(DialogueData->TestGraph);

	if(DocumentTracker != nullptr)
	{
		TSharedPtr<SDockTab> DocumentTab = DocumentTracker->OpenDocument(Payload, bNewGraph ? FDocumentTracker::OpenNewDocument : FDocumentTracker::RestorePreviousDocument);
	}
		
	/*const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(
		FTabManager::NewPrimaryArea());
	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;
	InitAssetEditor(EToolkitMode::Standalone, EditWithinLevelEditor, AppIdentifier, DummyLayout,
	                bCreateDefaultStandaloneMenu,
	                bCreateDefaultToolbar, ObjectsToEdit);*/
}

//-------------------------------------------------------------------------------------

class UDDDialogueData* FDDialogueEditor::GetDialogueGraphObj() const
{
	return GetEditingObjects().Num() == 1 ? Cast<UDDDialogueData>(GetEditingObjects()[0]) : nullptr;
}

//-------------------------------------------------------------------------------------

const FSlateBrush* FDDialogueEditor::GetDefaultTabIcon() const
{
	return FDDialogueEditorStyle::Get().GetBrush(StyleNamespace::Icon16);
}

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
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(
		this, &FDDialogueEditor::OnSelectedNodesChanged);
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
				.Text(LOCTEXT("TitleBar", "TEST Title"))
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
	// Temp Appearance..
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("EditorUtilityAppearanceCornerText", "EDITOR UTILITY");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_DefaultGraph", "Drag Off Pins to Create/Connect New Nodes.");
	return AppearanceInfo;
}

bool FDDialogueEditor::InEditingMode(bool bGraphIsEditable) const
{
	const bool bPlayWorld = !GEditor->bIsSimulatingInEditor && (GEditor->PlayWorld == NULL);
	return bGraphIsEditable && bPlayWorld;
}

#undef LOCTEXT_NAMESPACE