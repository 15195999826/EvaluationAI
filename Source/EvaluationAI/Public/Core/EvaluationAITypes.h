// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UObject/Interface.h"
#include "EvaluationAITypes.generated.h"

class UEvaluationAlgorithm;
class UEvaluationAIStrategy;
class UEvaluationAIDecisionComponent;
/**
 * AI决策结果数据
 */
USTRUCT()
struct EVALUATIONAI_API FEvaluationAIDecisionResult
{
    GENERATED_BODY()

    FEvaluationAIDecisionResult(){}
    
    // 声明一个Invalid 的常量
    static const FEvaluationAIDecisionResult Invalid;
    
    // 决策结果行为
    UPROPERTY()
    FGameplayTag DecisionAction = FGameplayTag::EmptyTag;

    // 决策结果的具体数据， 项目本身自行定义Key Value, 决定各个值代表什么含义
    UPROPERTY()
    TMap<FName, FString> StrDataMap;

    UPROPERTY()
    TMap<FName, int32> IntDataMap;

    UPROPERTY()
    TMap<FName, float> FloatDataMap;

    UPROPERTY()
    TMap<FName, FIntPoint> IntPointDataMap;
    
    UPROPERTY()
    TMap<FName, FVector> VectorDataMap;
    
    // Todo: 增加一条得分调整系数， 用于控制AI选择结果的倾向
    
    // 得分
    UPROPERTY()
    float Score = 0.f;

    FString ToString() const;
};

USTRUCT()
struct FEvaluationAITeamDecisionResult
{
    GENERATED_BODY()

    FEvaluationAITeamDecisionResult(){}
    
    static const FEvaluationAITeamDecisionResult Invalid;

    UPROPERTY()
    TMap<TObjectPtr<UEvaluationAIDecisionComponent>, FEvaluationAIDecisionResult> TeamDecisionResultMap;
};


/**
 * 团队上下文基类 - 用于传递团队相关的信息
 * 实际项目应该继承此类并添加特定的数据结构
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class EVALUATIONAI_API UEvaluationTeamContext : public UObject
{
    GENERATED_BODY()
    
public:
    // 团队ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    int32 TeamID = -1;
    
    // 团队成员
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    TArray<TObjectPtr<UEvaluationAIDecisionComponent>> TeamMembers;
};

/**
 * 定义策略
 */
USTRUCT(BlueprintType)
struct FEvaluationAIStrategyConfig : public FTableRowBase
{
    GENERATED_BODY()

    FEvaluationAIStrategyConfig(){}
    
    // 存储旧值以便比较
    UPROPERTY(Transient)
    mutable TSubclassOf<UEvaluationAIStrategy> OldValue;

    /**
     * 策略应该是很具体的， 除非非常特殊的AI需要进行额外创建新的， 其它情况下一般通用的比如进攻、防御、支援等策略就可以了
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UEvaluationAIStrategy> StrategyClass;

    // 预留CustomData, 目前是为了使用TS创建StrategyClass的可能性
    UPROPERTY(EditAnywhere)
    FName CustomData = NAME_None;
    
    UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadOnly, meta=(DisplayName = "评分算法", ReadOnlyKeys))
    TMap<FName, TSubclassOf<UEvaluationAlgorithm>> FinalAlgorithmMap;

    virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;
};