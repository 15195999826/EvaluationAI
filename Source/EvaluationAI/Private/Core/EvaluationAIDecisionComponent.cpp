#include "Core/EvaluationAIDecisionComponent.h"
#include "Core/EvaluationAIDecisionSystem.h"
#include "Core/EvaluationAIEvaluationHelper.h"
#include "Core/EvaluationAISettings.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

UEvaluationAIDecisionComponent::UEvaluationAIDecisionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    
    // 从设置中读取是否启用调试日志
    if (const UEvaluationAISettings* Settings = GetDefault<UEvaluationAISettings>())
    {
        bEnableDebugLogging = Settings->bEnableDebugLogging;
        bAllowTeamDecision = Settings->bEnableTeamDecision;
    }
    else
    {
        bEnableDebugLogging = false;
        bAllowTeamDecision = true;
    }
}

void UEvaluationAIDecisionComponent::InitializeComponent()
{
    Super::InitializeComponent();
}

void UEvaluationAIDecisionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UEvaluationAIDecisionComponent::SetEvaluationTeamID(int32 NewTeamID)
{
    EvaluationTeamID = NewTeamID;
}