#include "DD_DialogueEditorMode.h"

#include "DD_DialogueEditor/Editor/DD_Define.h"
#include "DD_DialogueEditor/Editor/DD_DialogueGraphEditor.h"
#include "DD_DialogueEditor/Editor/DialogueTabSummoner/DD_DialogueGraphDetailSummoner.h"


#define LOCTEXT_NAMESPACE "FDD_DialogueEditorMode"

FDD_DialogueEditorMode::FDD_DialogueEditorMode(const TSharedPtr<FDD_DialogueGraphEditor>& _InEditor) :
	FApplicationMode(FDialogueApplicationModes::StandardMode, [](const FName _ModeName) -> FText
	{
		return FText::FromString(TEXT("Mode: ") + _ModeName.ToString());
	})
{
	MyEditor = _InEditor;

	{
		TabFactories.RegisterFactory(MakeShareable(new FDD_DialogueGraphDetailSummoner(_InEditor)));
	}

	TabLayout = FTabManager::NewLayout("Standalone_ConversationEditor_GraphView_Layout_v4")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.7f)
				->AddTab(FDialogueEditorTabs::GraphEditorID, ETabState::ClosedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.3f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6f)
					->AddTab(FDialogueEditorTabs::GraphDetailsID, ETabState::OpenedTab)
					//->AddTab(FConversationEditorTabs::SearchID, ETabState::ClosedTab)
				)
			)
		);
}

void FDD_DialogueEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	check(MyEditor.IsValid());
	TSharedPtr<FDD_DialogueGraphEditor> EditorPtr = MyEditor.Pin();
	
	//BehaviorTreeEditorPtr->RegisterToolbarTab(InTabManager.ToSharedRef());
	EditorPtr->PushTabFactories(TabFactories);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FDD_DialogueEditorMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
	check(MyEditor.IsValid());
	TSharedPtr<FDD_DialogueGraphEditor> EditorPtr = MyEditor.Pin();
	
	//EditorPtr->SaveEditedObjectState();
}

void FDD_DialogueEditorMode::PostActivateMode()
{
	check(MyEditor.IsValid());
	TSharedPtr<FDD_DialogueGraphEditor> EditorPtr = MyEditor.Pin();
	//EditorPtr->RestoreBehaviorTree();

	FApplicationMode::PostActivateMode();
}
#undef LOCTEXT_NAMESPACE
