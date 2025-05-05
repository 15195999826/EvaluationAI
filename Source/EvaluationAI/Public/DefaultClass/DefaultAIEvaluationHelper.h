// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/EvaluationAIEvaluationHelper.h"
#include "DefaultAIEvaluationHelper.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATIONAI_API UDefaultAIEvaluationHelper : public UEvaluationAIEvaluationHelper
{
	GENERATED_BODY()

public:
	virtual UEvaluationWorldContext* MakeWorldContext() override;

	// 评估所有选项
	virtual void EvaluateAllActions(const UEvaluationAIDecisionComponent* InOwner,
	                                const UEvaluationWorldContext* InWorldContext,
	                                TArray<FEvaluationAIDecisionResult>& OutOptions) override;

	// 评估单个行动选项
	virtual void EvaluateAction(const UEvaluationAIDecisionComponent* InOwner,
	                            const UEvaluationWorldContext* InWorldContext,
	                            FEvaluationAIDecisionResult& OutEvaluatedOption) override;

	// 从评估选项中选择最佳选项
	virtual const FEvaluationAIDecisionResult& SelectBestAction(UEvaluationAIDecisionComponent* InOwner,
	                                                            const UEvaluationWorldContext* InWorldContext,
	                                                            const TArray<FEvaluationAIDecisionResult>& Options) override;
};
