// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIEvaluationHelper.generated.h"

/**
 * AI评估助手类 - 提供评估函数的入口点
 * 
 * 这个类不存储状态，只提供辅助评估功能。具体实现应由实际项目根据需要重写。
 * 它作为一个成员变量存放在EvaluationAIDecisionSystem中，为决策提供支持。
 * 
 * 主要职责:
 * - 提供通用的评估函数入口
 * - 为特定类型的行动提供评估逻辑
 * - 支持基于难度的评分调整
 * - 添加适当的随机性
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class EVALUATIONAI_API UEvaluationAIEvaluationHelper : public UObject
{
    GENERATED_BODY()
    
public:
    UEvaluationAIEvaluationHelper();

	virtual void InitHelper();
	
    virtual UEvaluationWorldContext* MakeWorldContext() PURE_VIRTUAL(UEvaluationAIEvaluationHelper::MakeWorldContext, return nullptr;);

    // 评估所有选项
    virtual void EvaluateAllActions(const UEvaluationAIDecisionComponent* InOwner,
                                    const UEvaluationWorldContext* InWorldContext,
                                    TArray<FEvaluationAIDecisionResult>& OutOptions)
									PURE_VIRTUAL(UEvaluationAIEvaluationHelper::EvaluateAllActions, );

    // 评估单个行动选项
    virtual void EvaluateAction(const UEvaluationAIDecisionComponent* InOwner,
                                const UEvaluationWorldContext* InWorldContext,
                                FEvaluationAIDecisionResult& OutEvaluatedOption)
    PURE_VIRTUAL(UEvaluationAIEvaluationHelper::EvaluateAction, );

    // 从评估选项中选择最佳选项
    virtual const FEvaluationAIDecisionResult& SelectBestAction(UEvaluationAIDecisionComponent* InOwner,
                                                                const UEvaluationWorldContext* InWorldContext,
                                                                const TArray<FEvaluationAIDecisionResult>& Options)
    PURE_VIRTUAL(UEvaluationAIEvaluationHelper::SelectBestAction, return FEvaluationAIDecisionResult::Invalid;);
}; 