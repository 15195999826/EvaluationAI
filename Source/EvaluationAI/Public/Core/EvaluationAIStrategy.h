// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIStrategy.generated.h"


class UEvaluationAIDecisionComponent;

/**
 * 策略基类 - 提供特定类型的行动选项生成和评估
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class EVALUATIONAI_API UEvaluationAIStrategy : public UObject
{
    GENERATED_BODY()
    
public:
    // UEvaluationAIStrategy();
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    FGameplayTag StrategyType;
    /**
     * 负责生成一个AI所有可能的行动选项
     * @param InOwner 
     * @param InWorldContext 
     * @return 
     */
    virtual TArray<FEvaluationAIDecisionResult> GenerateOptionsForAI(
    const UEvaluationAIDecisionComponent* InOwner, const UEvaluationWorldContext* InWorldContext)
    PURE_VIRTUAL(UEvaluationAIStrategy::GenerateOptionsForAI, return TArray<FEvaluationAIDecisionResult>(););
    

    
//     // 初始化策略
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual void Initialize(UEvaluationAIDecisionComponent* InDecisionComponent);
//     
//     // 评估此策略在当前情境的价值
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual float EvaluateValue();
//     
//     // 生成此策略对应的行动选项
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual TArray<FActionOption> GenerateOptions();
//     
//     // 获取策略类型
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual EStrategyType GetStrategyType() const;
//     
//     // 获取决策组件
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     UEvaluationAIDecisionComponent* GetDecisionComponent() const { return DecisionComponent; }
//     
//     // 获取策略权重
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     float GetStrategyWeight() const;
//     
// protected:
//     // 决策组件引用
//     UPROPERTY()
//     UEvaluationAIDecisionComponent* DecisionComponent;
//     
//     // 策略类型，子类必须覆盖
//     UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Strategy")
//     EStrategyType StrategyType;
//     
//     // 基础评分修正
//     UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Strategy")
//     float BaseScoreModifier;
//     
//     // 获取所有者Actor
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     AActor* GetOwningActor() const;
//     
//     // 评估结束回合选项
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual FActionOption EvaluateEndTurn();
//     
//     // 评估等待回合选项
//     UFUNCTION(BlueprintCallable, Category = "AI|Strategy")
//     virtual FActionOption EvaluateWaitTurn();
};