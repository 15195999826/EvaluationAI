// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIDecisionSystem.generated.h"

class UEvaluationAIEvaluationHelper;
class UEvaluationAIDecisionComponent;

/**
 * AI决策系统 - 提供基于评估的AI决策框架的核心入口点
 * 
 * 这个系统是EvaluationAI框架的核心，负责协调个体和团队AI决策。
 * 它保存基本的团队数据，并根据情况决定使用团队决策还是个体决策。
 * 
 * 主要职责 (Main Responsibilities):
 * - 管理AI决策流程 (Manages AI decision process)
 *   - 处理同步和异步决策请求
 *   - 维护决策生命周期
 *   - 确保决策结果的一致性
 * 
 * - 协调团队决策 (Coordinates team decisions)
 *   - 管理团队成员之间的协同
 *   - 处理团队级别的策略选择
 *   - 优化团队整体决策效果
 * 
 * - 存储团队成员关系 (Maintains team relationships)
 *   - 跟踪AI组件的团队归属
 *   - 管理团队上下文数据
 *   - 支持动态团队成员变更
 * 
 * - 提供决策计算功能 (Provides decision computation)
 *   - 评估可用行动方案
 *   - 计算决策权重和优先级
 *   - 生成最终决策结果
 * 
 * 关键特性 (Key Features):
 * - 支持团队和个体两种决策模式
 * - 提供可扩展的策略系统
 * - 内置评估助手功能
 * - 支持同步批量决策处理
 * 
 * 使用方式 (Usage):
 *
 * C++准备： 创建项目本身的WorldContext/策略类/评估器， 自行实现这些类的逻辑即可
 * 
 * 1. 通过GetWorld()->GetSubsystem<UEvaluationAIDecisionSystem>()获取实例
 *    (Get instance via GetWorld()->GetSubsystem<UEvaluationAIDecisionSystem>())
 * 
 * 2. 注册AI到团队（可选）
 *    (Register AI to team - optional)
 *    示例 (Example):
 *    DecisionSystem->RegisterAI(AIComponent, TeamID);
 * 
 * 3. 通过MakeDecision方法获取决策结果
 *    (Get decision results via MakeDecision methods)
 *    - 个体决策：MakeIndividualDecision()
 *    - 团队决策：MakeTeamDecision()
 * 
 * 配置建议 (Configuration Tips):
 * - 根据游戏需求选择合适的决策模式
 * - 合理设置团队规模，避免过大团队影响性能
 * - 适当调整评估参数以平衡决策质量和性能
 */
UCLASS(Abstract)
class EVALUATIONAI_API UEvaluationAIDecisionSystem : public UWorldSubsystem
{
    GENERATED_BODY()

    inline static int32 EmptyTeamID = -1;

protected:
    UPROPERTY()
    TArray<TObjectPtr<UEvaluationAIDecisionComponent>> RegisteredAIs;
    
    // 团队上下文映射
    UPROPERTY()
    TMap<int32, TObjectPtr<UEvaluationTeamContext>> TeamContexts;

public:
    // 清理系统
    virtual void Deinitialize() override;
    
    /**
     * 注册AI
     * @param Component 
     * @param TeamID 
     */
    void RegisterAI(UEvaluationAIDecisionComponent* Component, int32 TeamID = EmptyTeamID);
    
    // 从团队中注销
    void UnregisterAI(UEvaluationAIDecisionComponent* Component);

    const TArray<TObjectPtr<UEvaluationAIDecisionComponent>>& GetRegisteredAIs() const { return RegisteredAIs; }

    const TMap<int32, TObjectPtr<UEvaluationTeamContext>>& GetTeamContexts();

 
    /**
     * 同步AI思考， 适用于那些在回合一开始，就确定所有AI的决策的情况
     */
    void SyncAIThink();

    virtual void StartSyncAIThink() PURE_VIRTUAL();
    virtual void EndSyncAIThink() PURE_VIRTUAL();
    
    // 团队级决策
    const FEvaluationAITeamDecisionResult& MakeTeamDecision(int32 InTeamID);

    // 个体级决策
    FEvaluationAIDecisionResult MakeIndividualDecision(UEvaluationAIDecisionComponent* Component);

protected:
    // 为特定团队设置上下文
    UFUNCTION(BlueprintCallable, Category = "AI|Team")
    void SetTeamContext(int32 TeamID, UEvaluationTeamContext* Context);
    
    // 获取团队上下文
    UFUNCTION(BlueprintCallable, Category = "AI|Team")
    UEvaluationTeamContext* GetTeamContext(int32 TeamID);

    // Todo: 可以
    virtual TObjectPtr<UEvaluationAIStrategy> GetDecisionStrategy(TSubclassOf<UEvaluationAIStrategy> StrategyClass, const FName& CustomData) PURE_VIRTUAL(UEvaluationAIDecisionSystem::GetDecisionStrategy, return nullptr;);

    // 评估算法相关
protected:

    // 评估所有选项
    void EvaluateAllActions(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass,
                                    const UEvaluationAIDecisionComponent* InOwner,
                                    TArray<FEvaluationAIDecisionResult>& OutOptions);

    // 评估单个行动选项
    void EvaluateAction(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass,
                                const UEvaluationAIDecisionComponent* InOwner,
                                FEvaluationAIDecisionResult& OutEvaluatedOption);

    // 从评估选项中选择最佳选项
    const FEvaluationAIDecisionResult& SelectBestAction(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass,
                                                                UEvaluationAIDecisionComponent* InOwner,
                                                                const TArray<FEvaluationAIDecisionResult>& Options);
    
    virtual TObjectPtr<UEvaluationAlgorithm> GetAlgorithm(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass) PURE_VIRTUAL(UEvaluationAIDecisionSystem::GetAlgorithm, return nullptr;);
}; 