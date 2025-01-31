#include "DD_DialogueEditorStyle.h"

#include "Styling/SlateStyleRegistry.h"

FDD_DialogueEditorStyle* FDD_DialogueEditorStyle::Inst = nullptr;

FDD_DialogueEditorStyle::FDD_DialogueEditorStyle() : FSlateStyleSet("DD_DialogueEditorStyle")
{
	FString IconPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("DD_Dialogue/Icon.png"));
	if(FPaths::FileExists(IconPath))
	{
		Set(StyleNamespace::Icon16, new FSlateImageBrush(IconPath, FVector2D(16.0f, 16.0f)));
		Set(StyleNamespace::Icon64, new FSlateImageBrush(IconPath, FVector2D(64.0f, 64.0f)));
		Set(StyleNamespace::MenuThumbnail, new FSlateImageBrush(IconPath, FVector2D(64.0f, 64.0f)));
	}
	
	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FDD_DialogueEditorStyle::~FDD_DialogueEditorStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

void FDD_DialogueEditorStyle::MakeInstance()
{
	if(Inst) return;
	Inst = new FDD_DialogueEditorStyle();
}

void FDD_DialogueEditorStyle::RemoveInstance()
{
	if(!Inst) return;
	delete Inst;
	Inst = nullptr;
}

const FDD_DialogueEditorStyle& FDD_DialogueEditorStyle::GetInstance()
{
	if(!Inst) MakeInstance();
	return *Inst;
}
