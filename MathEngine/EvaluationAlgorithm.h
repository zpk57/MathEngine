#pragma once

#include "CalculationContext.h"
#include "../Data/Definitions.h"

// EvaluationAlgorithm contains algorithms.

class EvaluationAlgorithm
{
public:
	static void evaluateAll(const CalculationContext& context);

	static void evaluateCell(const CalculationContext& context, const CellPtr& cell);
};
