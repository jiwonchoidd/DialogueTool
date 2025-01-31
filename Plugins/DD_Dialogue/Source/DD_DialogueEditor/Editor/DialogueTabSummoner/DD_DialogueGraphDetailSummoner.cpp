#include "DD_DialogueGraphDetailSummoner.h"

#include "DD_DialogueEditor/Editor/DD_Define.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "DD_DialogueEditor/Editor/DD_DialogueGraphEditor.h"

#define LOCTEXT_NAMESPACE "FDD_DialogueEditor"

FDD_DialogueGraphDetailSummoner::FDD_DialogueGraphDetailSummoner(const TSharedPtr<class FDD_DialogueGraphEditor>& _EditorPtr)
	: FWorkflowTabFactory(FDialogueEditorTabs::GraphDetailsID,  _EditorPtr)
	, DialogueEditorPtr(_EditorPtr)
{
	TabLabel = LOCTEXT("DialogueLabel", "Dialogue");
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "BTEditor.Blackboard");

	bIsSingleton = true;

	ViewMenuDescription = LOCTEXT("DialogueEditor", "Dialogue");
	ViewMenuTooltip = LOCTEXT("DialogueEditor_ToolTip", "Show the Dialogue editor");
}

TSharedRef<SWidget> FDD_DialogueGraphDetailSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return DialogueEditorPtr.Pin()->SpawnEditor();
}

FText FDD_DialogueGraphDetailSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return LOCTEXT("BehaviorTreeDetailsTabTooltip", "The behavior tree details tab allows editing of the properties of behavior tree nodes");
}

#undef LOCTEXT_NAMESPACE
