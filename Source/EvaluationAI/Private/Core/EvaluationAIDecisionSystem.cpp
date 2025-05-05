// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/EvaluationAIDecisionSystem.h"
#include "Core/EvaluationAIDecisionComponent.h"
#include "Core/EvaluationAIEvaluationHelper.h"
#include "Core/EvaluationAISettings.h"
#include "Core/EvaluationAIStrategy.h"
#include "Core/EvaluationAIStrategyFactory.h"
#include "DefaultClass/DefaultAIEvaluationHelper.h"
#include "DefaultClass/DefaultAIStrategyFactory.h"

void UEvaluationAIDecisionSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    auto Settings = GetDefault<UEvaluationAISettings>();
    
    // 创建评估助手
    auto HelperClass = Settings->DefaultEvaluationHelperClass;
    
    if (HelperClass == nullptr)
    {
        HelperClass = UDefaultAIEvaluationHelper::StaticClass();
    }
    
    EvaluationHelper = NewObject<UEvaluationAIEvaluationHelper>(this, HelperClass);
    EvaluationHelper->InitHelper();
    // 创建策略工厂
    auto FactoryClass = Settings->StrategyFactoryClass;
    
    if (!FactoryClass)
    {
        FactoryClass = UDefaultAIStrategyFactory::StaticClass();
    }

    // 使用工厂类创建策略对象
    auto StrategyFactory = NewObject<UEvaluationAIStrategyFactory>(this, FactoryClass);
    for (const auto& StrategyConfig : Settings->StrategyConfigs)
    {
        auto NewStrategy = StrategyFactory->CreateStrategy(this, StrategyConfig);
        if (NewStrategy)
        {
            DecisionStrategyMap.Add(NewStrategy->StrategyType, NewStrategy);
        }
    }
}

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
        auto TeamContextClass = GetDefault<UEvaluationAISettings>()->TeamContextClass;
        auto NewTeamContext = NewObject<UEvaluationTeamContext>(this, TeamContextClass);
        TeamContexts.Add(TeamID, NewTeamContext);
    }
    
    TeamContexts[TeamID]->TeamMembers.Add(Component);
    
    // 更新组件的团队ID
    Component->SetEvaluationTeamID(TeamID);
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
    auto WorldContext = EvaluationHelper->MakeWorldContext();

    TMap<int32, FEvaluationAITeamDecisionResult> TeamDecisions;
    // 先进行队伍决策
    for (auto& TeamPair : TeamContexts)
    {
        auto TeamID = TeamPair.Key;
        // 进行团队决策
        TeamDecisions.Add(TeamID, MakeTeamDecision(TeamID, WorldContext));
    }

    // 再进行个人决策
    for (auto AI : RegisteredAIs)
    {
        // Todo: 获取自己在队伍决策中的结果， 然后根据自身情况决定使用队伍决策还是个人决策 
        // auto TeamID = AI->GetEvaluationTeamID();
   
        // 进行个人决策
        FEvaluationAIDecisionResult Decision = MakeIndividualDecision(AI, WorldContext);
        // 保存个人最终决策到组件中， 留给项目本身决定如何执行
        AI->SetDecision(Decision);
    }
}

const FEvaluationAITeamDecisionResult& UEvaluationAIDecisionSystem::MakeTeamDecision(int32 InTeamID,
                                                                                     const UEvaluationWorldContext* InWorldContext)
{
    // FEvaluationAITeamDecisionResult Ret;

    // Todo: 调用评估系统函数， 并且考虑世界信息和团队合作关系， 复杂计算评分
    // 这个部分的内容只调用函数， 具体的实现交给项目自身实现的评估辅助函数实现

    return FEvaluationAITeamDecisionResult::Invalid;
}

FEvaluationAIDecisionResult UEvaluationAIDecisionSystem::MakeIndividualDecision(
    UEvaluationAIDecisionComponent* Component, const UEvaluationWorldContext* InWorldContext)
{
    auto StrategyType = Component->GetAIConfig().StrategyType;
    check(DecisionStrategyMap.Contains(StrategyType));
    // 1. 生成行动选项
    TArray<FEvaluationAIDecisionResult> Options = DecisionStrategyMap[StrategyType]->GenerateOptionsForAI(Component, InWorldContext);
    // 2. 评估所有选项
    // 如果没有选项，返回空决策
    if (Options.Num() == 0)
    {
        return FEvaluationAIDecisionResult::Invalid;
    }
    
    // 2. 评估所有选项
    EvaluationHelper->EvaluateAllActions(Component, InWorldContext, Options);
    
    // 3. 选择最佳选项
    const auto& BestAction = EvaluationHelper->SelectBestAction(Component, InWorldContext, Options);
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
