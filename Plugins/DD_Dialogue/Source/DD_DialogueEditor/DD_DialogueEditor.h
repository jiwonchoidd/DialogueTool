#pragma once

#include "CoreMinimal.h"

/*
 * 에디터 전용 모듈 - 참고
 * https://easycomplex-tech.com/blog/Unreal/AssetEditor/UEAssetEditorDev-AssetEditorGraph/
 */

class FDD_DialogueEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
