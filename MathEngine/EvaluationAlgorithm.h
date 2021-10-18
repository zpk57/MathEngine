#pragma once

#include "CalculationContext.h"
#include "../Data/Definitions.h"

// EvaluationAlgorithm contains algorithms.

class EvaluationAlgorithm
{
public:
	static void evaluateAllLinear(CalculationContext& context);

	static void evaluateCellLinear(CalculationContext& context, const CellPtr& cell);

	static void evaluateAllSplitted(CalculationContext& context);

	static void evaluateCellSplitted(CalculationContext& context, const CellPtr& cell);
};
