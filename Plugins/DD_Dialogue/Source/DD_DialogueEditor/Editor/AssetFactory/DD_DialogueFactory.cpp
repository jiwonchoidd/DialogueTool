#include "DD_DialogueFactory.h"

#include "DD_Dialogue/Dialogue/DD_DialogueData.h"

#define LOCTEXT_NAMESPACE "UDD_DialogueFactory"

UDD_DialogueFactory::UDD_DialogueFactory()
{
	SupportedClass = UDD_DialogueData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UDD_DialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDD_DialogueData>(InParent, Class, Name, Flags);
}

FText UDD_DialogueFactory::GetDisplayName() const
{
	return LOCTEXT("DD_Dialogue Data", "Dialogue Data");
}

FText UDD_DialogueFactory::GetToolTip() const
{
	return Super::GetToolTip();
}

#undef LOCTEXT_NAMESPACE
