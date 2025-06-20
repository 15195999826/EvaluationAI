// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIStrategy.generated.h"


class UEvaluationAIDecisionComponent;

/**
 * 策略基类 - 提供特定类型的行动选项生成
 * 内部实现一个简单的游戏状态判断， 决定最终使用哪个评分算法
 *
 */
UCLASS(Abstract)
class EVALUATIONAI_API UEvaluationAIStrategy : public UObject
{
    GENERATED_BODY()
    
public:
    // UEvaluationAIStrategy();
    /**
     * 通过状态判断， 决定最终使用的评分算法的标志; 算法类在AIConfig中获取
     */
    virtual const TArray<FName>& GetFinalAlgorithmNames()PURE_VIRTUAL(UEvaluationAIStrategy::GetFinalAlgorithmNames, static TArray<FName> FinalAlgorithmNames = {}; return FinalAlgorithmNames;);

    /**
     * 举例说明：
     * AI策略倾向：普通
     * 
     * 决策流程：
     * 1. 开始普通策略判断
     * 
     * 2. 判断是否进入战斗状态
     *    - 如果否 -> 检查是否听见敌音
     *      - 如果否 -> 【最终决策：闲置】
     *      - 如果是 -> 检查自身生命值
     * 
     * 3. 如果进入战斗状态 -> 判断是否发现敌人
     *    - 如果否 -> 检查最后一次受击时间
     *      - 如果>5回合 -> 【最终决策：闲置】
     *      - 如果≤5回合 -> 检查自身生命值
     *    - 如果是 -> 检查自身生命值
     * 
     * 4. 生命值判断（统一处理点）
     *    - 如果生命值≤35% -> 【最终决策：撤退】
     *    - 如果生命值>35% -> 【最终决策：进攻】
     * 
     * =====================================
     * 最终决策结果汇总：
     * • 【闲置】- 未发现威胁或长时间未受攻击
     * • 【撤退】- 生命值过低(≤35%)时的保命策略  
     * • 【进攻】- 生命值充足(>35%)时的主动攻击
     * =====================================
     * @return 最终决策结果
     */
    virtual FName RunStrategy(const UEvaluationAIDecisionComponent* InOwner) PURE_VIRTUAL(UEvaluationAIStrategy::RunStrategy, return NAME_None;);
    
    /**
     * 负责生成一个AI所有可能的行动选项
     * @param InOwner 
     * @return 
     */
    virtual TArray<FEvaluationAIDecisionResult> GenerateOptionsForAI(const UEvaluationAIDecisionComponent* InOwner)
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

#define DECLARE_AI_STRATEGY_ALGORITHMS(...) \
inline static TArray<FName> FinalAlgorithmNames = { __VA_ARGS__ }; \
virtual const TArray<FName>& GetFinalAlgorithmNames() override { return FinalAlgorithmNames; }