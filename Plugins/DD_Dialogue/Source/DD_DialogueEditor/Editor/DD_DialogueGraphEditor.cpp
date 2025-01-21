#include "DD_DialogueGraphEditor.h"

#include "DD_DialogueGraphEditorSummoner.h"
#include "AssetFactory/DD_DialogueEditorStyle.h"
#include "DD_Dialogue/DD_Dialogue.h"
#include "DD_Dialogue/Dialogue/DD_DialogueData.h"
#include "DD_Dialogue/Dialogue/Graph/DD_DialogueGraph.h"
#include "DD_Dialogue/Dialogue/Graph/DD_DialogueGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

const FName AppIdentifier("DD_DialogueEditorApp");

#define LOCTEXT_NAMESPACE "FDD_DialogueEditor"

FDD_DialogueGraphEditor::FDD_DialogueGraphEditor()
{
}

FDD_DialogueGraphEditor::~FDD_DialogueGraphEditor()
{
}

void FDD_DialogueGraphEditor::OpenDialogueEditor(const TArray<UObject*>& InObjects,
                                          const TSharedPtr<IToolkitHost>& EditWithinLevelEditor)
{
	DialogueData = Cast<UDD_DialogueData>(InObjects[0]);

	if (!IsValid(DialogueData))
	{
		UE_LOG(DD_Dialogue, Warning, TEXT("DialogueEditor::OpenDialogueEditor Graph Object is Null.."));
		return;
	}

	TSharedPtr<FDD_DialogueGraphEditor> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker);
		DocumentManager->Initialize(ThisPtr);

		{
			TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FDD_DialogueGraphEditorSummoner(ThisPtr,
				FDD_DialogueGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &FDD_DialogueGraphEditor::CreateGraphEditorWidget)
			));

			GraphEditorTabFactoryPtr = GraphEditorFactory;
			DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
		}
	}
	
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(DialogueData);
		
	const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(
		FTabManager::NewPrimaryArea());
	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;
	InitAssetEditor(EToolkitMode::Standalone, EditWithinLevelEditor, AppIdentifier, DummyLayout,
	                bCreateDefaultStandaloneMenu,
	                bCreateDefaultToolbar, ObjectsToEdit);

	
	OpenDocument();
}

//-------------------------------------------------------------------------------------

class UDD_DialogueData* FDD_DialogueGraphEditor::GetDialogueGraphObj() const
{
	return GetEditingObjects().Num() == 1 ? Cast<UDD_DialogueData>(GetEditingObjects()[0]) : nullptr;
}

//-------------------------------------------------------------------------------------

const FSlateBrush* FDD_DialogueGraphEditor::GetDefaultTabIcon() const
{
	return gDialStyle.GetBrush(StyleNamespace::Icon16);
}

void FDD_DialogueGraphEditor::OnSelectedNodesChanged(const FGraphPanelSelectionSet& _SelectionSet)
{
}

void FDD_DialogueGraphEditor::OnNodeDoubleClicked(class UEdGraphNode* _GraphNode)
{
}

void FDD_DialogueGraphEditor::OnNodeTitleCommitted(const FText& _Text, ETextCommit::Type _Type, UEdGraphNode* _GraphNode)
{
}

//-------------------------------------------------------------------------------------

TSharedRef<SGraphEditor> FDD_DialogueGraphEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(
		this, &FDD_DialogueGraphEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FDD_DialogueGraphEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FDD_DialogueGraphEditor::OnNodeTitleCommitted);

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
	                         .IsEditable(this, &FDD_DialogueGraphEditor::InEditingMode, bGraphIsEditable)
	                         .Appearance(this, &FDD_DialogueGraphEditor::GetGraphAppearance)
	                         .TitleBar(TitleBarWidget)
	                         .GraphToEdit(InGraph)
	                         .GraphEvents(InEvents);
}

void FDD_DialogueGraphEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	if(DocumentManager.IsValid())
		DocumentManager->SetTabManager(_TabManager);
	FWorkflowCentricApplication::RegisterTabSpawners(_TabManager);
}

//-------------------------------------------------------------------------------------

FGraphAppearanceInfo FDD_DialogueGraphEditor::GetGraphAppearance() const
{
	// Temp Appearance..
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("EditorUtilityAppearanceCornerText", "EDITOR UTILITY");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_DefaultGraph", "Drag Off Pins to Create/Connect New Nodes.");
	return AppearanceInfo;
}

bool FDD_DialogueGraphEditor::InEditingMode(bool bGraphIsEditable) const
{
	const bool bPlayWorld = !GEditor->bIsSimulatingInEditor && (GEditor->PlayWorld == NULL);
	return bGraphIsEditable && bPlayWorld;
}

void FDD_DialogueGraphEditor::OpenDocument() const
{
	const bool bNewGraph = DialogueData->TestGraph == nullptr;
	if(bNewGraph)
	{
		UEdGraph* pNewGraph = FBlueprintEditorUtils::CreateNewGraph(DialogueData, TEXT("Test111"), UDD_DialogueGraph::StaticClass(), UDD_DialogueGraphSchema::StaticClass());
		const UEdGraphSchema* Schema = pNewGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*pNewGraph);
		DialogueData->TestGraph = pNewGraph;
	}
	
	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(DialogueData->TestGraph);
	if(DocumentManager.IsValid())
	{
		TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, bNewGraph ? FDocumentTracker::OpenNewDocument : FDocumentTracker::RestorePreviousDocument);
	}
}

#undef LOCTEXT_NAMESPACE
