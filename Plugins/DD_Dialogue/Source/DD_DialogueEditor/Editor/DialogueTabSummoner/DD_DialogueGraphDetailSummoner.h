#pragma once
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

struct DD_DIALOGUEEDITOR_API FDD_DialogueGraphDetailSummoner : public FWorkflowTabFactory
{
public:
	FDD_DialogueGraphDetailSummoner(const TSharedPtr<class FDD_DialogueGraphEditor>& _EditorPtr);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<FDD_DialogueGraphEditor> DialogueEditorPtr = nullptr;
};
