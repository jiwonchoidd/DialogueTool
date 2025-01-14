#include "FDDialogueEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"

FDDialogueEditorStyle::FDDialogueEditorStyle() : FSlateStyleSet("DDialogueEditorStyle")
{
	FString IconPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("DDDialogue/Icon.png"));
	if(FPaths::FileExists(IconPath))
	{
		Set(StyleNamespace::Icon, new FSlateImageBrush(IconPath, FVector2D(64.0f, 64.0f)));
	}
	
	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FDDialogueEditorStyle::~FDDialogueEditorStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

const FDDialogueEditorStyle& FDDialogueEditorStyle::Get()
{
	static const FDDialogueEditorStyle Inst;
	return Inst;
}
