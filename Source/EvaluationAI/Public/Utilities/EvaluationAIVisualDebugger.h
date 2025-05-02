// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/EvaluationAITypes.h"
#include "EvaluationAIVisualDebugger.generated.h"

class UEvaluationAIDecisionComponent;

/**
 * 可视化调试工具 - 用于在编辑器和游戏中可视化显示AI决策过程
 */
UCLASS(BlueprintType)
class EVALUATIONAI_API UEvaluationAIVisualDebugger : public UObject
{
    GENERATED_BODY()
    
public:
//     UEvaluationAIVisualDebugger();
//     
//     // 初始化调试工具
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     virtual void Initialize(UEvaluationAIDecisionComponent* InDecisionComponent);
//     
//     // 显示行动选项
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     virtual void VisualizeActionOptions(const TArray<FActionOption>& Options);
//     
//     // 显示决策
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     virtual void VisualizeDecision(const FActionDecision& Decision);
//     
//     // 显示技能评估
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     virtual void VisualizeAbilityEvaluation(TSubclassOf<UGameplayAbility> AbilityClass, AActor* Target, float Score);
//     
//     // 显示战场态势
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     virtual void VisualizeBattlefieldSituation();
//     
//     // 获取决策组件
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     UEvaluationAIDecisionComponent* GetDecisionComponent() const { return DecisionComponent; }
//     
//     // 启用/禁用调试显示
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     void SetDebugEnabled(bool bEnabled) { bDebugEnabled = bEnabled; }
//     
//     // 检查调试是否启用
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     bool IsDebugEnabled() const { return bDebugEnabled; }
//     
//     // 设置调试持续时间
//     UFUNCTION(BlueprintCallable, Category = "AI|Debug")
//     void SetDebugDuration(float Duration) { DebugDuration = Duration; }
//
// protected:
//     // 决策组件引用
//     UPROPERTY()
//     UEvaluationAIDecisionComponent* DecisionComponent;
//     
//     // 是否启用调试
//     UPROPERTY()
//     bool bDebugEnabled;
//     
//     // 调试显示持续时间
//     UPROPERTY()
//     float DebugDuration;
//     
//     // 绘制箭头
//     UFUNCTION()
//     void DrawDebugArrow(const FVector& Start, const FVector& End, FColor Color, const FString& Label);
//     
//     // 绘制选项文本
//     UFUNCTION()
//     void DrawDebugText(const FVector& Location, const FString& Text, FColor Color);
}; 