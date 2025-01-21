#include "DD_Dialogue_AssetTypeActions.h"

#include "DD_DialogueEditorStyle.h"
#include "DD_Dialogue/Dialogue/DD_DialogueData.h"
#include "DD_DialogueEditor/Editor/DD_DialogueGraphEditor.h"

#define LOCTEXT_NAMESPACE "UDD_DialogueFactory"

uint32 FDD_Dialogue_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

FText FDD_Dialogue_AssetTypeActions::GetName() const
{
	return INVTEXT("Simple Dialogue");
}

FText FDD_Dialogue_AssetTypeActions::GetDisplayNameFromAssetData(const FAssetData& AssetData) const
{
	return INVTEXT("Simple Dialogue");
}

UClass* FDD_Dialogue_AssetTypeActions::GetSupportedClass() const
{
	return UDD_DialogueData::StaticClass();
}

FColor FDD_Dialogue_AssetTypeActions::GetTypeColor() const
{
	return FColor::White;
}

const FSlateBrush* FDD_Dialogue_AssetTypeActions::GetIconBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return gDialStyle.GetBrush(StyleNamespace::Icon16);
}

const FSlateBrush* FDD_Dialogue_AssetTypeActions::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return gDialStyle.GetBrush(StyleNamespace::Icon16);
}

void FDD_Dialogue_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TSharedRef<FDD_DialogueGraphEditor> DialogueEditor = MakeShared<FDD_DialogueGraphEditor>();
	DialogueEditor->OpenDialogueEditor(InObjects, EditWithinLevelEditor);
}

#undef LOCTEXT_NAMESPACE