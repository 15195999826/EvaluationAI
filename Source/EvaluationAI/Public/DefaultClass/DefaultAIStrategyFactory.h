// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/EvaluationAIStrategyFactory.h"
#include "DefaultAIStrategyFactory.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATIONAI_API UDefaultAIStrategyFactory : public UEvaluationAIStrategyFactory
{
	GENERATED_BODY()

public:
	virtual UEvaluationAIStrategy* CreateStrategy(UObject* Outer, const FStrategyConfigData& InStrategyConfig) override;

protected:
	virtual void InitializeStrategy(UEvaluationAIStrategy* NewStrategy, const FStrategyConfigData& InStrategyConfig) override;
};
