// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIDecisionComponent.generated.h"
class UEvaluationAIStrategy;
class UEvaluationAIDecisionSystem;
/**
 * AI决策组件 - 角色的AI决策执行单元
 * 
 * 这个组件是EvaluationAI框架中连接角色与决策系统的桥梁，负责执行具体的AI行为。
 * 
 * 主要职责 (Main Responsibilities):
 * 1. 提供配置数据
 * 2. 保存决策结果
 */
UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class EVALUATIONAI_API UEvaluationAIDecisionComponent : public UActorComponent
{
    GENERATED_BODY()

    
    friend UEvaluationAIDecisionSystem;
public:    
    // 设置该组件的默认值
    UEvaluationAIDecisionComponent();

    // 当组件被创建时调用
    virtual void InitializeComponent() override;
    
    // 组件开始游戏时调用
    virtual void BeginPlay() override;

    // 获取AI配置
    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    const FEvaluationAIConfig& GetAIConfig() const { return AIConfig; }
    
    // 设置团队ID
    UFUNCTION(BlueprintCallable, Category = "AI|Team")
    void SetEvaluationTeamID(int32 NewTeamID);
    
    // 获取团队ID
    UFUNCTION(BlueprintCallable, Category = "AI|Team")
    int32 GetEvaluationTeamID() const { return EvaluationTeamID; }

    void SetDecision(const FEvaluationAIDecisionResult& InDecision)
    {
        DecisionResult = InDecision;
    }

    const FEvaluationAIDecisionResult& GetDecision() const { return DecisionResult; }

protected:
    // AI配置数据资产
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Configuration")
    FEvaluationAIConfig AIConfig;
    
    // 是否启用调试日志
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Debug")
    bool bEnableDebugLogging;
    
    // 团队ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Team")
    int32 EvaluationTeamID = -1;
    
    // 是否允许团队决策
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Team")
    bool bAllowTeamDecision = true;
    
    FEvaluationAIDecisionResult DecisionResult;
}; 