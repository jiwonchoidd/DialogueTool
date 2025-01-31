#include "DD_DialogueEditor.h"

#include "AssetToolsModule.h"
#include "Editor/DD_Define.h"
#include "Editor/DD_DialogueEditorStyle.h"
#include "Editor/DD_Dialogue_AssetTypeActions.h"

// Tab identifiers
const FName FDialogueEditorTabs::GraphDetailsID(TEXT("FDialogueEditorTabs_GraphDetails"));
const FName FDialogueEditorTabs::GraphEditorID(TEXT("FDialogueEditorTabs_GraphEditor"));
const FName FDialogueApplicationModes::StandardMode(TEXT("FDialogueEditorStandard_Mode"));

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