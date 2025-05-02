// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvaluationAI.h"

DEFINE_LOG_CATEGORY(LogEvaluationAI);

#define LOCTEXT_NAMESPACE "FEvaluationAIModule"

void FEvaluationAIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// 输出插件加载信息
	UE_LOG(LogEvaluationAI, Log, TEXT("EvaluationAI Plugin loaded"));
}

void FEvaluationAIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	UE_LOG(LogEvaluationAI, Log, TEXT("EvaluationAI Plugin unloaded"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEvaluationAIModule, EvaluationAI)