#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEvaluationAIEditorModuleModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    /** 注册自定义详情面板 */
    void RegisterCustomizations();
	
    /** 注销自定义详情面板 */
    void UnregisterCustomizations();
};
