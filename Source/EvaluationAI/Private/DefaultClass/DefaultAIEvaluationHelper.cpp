// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultClass/DefaultAIEvaluationHelper.h"

UEvaluationWorldContext* UDefaultAIEvaluationHelper::MakeWorldContext()
{
	return Super::MakeWorldContext();
}

void UDefaultAIEvaluationHelper::EvaluateAllActions(const UEvaluationAIDecisionComponent* InOwner,
	const UEvaluationWorldContext* InWorldContext, TArray<FEvaluationAIDecisionResult>& OutOptions)
{
	Super::EvaluateAllActions(InOwner, InWorldContext, OutOptions);
}

void UDefaultAIEvaluationHelper::EvaluateAction(const UEvaluationAIDecisionComponent* InOwner,
	const UEvaluationWorldContext* InWorldContext, FEvaluationAIDecisionResult& OutEvaluatedOption)
{
	Super::EvaluateAction(InOwner, InWorldContext, OutEvaluatedOption);
}

const FEvaluationAIDecisionResult& UDefaultAIEvaluationHelper::SelectBestAction(UEvaluationAIDecisionComponent* InOwner,
	const UEvaluationWorldContext* InWorldContext, const TArray<FEvaluationAIDecisionResult>& Options)
{
	return Super::SelectBestAction(InOwner, InWorldContext, Options);
}
