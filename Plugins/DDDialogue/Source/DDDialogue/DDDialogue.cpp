// Copyright Epic Games, Inc. All Rights Reserved.

#include "DDDialogue.h"

#include "AssetToolsModule.h"
#include "AssetFactory/DDDialogueFactory.h"

#define LOCTEXT_NAMESPACE "FDDDialogueModule"

TUniquePtr<FDDDialogue_AssetTypeActions> Actions;

void FDDDialogueModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	Actions = MakeUnique<FDDDialogue_AssetTypeActions>();
	AssetTools.RegisterAssetTypeActions(Actions->AsShared());

}

void FDDDialogueModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(Actions->AsShared());
	}	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDDDialogueModule, DDDialogue)