#include "DDDialogueEditor.h"

#include "AssetToolsModule.h"
#include "Editor/AssetFactory/FDDDialogue_AssetTypeActions.h"

TArray<TSharedPtr<FDDDialogue_AssetTypeActions>> AssetAction;

void FDDDialogueEditorModule::StartupModule()
{
	const auto& Actions = MakeShared<FDDDialogue_AssetTypeActions>();
	AssetAction.Emplace(Actions);

	if (FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for(auto Action : AssetAction)
		{
			AssetToolsModule->Get().RegisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

void FDDDialogueEditorModule::ShutdownModule()
{
	if (FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for(auto Action : AssetAction)
		{
			AssetToolsModule->Get().UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

IMPLEMENT_MODULE(FDDDialogueEditorModule, DDDialogueEditor)