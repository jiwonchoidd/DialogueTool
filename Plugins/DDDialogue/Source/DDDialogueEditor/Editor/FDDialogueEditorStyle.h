#pragma once

namespace StyleNamespace
{
	const FName Icon = FName("DDDialogue.Icon");
}

class FDDialogueEditorStyle : public FSlateStyleSet
{
public:
	FDDialogueEditorStyle();

	virtual ~FDDialogueEditorStyle() override;

	static const FDDialogueEditorStyle& Get();
};
