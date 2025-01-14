#pragma once

#include "CoreMinimal.h"

/*
 * 에디터 전용 모듈 
 */ 
class FDDDialogueEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
