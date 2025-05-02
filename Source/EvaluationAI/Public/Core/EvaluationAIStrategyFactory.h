// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EvaluationAITypes.h"
#include "UObject/NoExportTypes.h"
#include "EvaluationAIStrategyFactory.generated.h"

class UEvaluationAIStrategy;

/**
 * AI策略工厂基类 - 负责创建AI策略对象
 * 
 * 这个类允许项目自定义AI策略对象的创建方式。
 * 项目可以继承这个类来实现自己的工厂类，以支持更复杂的策略对象创建逻辑。
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class EVALUATIONAI_API UEvaluationAIStrategyFactory : public UObject
{
    GENERATED_BODY()
    
public:
    /**
     * 创建策略对象
     * @param Outer 外部对象
     * @param InStrategyConfig
     * @return 创建的策略对象
     */
    virtual UEvaluationAIStrategy* CreateStrategy(UObject* Outer, const FStrategyConfigData& InStrategyConfig) PURE_VIRTUAL(UEvaluationAIStrategyFactory::CreateStrategy, return nullptr; );

protected:
    /**
     * 初始化新创建的策略对象
     * 派生类可以重写这个函数来添加额外的初始化逻辑
     * @param NewStrategy 新创建的策略对象
     * @param InStrategyConfig
     */
    virtual void InitializeStrategy(UEvaluationAIStrategy* NewStrategy, const FStrategyConfigData& InStrategyConfig) PURE_VIRTUAL();
}; 