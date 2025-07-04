// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EvaluationAITypes.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "EvaluationAISettings.generated.h"

class UEvaluationAIStrategy;
class UEvaluationTeamContext;
class UEvaluationAIEvaluationHelper;

/**
 * EvaluationAI插件全局设置
 * 
 * 这个类定义了EvaluationAI插件的全局配置选项，
 * 可以在Project Settings中编辑这些设置。
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Evaluation AI"))
class EVALUATIONAI_API UEvaluationAISettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    virtual FName GetCategoryName() const override;
    
    // 可用的AI Action, 使用GameplayTag
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Evaluation", meta=(DisplayName = "可用的Actions"))
    TArray<FGameplayTag> Actions;

    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Team", meta=(DisplayName = "团队上下文类"))
    TSubclassOf<UEvaluationTeamContext> TeamContextClass;
    
    // 是否启用团队决策
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Team")
    bool bEnableTeamDecision = true;
    
    // 是否启用调试日志
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Debug")
    bool bEnableDebugLogging = false;
    
    // 是否在编辑器中显示AI决策视觉化
    UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Debug")
    bool bEnableDecisionVisualization = false;
}; 