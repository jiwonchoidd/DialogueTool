// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FDDDialogueModule"
DECLARE_LOG_CATEGORY_EXTERN(DDDialogue, Log, All);

class FDDDialogueModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static bool IsPIENotSimulating();
};
