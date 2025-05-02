// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/EvaluationAISettings.h"
#include "Core/EvaluationAIEvaluationHelper.h"

FName UEvaluationAISettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}
