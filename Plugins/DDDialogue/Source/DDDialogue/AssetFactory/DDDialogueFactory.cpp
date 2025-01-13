// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueFactory.h"

#include "DDDialogueDataAsset.h"
#include "DDDialogue/DialogueGraph/Editor/FDDialogueEditor.h"

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
	return NSLOCTEXT("AssetTypeActions", "DDDialogue_AssetTypeName", "DD Dialogue");
}

UClass* FDDDialogue_AssetTypeActions::GetSupportedClass() const
{
	return UDDDialogueDataAsset::StaticClass();
}

FColor FDDDialogue_AssetTypeActions::GetTypeColor() const
{
	return FColor::Purple;
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetIconBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return nullptr;
}

const FSlateBrush* FDDDialogue_AssetTypeActions::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FAssetTypeActions_Base::GetThumbnailBrush(InAssetData, InClassName);
}

void FDDDialogue_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	TSharedRef<FDDialogueEditor> DialogueEditor = MakeShared<FDDialogueEditor>();
	DialogueEditor->OpenDialogueEditor(InObjects, EditWithinLevelEditor);
}
