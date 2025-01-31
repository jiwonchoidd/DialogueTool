#include "DD_DialogueGraphEditor.h"

#include "DD_DialogueEditorStyle.h"
#include "GraphEditorActions.h"
#include "DD_Dialogue/DD_Dialogue.h"
#include "DD_Dialogue/Dialogue/DD_DialogueData.h"
#include "DD_Dialogue/Dialogue/Graph/DD_DialogueGraph.h"
#include "DD_Dialogue/Dialogue/Graph/DD_DialogueGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"

const FName AppIdentifier("DD_DialogueEditorApp");
const FName PropertiesTabId(TEXT("DialogueGraphEditor_Properties"));
const FName GraphTabId(TEXT("DialogueGraphEditor_Graph"));

#define LOCTEXT_NAMESPACE "FDD_DialogueEditor"

FDD_DialogueGraphEditor::FDD_DialogueGraphEditor()
{
}

FDD_DialogueGraphEditor::~FDD_DialogueGraphEditor()
{
	//GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.RemoveAll(this);
	//FCoreUObjectDelegates::OnObjectsReplaced.RemoveAll(this);

	DetailsView.Reset();
}

void FDD_DialogueGraphEditor::InitDialogueEditor(EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, class UDD_DialogueData* _pDialogueData)
{
	DialogueData = _pDialogueData;

	
	CommonInitialization();

	TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DialogueEditor_Layout_v3")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			                             ->Split
			                             (
				                             FTabManager::NewSplitter()
				                             ->Split
				                             (
					                             FTabManager::NewStack()
					                             ->SetSizeCoefficient(0.2f)
					                             ->AddTab(PropertiesTabId, ETabState::OpenedTab)
				                             )
				                             ->Split
				                             (
					                             FTabManager::NewStack()
					                             ->SetSizeCoefficient(0.8f)
					                             ->AddTab(GraphTabId, ETabState::OpenedTab)
				                             )
			                             )
		);

	constexpr bool bCreateDefaultStandaloneMenu = true;
	constexpr bool bCreateDefaultToolbar = true;

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(DialogueData);
	InitAssetEditor(EToolkitMode::Standalone, InitToolkitHost, AppIdentifier, StandaloneDefaultLayout,
	                bCreateDefaultStandaloneMenu,
	                bCreateDefaultToolbar, ObjectsToEdit);

	RegenerateMenusAndToolbars();
}

//-------------------------------------------------------------------------------------

class UDD_DialogueData* FDD_DialogueGraphEditor::GetGraphData() const
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
	UE_LOG(DD_Dialogue, Log, TEXT("OnSelectedNodesChanged"))
}

void FDD_DialogueGraphEditor::OnNodeDoubleClicked(class UEdGraphNode* _GraphNode)
{
	UE_LOG(DD_Dialogue, Log, TEXT("OnNodeDoubleClicked"))
}

void FDD_DialogueGraphEditor::OnNodeTitleCommitted(const FText& _Text, ETextCommit::Type _Type,
                                                   UEdGraphNode* _GraphNode)
{
	UE_LOG(DD_Dialogue, Log, TEXT("OnNodeTitleCommitted"))
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
	//InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FBlueprintEditor::OnCreateGraphActionMenu);

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
				.Text(LOCTEXT("TitleBar", "Dialogue Graph"))
				.TextStyle(FAppStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
			]
		];

	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
				.AdditionalCommands(GraphEditorCommands)
	            .IsEditable(this, &FDD_DialogueGraphEditor::InEditingMode, bGraphIsEditable)
	            .Appearance(this, &FDD_DialogueGraphEditor::GetGraphAppearance)
	            .TitleBar(TitleBarWidget)
	            .GraphToEdit(InGraph)
	            .GraphEvents(InEvents)
				.AutoExpandActionMenu(true)
				.ShowGraphStateOverlay(false);
}

void FDD_DialogueGraphEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	WorkspaceMenuCategory = _TabManager->AddLocalWorkspaceMenuCategory(
		LOCTEXT("WorkspaceMenu_GenericAssetEditor", "Asset Editor"));
	FWorkflowCentricApplication::RegisterTabSpawners(_TabManager);

	_TabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FDD_DialogueGraphEditor::SpawnGraphTab))
	           .SetDisplayName(LOCTEXT("GraphCanvasTab", "Graph"))
	           .SetGroup(WorkspaceMenuCategory.ToSharedRef())
	           .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));

	_TabManager->RegisterTabSpawner(PropertiesTabId,
	                                FOnSpawnTab::CreateSP(this, &FDD_DialogueGraphEditor::SpawnPropertiesTab))
	           .SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
	           .SetGroup(WorkspaceMenuCategory.ToSharedRef())
	           .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Dialogue.Tabs.Details"))
	           .SetReadOnlyBehavior(ETabReadOnlyBehavior::Custom);
}

void FDD_DialogueGraphEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(_TabManager);
	_TabManager->UnregisterTabSpawner(GraphTabId);
	_TabManager->UnregisterTabSpawner(PropertiesTabId);
}

//-------------------------------------------------------------------------------------

FGraphAppearanceInfo FDD_DialogueGraphEditor::GetGraphAppearance() const
{
	// Temp Appearance..
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("EditorUtilityAppearanceCornerText", "Dialogue Editor");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_DefaultGraph",
	                                         "Drag Off Pins to Create/Connect New Nodes.");
	return AppearanceInfo;
}

bool FDD_DialogueGraphEditor::InEditingMode(bool bGraphIsEditable) const
{
	const bool bPlayWorld = !GEditor->bIsSimulatingInEditor && (GEditor->PlayWorld == NULL);
	return bGraphIsEditable && bPlayWorld;
}

void FDD_DialogueGraphEditor::CommonInitialization()
{
	// Graph
	const bool bNewGraph = DialogueData->Graph == nullptr;
	if (bNewGraph)
	{
		UEdGraph* pNewGraph = FBlueprintEditorUtils::CreateNewGraph(DialogueData, NAME_None,
		                                                            UDD_DialogueGraph::StaticClass(),
		                                                            UDD_DialogueGraphSchema::StaticClass());
		const UEdGraphSchema* Schema = pNewGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*pNewGraph);
		DialogueData->Graph = Cast<UDD_DialogueGraph>(pNewGraph);
	}

	// CommandList
	FGraphEditorCommands::Register();
	//FDialogueGraphEditorCommands::Register();

	/*const FSoundCueGraphEditorCommands& Commands = FSoundCueGraphEditorCommands::Get();
	ToolkitCommands->MapAction(
		Commands.PlayCue,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::PlayCue));

	ToolkitCommands->MapAction(
		Commands.PlayNode,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::PlayNode),
		FCanExecuteAction::CreateSP( this, &FSoundCueEditor::CanPlayNode ));

	ToolkitCommands->MapAction(
		Commands.StopCueNode,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::Stop));

	ToolkitCommands->MapAction(
		Commands.TogglePlayback,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::TogglePlayback));

	ToolkitCommands->MapAction(
		FGenericCommands::Get().Undo,
		FExecuteAction::CreateSP( this, &FSoundCueEditor::UndoGraphAction ));

	ToolkitCommands->MapAction(
		FGenericCommands::Get().Redo,
		FExecuteAction::CreateSP( this, &FSoundCueEditor::RedoGraphAction ));

	ToolkitCommands->MapAction(
		Commands.ToggleSolo,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::ToggleSolo),
		FCanExecuteAction::CreateSP(this, &FSoundCueEditor::CanExcuteToggleSolo),
		FIsActionChecked::CreateSP(this, &FSoundCueEditor::IsSoloToggled));
		
	ToolkitCommands->MapAction(
		Commands.ToggleMute,
		FExecuteAction::CreateSP(this, &FSoundCueEditor::ToggleMute),
		FCanExecuteAction::CreateSP(this, &FSoundCueEditor::CanExcuteToggleMute),
		FIsActionChecked::CreateSP(this, &FSoundCueEditor::IsMuteToggled));*/
	
	// Tab Widget
	if (!GraphEditor.IsValid())
	{
		GraphEditor = CreateGraphEditorWidget(DialogueData->Graph);
	}

	if (!DetailsView.IsValid())
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
			"PropertyEditor");
		FDetailsViewArgs DetailsViewArgs;
		DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
		DetailsViewArgs.NotifyHook = this;
		DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
		DetailsView->SetObjects(TArray<UObject*>{DialogueData});
	}
}

TSharedRef<SDockTab> FDD_DialogueGraphEditor::SpawnGraphTab(const FSpawnTabArgs& _Args) const
{
	check(_Args.GetTabId() == GraphTabId);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("SoundCueGraphCanvasTitle", "Viewport"));

	if (GraphEditor.IsValid())
	{
		SpawnedTab->SetContent(GraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FDD_DialogueGraphEditor::SpawnPropertiesTab(const FSpawnTabArgs& _Args) const
{
	check(_Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		.OnCanCloseTab_Lambda([]() { return false; })
		[
			DetailsView.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE
