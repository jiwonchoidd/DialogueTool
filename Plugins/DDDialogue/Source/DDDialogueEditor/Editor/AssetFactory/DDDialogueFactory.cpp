#include "DDDialogueFactory.h"

#include "DDDialogue/Dialogue/DDDialogueData.h"
#include "DDDialogueEditor/Editor/FDDialogueEditorStyle.h"

#define LOCTEXT_NAMESPACE "UDDDialogueFactory"

UDDDialogueFactory::UDDDialogueFactory()
{
	SupportedClass = UDDDialogueData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDDDialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDDDialogueData>(InParent, Class, Name, Flags);
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
