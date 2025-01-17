#include "FDDDialogue_AssetTypeActions.h"

#include "DDDialogue/Dialogue/DDDialogueData.h"
#include "DDDialogueEditor/Editor/FDDialogueEditor.h"
#include "DDDialogueEditor/Editor/FDDialogueEditorStyle.h"

#define LOCTEXT_NAMESPACE "UDDDialogueFactory"

uint32 FDDDialogue_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

FText FDDDialogue_AssetTypeActions::GetName() const
{
	return LOCTEXT("DialogueAssetTypeActionsName", "DDDialogue");
}

UClass* FDDDialogue_AssetTypeActions::GetSupportedClass() const
{
	return UDDDialogueData::StaticClass();
}

FColor FDDDialogue_AssetTypeActions::GetTypeColor() const
{
	return FColor::White;
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetIconBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FDDialogueEditorStyle::Get().GetBrush(StyleNamespace::Icon16);
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FDDialogueEditorStyle::Get().GetBrush(StyleNamespace::Icon16);
}

void FDDDialogue_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TSharedRef<FDDialogueEditor> DialogueEditor = MakeShared<FDDialogueEditor>();
	DialogueEditor->Initialize();
	DialogueEditor->OpenDialogueEditor(InObjects, EditWithinLevelEditor);
}

#undef LOCTEXT_NAMESPACE