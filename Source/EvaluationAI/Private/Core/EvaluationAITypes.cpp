#include "Core/EvaluationAITypes.h"

#include "Core/EvaluationAIStrategy.h"

// 定义FEvaluationAIDecisionResult 的 Invalid常量
const FEvaluationAIDecisionResult FEvaluationAIDecisionResult::Invalid{};

const FEvaluationAITeamDecisionResult FEvaluationAITeamDecisionResult::Invalid{};

FString FEvaluationAIDecisionResult::ToString() const
{
	// 创建一个字符串构建器以提高性能
	FStringBuilderBase Builder;
    
	// 添加决策行为标签
	Builder.Appendf(TEXT("决策行为: %s, 得分: %.2f"), *DecisionAction.ToString(), Score);
    
	// 添加字符串数据
	if (StrDataMap.Num() > 0)
	{
		Builder.Append(TEXT("\n字符串数据:"));
		for (const auto& Pair : StrDataMap)
		{
			Builder.Appendf(TEXT("\n  %s: %s"), *Pair.Key.ToString(), *Pair.Value);
		}
	}
    
	// 添加整数数据
	if (IntDataMap.Num() > 0)
	{
		Builder.Append(TEXT("\n整数数据:"));
		for (const auto& Pair : IntDataMap)
		{
			Builder.Appendf(TEXT("\n  %s: %d"), *Pair.Key.ToString(), Pair.Value);
		}
	}
    
	// 添加浮点数据
	if (FloatDataMap.Num() > 0)
	{
		Builder.Append(TEXT("\n浮点数据:"));
		for (const auto& Pair : FloatDataMap)
		{
			Builder.Appendf(TEXT("\n  %s: %.2f"), *Pair.Key.ToString(), Pair.Value);
		}
	}
    
	// 添加点数据
	if (IntPointDataMap.Num() > 0)
	{
		Builder.Append(TEXT("\n坐标数据:"));
		for (const auto& Pair : IntPointDataMap)
		{
			Builder.Appendf(TEXT("\n  %s: (%d, %d)"), *Pair.Key.ToString(), Pair.Value.X, Pair.Value.Y);
		}
	}
    
	return Builder.ToString();
}

void FEvaluationAIStrategyConfig::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
#if WITH_EDITOR
	// 检查特定属性是否变化
	if (OldValue != StrategyClass)
	{
		UE_LOG(LogTemp, Log, TEXT("行 %s 中的 StrategyClass 从 %s 变为 %s"), 
			*InRowName.ToString(), OldValue==nullptr? TEXT("nullptr") : *OldValue->GetName(), StrategyClass ? *StrategyClass->GetName() : TEXT("nullptr"));
            
		// 更新旧值
		OldValue = StrategyClass;
	}
	
	
	if (!StrategyClass)
	{
		FinalAlgorithmMap.Empty();
		return;
	}
	
	// 获取策略类的默认对象
	UEvaluationAIStrategy* DefaultStrategy = Cast<UEvaluationAIStrategy>(StrategyClass->GetDefaultObject());
	auto DesiredFinalAlgorithmMap = DefaultStrategy->GetFinalAlgorithmNames();
	if (DesiredFinalAlgorithmMap.Num() == 0)
	{
		FinalAlgorithmMap.Empty();
		return;
	}

	// 移除那些不在DesiredFinalAlgorithmMap中的键
	for (const auto& KeyName : FinalAlgorithmMap)
	{
		if (!DesiredFinalAlgorithmMap.Contains(KeyName.Key))
		{
			// 如果不在DesiredFinalAlgorithmMap中，则从FinalAlgorithmMap中移除
			FinalAlgorithmMap.Remove(KeyName.Key);
		}
	}

	for (const auto& KeyName : DesiredFinalAlgorithmMap)
	{
		// 检查FinalAlgorithmMap中是否已经存在这个键
		if (!FinalAlgorithmMap.Contains(KeyName))
		{
			// 如果不存在，则添加新的键值对
			FinalAlgorithmMap.Add(KeyName, nullptr);
		}
	}
#endif // WITH_EDITOR
}
