// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvaluationAITypes.h"
#include "UObject/Object.h"
#include "EvaluationAlgorithm.generated.h"

class UEvaluationAIDecisionComponent;
/**
 * 针对各个选项的评分细则， 不同类型的AI可能有不同的评分细则
 */
UCLASS(Abstract)
class EVALUATIONAI_API UEvaluationAlgorithm : public UObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;
	
	virtual void EvaluateAllActions(
		const UEvaluationAIDecisionComponent* InOwner,
		TArray<FEvaluationAIDecisionResult>& OutOptions) PURE_VIRTUAL(UEvaluationAlgorithm::EvaluateAllActions,);

	// 评估单个行动选项
	virtual void EvaluateAction(
		const UEvaluationAIDecisionComponent* InOwner,
		FEvaluationAIDecisionResult& OutEvaluatedOption) PURE_VIRTUAL(UEvaluationAlgorithm::EvaluateAction,);

	// 从评估选项中选择最佳选项
	virtual const FEvaluationAIDecisionResult& SelectBestAction(
		UEvaluationAIDecisionComponent* InOwner,
		const TArray<FEvaluationAIDecisionResult>& Options) PURE_VIRTUAL(
		UEvaluationAlgorithm::SelectBestAction, {static FEvaluationAIDecisionResult Invalid; return Invalid; });
};
