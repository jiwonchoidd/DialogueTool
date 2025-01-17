#pragma once

namespace StyleNamespace
{
	const FName Icon16 = FName("DDDialogue16.Icon");
	const FName Icon64 = FName("DDDialogue64.Icon");
	// FSlateIconFinder::FindCustomIconForClass
	const FName MenuThumbnail = FName("ClassThumbnail.DDDialogueData");
}

class FDDialogueEditorStyle : public FSlateStyleSet
{
public:
	FDDialogueEditorStyle();

	virtual ~FDDialogueEditorStyle() override;

	static const FDDialogueEditorStyle& Get();
};
