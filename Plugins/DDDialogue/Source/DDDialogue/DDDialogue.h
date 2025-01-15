// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DDDIALOGUE_API DECLARE_LOG_CATEGORY_EXTERN(DDDialogue, Log, All);

class FDDDialogueModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
