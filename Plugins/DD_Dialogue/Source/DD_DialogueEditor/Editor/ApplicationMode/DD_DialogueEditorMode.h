#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"



class DD_DIALOGUEEDITOR_API FDD_DialogueEditorMode : public FApplicationMode
{
public:
	FDD_DialogueEditorMode(const TSharedPtr<class FDD_DialogueGraphEditor>& _InEditor);

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;
protected:
	TWeakPtr<FDD_DialogueGraphEditor> MyEditor;

	// Set of spawnable tabs in Class Defaults mode
	FWorkflowAllowedTabSet TabFactories;
};
