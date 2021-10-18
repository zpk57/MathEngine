#include "MathEngine.h"

#include "CalculationContext.h"
#include "EvaluationAlgorithm.h"


void MathEngine::evaluateAll(const DocumentPtr& doc, size_t threads)
{
	CalculationContext context(doc);

//	for (size_t i = 0; i < threads; ++i)
//		context.schedule(std::bind(&EvaluationAlgorithm::evaluateAllLinear, std::placeholders::_1));

	context.schedule(std::bind(&EvaluationAlgorithm::evaluateAllSplitted, std::placeholders::_1));

	context.calculate(threads);
}
