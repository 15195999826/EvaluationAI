# EvaluationAI 框架

## 架构概述

EvaluationAI是一个为回合制游戏设计的基于评估函数（Evaluation Function）与GAS系统（Gameplay Ability System）集成的AI决策系统。该系统主要由以下组件构成：

1. **决策系统** - 负责管理和协调AI决策流程
2. **决策组件** - 负责单个角色的AI决策执行
3. **评估系统** - 负责评估不同行动选项的得分
4. **策略系统** - 负责生成和管理AI策略
5. **团队管理** - 负责协调团队级别的决策

整个AI决策过程遵循以下流程：
1. 根据场景选择使用个体决策或团队决策模式
2. 通过AI决策组件生成可能的行动选项
3. 使用评估系统计算每个选项的得分
4. 根据评估结果选择最佳行动执行

## 核心组件

### 1. 决策系统 (EvaluationAIDecisionSystem)

决策系统是整个框架的核心，主要职责包括：
- 管理AI决策流程
- 协调团队决策
- 存储团队成员关系
- 提供决策计算功能

关键特性：
- 支持团队和个体两种决策模式
- 提供可扩展的策略系统
- 内置评估助手功能
- 支持同步批量决策处理

### 2. 决策组件 (EvaluationAIDecisionComponent)

决策组件是连接角色与决策系统的桥梁，主要职责包括：
- 决策流程管理
- 策略管理
- 行为生成与执行
- 生命周期管理
- 游戏系统接口

配置选项：
- 决策间隔设置
- 策略优先级配置
- 团队ID设置
- 调试功能开关

### 3. 策略系统 (EvaluationAIStrategy)

策略系统负责定义和生成可能的行为选项：
- 评估策略在当前情境的价值
- 生成对应的行动选项
- 提供策略权重调整
- 支持策略组合和切换

### 4. 评估系统 (EvaluationAIEvaluationHelper)

评估系统负责计算行动选项的得分：
- 基础评分计算
- 策略权重调整
- 情境因素考虑
- 团队协同评估

## 插件目录结构

```
EvaluationAI/
├── Source/
│   ├── Core/                          # 核心AI决策系统
│   │   ├── EvaluationAIDecisionSystem.h    # 决策系统
│   │   ├── EvaluationAIDecisionComponent.h # 决策组件
│   │   ├── EvaluationAIStrategy.h          # 策略基类
│   │   ├── EvaluationAITypes.h             # 数据类型
│   │   ├── EvaluationAIEvaluationHelper.h  # 评估助手
│   │   └── EvaluationAISettings.h          # 系统设置
│   │
│   ├── Strategies/                    # 策略实现
│   │   ├── AttackStrategies/          # 攻击策略
│   │   ├── MovementStrategies/        # 移动策略 
│   │   └── SupportStrategies/         # 支援策略
│   │
│   └── Utilities/                     # 工具类
```

## 使用方法

1. **配置决策组件**:
   - 将EvaluationAIDecisionComponent添加到需要AI决策的角色
   - 配置AI参数和团队ID
   - 设置决策模式和调试选项

2. **获取决策系统**:
   ```cpp
   auto DecisionSystem = GetWorld()->GetSubsystem<UEvaluationAIDecisionSystem>();
   ```

3. **注册AI到团队**:
   ```cpp
   DecisionSystem->RegisterAI(AIComponent, TeamID);
   ```

4. **使用决策功能**:
   - 个体决策：`MakeIndividualDecision()`
   - 团队决策：`MakeTeamDecision()`

## 当前功能

### 1. 基础决策系统
- [x] 个体决策支持
- [x] 团队决策支持
- [x] 基础评估系统
- [x] 策略管理系统

### 2. 团队协作
- [x] 团队成员管理
- [x] 团队上下文共享
- [x] 基础协同决策

### 3. 配置系统
- [x] AI基础配置
- [x] 团队配置
- [x] 调试选项

## 未来规划

### 1. 战略层规划系统
- [ ] 分层策略系统
- [ ] 跨回合决策规划
- [ ] 目标优先级管理
- [ ] 资源分配优化

### 2. 高级评估系统
- [ ] 多维度评估模型
- [ ] 动态权重调整
- [ ] 历史数据分析
- [ ] 对手模式识别

### 3. 性能优化
- [ ] 多线程决策计算
- [ ] 评估缓存机制
- [ ] 决策树优化
- [ ] 批量处理优化

### 4. 调试工具
- [ ] 可视化决策过程
- [ ] 性能分析工具
- [ ] 决策日志系统
- [ ] 策略测试工具

## 注意事项

1. **性能考虑**:
   - 控制决策频率
   - 优化策略数量
   - 合理使用团队决策

2. **扩展建议**:
   - 遵循策略接口规范
   - 注意评估系统扩展
   - 保持向后兼容性

3. **调试提示**:
   - 使用内置日志系统
   - 合理配置调试选项
   - 注意性能监控 