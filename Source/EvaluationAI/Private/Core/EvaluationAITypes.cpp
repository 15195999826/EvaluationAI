#include "Core/EvaluationAITypes.h"

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
