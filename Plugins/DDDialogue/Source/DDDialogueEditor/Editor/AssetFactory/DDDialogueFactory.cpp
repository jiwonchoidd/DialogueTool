#include "DDDialogueFactory.h"

#include "DDDialogue/Dialogue/DDDialogueDataAsset.h"

#define LOCTEXT_NAMESPACE "UDDDialogueFactory"

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

FText UDDDialogueFactory::GetDisplayName() const
{
	return LOCTEXT("DDDialogue Data", "Dialogue Data");
}

FText UDDDialogueFactory::GetToolTip() const
{
	return Super::GetToolTip();
}

#undef LOCTEXT_NAMESPACE