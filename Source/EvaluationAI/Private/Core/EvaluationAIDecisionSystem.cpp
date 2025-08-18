// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/EvaluationAIDecisionSystem.h"

#include "EvaluationAI.h"
#include "Core/EvaluationAIDecisionComponent.h"
#include "Core/EvaluationAISettings.h"
#include "Core/EvaluationAIStrategy.h"
#include "Core/EvaluationAlgorithm.h"

void UEvaluationAIDecisionSystem::Deinitialize()
{
    // 清理团队上下文
    TeamContexts.Empty();
    
    Super::Deinitialize();
}

void UEvaluationAIDecisionSystem::RegisterAI(UEvaluationAIDecisionComponent* Component, int32 TeamID)
{
    check(!RegisteredAIs.Contains(Component))

    RegisteredAIs.Add(Component);
    
    if (TeamID == EmptyTeamID)
    {
        return;
    }

    // Todo: 并未提供修改队伍的功能， 只允许注册一次
    
    // 添加到新团队
    if (!TeamContexts.Contains(TeamID))
    {
        // auto TeamContextClass = GetDefault<UEvaluationAISettings>()->TeamContextClass;
        // auto NewTeamContext = NewObject<UEvaluationTeamContext>(this, TeamContextClass);
        // TeamContexts.Add(TeamID, NewTeamContext);
    }
    
    // TeamContexts[TeamID]->TeamMembers.Add(Component);
    
    // 更新组件的团队ID
    // Component->SetEvaluationTeamID(TeamID);
}

void UEvaluationAIDecisionSystem::UnregisterAI(UEvaluationAIDecisionComponent* Component)
{
    check(RegisteredAIs.Contains(Component))

    RegisteredAIs.Remove(Component);
    
    auto TeamID = Component->GetEvaluationTeamID();
    if (TeamID == EmptyTeamID)
    {
        return;
    }

    if (TeamContexts.Contains(TeamID))
    {
        TeamContexts[TeamID]->TeamMembers.Remove(Component);

        // 检查当前队伍是否为空， 是的话，移除队伍
        if (TeamContexts[TeamID]->TeamMembers.Num() == 0)
        {
            TeamContexts.Remove(TeamID);
        }
    }
    
    // 重置组件的团队ID
    Component->SetEvaluationTeamID(EmptyTeamID);
    
}

const TMap<int32, TObjectPtr<UEvaluationTeamContext>>& UEvaluationAIDecisionSystem::GetTeamContexts()
{
    return TeamContexts;
}

void UEvaluationAIDecisionSystem::SyncAIThink()
{
    StartSyncAIThink();
    TMap<int32, FEvaluationAITeamDecisionResult> TeamDecisions;
    
    // 先进行队伍决策
    for (auto& TeamPair : TeamContexts)
    {
        auto TeamID = TeamPair.Key;
        // 进行团队决策
        TeamDecisions.Add(TeamID, MakeTeamDecision(TeamID));
    }

    // 再进行个人决策
    for (auto AI : RegisteredAIs)
    {
        // Todo: 获取自己在队伍决策中的结果， 然后根据自身情况决定使用队伍决策还是个人决策 
        // auto TeamID = AI->GetEvaluationTeamID();
   
        // 进行个人决策
        FEvaluationAIDecisionResult Decision = MakeIndividualDecision(AI);
        // 保存个人最终决策到组件中， 留给项目本身决定如何执行
        AI->SetDecision(Decision);
    }

    EndSyncAIThink();
}

const FEvaluationAITeamDecisionResult& UEvaluationAIDecisionSystem::MakeTeamDecision(int32 InTeamID)
{
    // FEvaluationAITeamDecisionResult Ret;

    // Todo: 调用评估系统函数， 并且考虑世界信息和团队合作关系， 复杂计算评分
    // 这个部分的内容只调用函数， 具体的实现交给项目自身实现的评估辅助函数实现

    return FEvaluationAITeamDecisionResult::Invalid;
}

FEvaluationAIDecisionResult UEvaluationAIDecisionSystem::MakeIndividualDecision(UEvaluationAIDecisionComponent* Component)
{
    auto StrategyConfig = Component->GetAIStrategyConfig();
    auto DecisionStrategy = GetDecisionStrategy(StrategyConfig->StrategyClass, StrategyConfig->CustomData);

    if (!DecisionStrategy)
    {
        UE_LOG(LogEvaluationAI, Error, TEXT("[MakeIndividualDecision]没有找到对应的决策策略实例: %s"), StrategyConfig->StrategyClass == nullptr? TEXT("nullptr") : *StrategyConfig->StrategyClass->GetName());
        return FEvaluationAIDecisionResult::Invalid;
    }
    
    // 1. 根据世界状态等数据， 运行一系列状态判断，获取当前使用的评估算法类
    auto EvaluationAlgorithmName = DecisionStrategy->RunStrategy(Component);
    UE_LOG(LogEvaluationAI, Verbose, TEXT("[角色%s]当前使用的评估算法: %s"), *Component->GetOwner()->GetName(), *EvaluationAlgorithmName.ToString());
    TSubclassOf<UEvaluationAlgorithm> EvaluationAlgorithmClass;
    if (StrategyConfig->FinalAlgorithmMap.Contains(EvaluationAlgorithmName))
    {
        EvaluationAlgorithmClass = StrategyConfig->FinalAlgorithmMap[EvaluationAlgorithmName];
    }
    else
    {
        UE_LOG(LogEvaluationAI, Error, TEXT("[MakeIndividualDecision]没有找到对应的评估算法类: %s"), *EvaluationAlgorithmName.ToString());
        return FEvaluationAIDecisionResult::Invalid;
    }

    // 2. 生成行动选项
    TArray<FEvaluationAIDecisionResult> Options = DecisionStrategy->GenerateOptionsForAI(Component);
    
    // 如果没有选项，返回空决策
    if (Options.Num() == 0)
    {
        return FEvaluationAIDecisionResult::Invalid;
    }
    
    // 3. 评估所有选项
    EvaluateAllActions(EvaluationAlgorithmClass, Component, Options);
    
    // 4. 选择最佳选项
    const auto& BestAction = SelectBestAction(EvaluationAlgorithmClass, Component, Options);
    return BestAction;
}


void UEvaluationAIDecisionSystem::SetTeamContext(int32 TeamID, UEvaluationTeamContext* Context)
{
    if (TeamID >= 0 && Context)
    {
        TeamContexts.Add(TeamID, Context);
        Context->TeamID = TeamID;
    }
}

UEvaluationTeamContext* UEvaluationAIDecisionSystem::GetTeamContext(int32 TeamID)
{
    return TeamContexts.FindRef(TeamID);
}

void UEvaluationAIDecisionSystem::EvaluateAllActions(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass,
    const UEvaluationAIDecisionComponent* InOwner, TArray<FEvaluationAIDecisionResult>& OutOptions)
{
    GetAlgorithm(AlgorithmClass)->EvaluateAllActions(InOwner, OutOptions);
}

void UEvaluationAIDecisionSystem::EvaluateAction(TSubclassOf<UEvaluationAlgorithm> AlgorithmClass,
    const UEvaluationAIDecisionComponent* InOwner, FEvaluationAIDecisionResult& OutEvaluatedOption)
{
    GetAlgorithm(AlgorithmClass)->EvaluateAction(InOwner, OutEvaluatedOption);
}

const FEvaluationAIDecisionResult& UEvaluationAIDecisionSystem::SelectBestAction(
    TSubclassOf<UEvaluationAlgorithm> AlgorithmClass, UEvaluationAIDecisionComponent* InOwner,
    const TArray<FEvaluationAIDecisionResult>& Options)
{
    return GetAlgorithm(AlgorithmClass)->SelectBestAction(InOwner, Options);
}
