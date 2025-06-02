#include "DD_TalkNode.h"

#include "Widgets/Input/SMultiLineEditableTextBox.h"

void UDD_TalkNode::AllocateDefaultPins()
{
	check(Pins.Num() == 0);

	CreatePin(EGPD_Input, TEXT("DialogueNode"), TEXT("Input"));
	CreatePin(EGPD_Output, TEXT("DialogueNode"), TEXT("Output"));
}

TSharedPtr<SGraphNode> UDD_TalkNode::CreateVisualWidget()
{
	TSharedPtr<SGraphNode> NodeWidget = SNew(STalkNode, this);
	return NodeWidget;
}

//----------------------------------------------------------------------------

void STalkNode::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	this->GraphNode = InNode;

	this->SetCursor(EMouseCursor::CardinalCross);
	this->UpdateGraphNode();
}

void STalkNode::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	MainBox->AddSlot()
	.AutoHeight()
	.Padding(5.0f)
	[
		SAssignNew(EditableText, SMultiLineEditableTextBox)
		.Text(FText::FromString(TEXT("내용을 입력하세요...")))
	];
}

void STalkNode::GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const
{
	SGraphNode::GetNodeInfoPopups(Context, Popups);
}
