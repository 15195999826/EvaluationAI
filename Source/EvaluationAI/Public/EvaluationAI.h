// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

EVALUATIONAI_API DECLARE_LOG_CATEGORY_EXTERN(LogEvaluationAI, Log, All);

class FEvaluationAIModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
