// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDialogueFactory.h"

#include "DDDialogue/DialogueGraph/DDDialogueGraph.h"

UDDDialogueFactory::UDDDialogueFactory()
{
	SupportedClass = UDDDialogueGraph::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDDDialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDDDialogueGraph>(InParent, Class, Name, Flags);
}


//------------------------------------------------------------------------------

uint32 FDDDialogue_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

FText FDDDialogue_AssetTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_Graph", "Dialogue_Graph");
}

UClass* FDDDialogue_AssetTypeActions::GetSupportedClass() const
{
	return UDDDialogueGraph::StaticClass();
}

FColor FDDDialogue_AssetTypeActions::GetTypeColor() const
{
	return FColor::Purple;
}
