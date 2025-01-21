#include "DD_DialogueEditor.h"

#include "AssetToolsModule.h"
#include "Editor/AssetFactory/DD_DialogueEditorStyle.h"
#include "Editor/AssetFactory/DD_Dialogue_AssetTypeActions.h"

TArray<TSharedPtr<FDD_Dialogue_AssetTypeActions>> AssetAction;

void FDD_DialogueEditorModule::StartupModule()
{
	const auto& Actions = MakeShared<FDD_Dialogue_AssetTypeActions>();
	AssetAction.Emplace(Actions);

	if (FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for(auto Action : AssetAction)
		{
			AssetToolsModule->Get().RegisterAssetTypeActions(Action.ToSharedRef());
		}
	}
	
	FDD_DialogueEditorStyle::MakeInstance();
}

void FDD_DialogueEditorModule::ShutdownModule()
{
	FDD_DialogueEditorStyle::RemoveInstance();

	if (FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		for(auto Action : AssetAction)
		{
			AssetToolsModule->Get().UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

IMPLEMENT_MODULE(FDD_DialogueEditorModule, DD_DialogueEditor)