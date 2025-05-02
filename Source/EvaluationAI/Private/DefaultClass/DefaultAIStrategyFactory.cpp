// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultClass/DefaultAIStrategyFactory.h"

#include "Core/EvaluationAIStrategy.h"

UEvaluationAIStrategy* UDefaultAIStrategyFactory::CreateStrategy(UObject* Outer,
                                                                 const FStrategyConfigData& InStrategyConfig)
{
	// 创建策略对象
	UEvaluationAIStrategy* NewStrategy = NewObject<UEvaluationAIStrategy>(Outer, InStrategyConfig.StrategyClass);
    
	// 初始化策略对象
	if (NewStrategy)
	{
		InitializeStrategy(NewStrategy, InStrategyConfig);
	}
    
	return NewStrategy;
}

void UDefaultAIStrategyFactory::InitializeStrategy(UEvaluationAIStrategy* NewStrategy,
	const FStrategyConfigData& InStrategyConfig)
{
	NewStrategy->StrategyType = InStrategyConfig.StrategyType;
}

