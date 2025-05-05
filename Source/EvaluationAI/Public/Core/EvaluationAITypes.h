// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "UObject/Interface.h"
#include "EvaluationAITypes.generated.h"

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

USTRUCT(BlueprintType)
struct FEvaluationAIConfig
{
    GENERATED_BODY()

    FEvaluationAIConfig(){}

    /**
     * 策略应该是很具体的， 除非非常特殊的AI需要进行额外创建新的， 其它情况下一般通用的比如进攻、防御、支援等策略就可以了
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag StrategyType;

    /**
     * 可选行为， 如，视具体项目， 可能有移动、防御、使用技能等（有的项目也会把这些东西都定义成技能）
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FGameplayTag> AvailableActions;
};

/**
 * 策略配置数据
 */
USTRUCT(BlueprintType)
struct FStrategyConfigData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag StrategyType;
    // 策略类
    UPROPERTY(EditAnywhere, Category = "Strategy")
    TSubclassOf<UEvaluationAIStrategy> StrategyClass;

    // 自定义数据
    UPROPERTY(EditAnywhere, Category = "Strategy")
    FName CustomData = NAME_None;
};

/**
 * 决策世界数据 - 包含做出决策所需的所有上下文信息
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class EVALUATIONAI_API UEvaluationWorldContext : public UObject
{
    GENERATED_BODY()
    
public:
 
};