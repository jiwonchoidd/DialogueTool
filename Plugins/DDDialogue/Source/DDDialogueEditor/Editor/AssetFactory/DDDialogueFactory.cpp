// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueFactory.h"

#include "DDDialogue/Dialogue/DDDialogueDataAsset.h"
#include "DDDialogueEditor/Editor/FDDialogueEditor.h"
#include "DDDialogueEditor/Editor/FDDialogueEditorStyle.h"

UDDDialogueFactory::UDDDialogueFactory()
{
	SupportedClass = UDDDialogueDataAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDDDialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDDDialogueDataAsset>(InParent, Class, Name, Flags);
}

//------------------------------------------------------------------------------

uint32 FDDDialogue_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FDDDialogue_AssetTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "DDDialogue_AssetTypeName", "DDDialogue");
}

UClass* FDDDialogue_AssetTypeActions::GetSupportedClass() const
{
	return UDDDialogueDataAsset::StaticClass();
}

FColor FDDDialogue_AssetTypeActions::GetTypeColor() const
{
	return FColor::White;
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetIconBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FDDialogueEditorStyle::Get().GetBrush(StyleNamespace::Icon);
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FDDialogueEditorStyle::Get().GetBrush(StyleNamespace::Icon);
}

void FDDDialogue_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TSharedRef<FDDialogueEditor> DialogueEditor = MakeShared<FDDialogueEditor>();
	DialogueEditor->OpenDialogueEditor(InObjects, EditWithinLevelEditor);
}
