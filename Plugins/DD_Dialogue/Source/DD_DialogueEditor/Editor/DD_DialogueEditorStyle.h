#pragma once

namespace StyleNamespace
{
	const FName Icon16 = FName("DD_Dialogue16.Icon");
	const FName Icon64 = FName("DD_Dialogue64.Icon");
	// FSlateIconFinder::FindCustomIconForClass
	const FName MenuThumbnail = FName("ClassThumbnail.DD_DialogueData");
}

class DD_DIALOGUEEDITOR_API FDD_DialogueEditorStyle : public FSlateStyleSet
{
public:
	FDD_DialogueEditorStyle();
	virtual ~FDD_DialogueEditorStyle() override;

public:
	static void							MakeInstance();
	static void							RemoveInstance();
	static const FDD_DialogueEditorStyle& GetInstance();
private:
	static FDD_DialogueEditorStyle*		Inst;
};

#define gDialStyle FDD_DialogueEditorStyle::GetInstance()