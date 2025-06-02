// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DD_DialogueBaseNode.h"
#include "SGraphNode.h"
#include "DD_TalkNode.generated.h"

/**
 * 
 */
UCLASS()
class DD_DIALOGUE_API UDD_TalkNode : public UDD_DialogueBaseNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	// End of UEdGraphNode interface.

	/** 노드의 대사 */
	UPROPERTY(EditAnywhere, Category = "Dialogue")
	FString DialogueText;
};

class STalkNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(STalkNode)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);

protected:
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
	// SNodePanel::SNode interface
	virtual void
	GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;
	// End of SNodePanel::SNode interface

	// SGraphNode interface
	virtual void UpdateGraphNode() override
	{
		SGraphNode::UpdateGraphNode();
		RemoveSlot(ENodeZone::TopCenter);
	}
	// End of SGraphNode interface
private:
	TSharedPtr<class SMultiLineEditableTextBox> EditableText;
};
