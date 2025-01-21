// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DD_DIALOGUE_API DECLARE_LOG_CATEGORY_EXTERN(DD_Dialogue, Log, All);

class FDD_DialogueModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
