// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDDialogue.h"

#include "AssetToolsModule.h"
#include "AssetFactory/DDDialogueFactory.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FDDDialogueModule"

TSharedPtr<FDDDialogue_AssetTypeActions> Actions;
TSharedPtr<FSlateStyleSet> Styles;

void FDDDialogueModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// Regist Action
	Actions = MakeShared<FDDDialogue_AssetTypeActions>();
	if(Actions.IsValid())
	{
		AssetTools.RegisterAssetTypeActions(Actions.ToSharedRef());
	}

	// Regist Icon
	Styles = MakeShareable<FSlateStyleSet>(new FSlateStyleSet("DDDialogueStyle"));

	FString IconPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("DDDialogue/Icon.png"));
	if(FPaths::FileExists(IconPath))
	{
		Styles->Set("DDDialogue.Icon", new FSlateImageBrush(IconPath, FVector2D(64.0f, 64.0f)));
		FSlateStyleRegistry::RegisterSlateStyle(*Styles);
	}
}

void FDDDialogueModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		if(Styles.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*Styles);
			Styles.Reset();
		}
		if(Actions.IsValid())
		{
			AssetTools.UnregisterAssetTypeActions(Actions.ToSharedRef());
			Actions.Reset();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDDDialogueModule, DDDialogue)