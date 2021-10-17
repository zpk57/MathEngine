#include "MathEngine.h"

#include "CalculationContext.h"
#include "EvaluationAlgorithm.h"


void MathEngine::evaluateAll(const DocumentPtr& doc, size_t threads)
{
	// Just creating of "evaluateAll" tasks and execute it with same num threads.

	CalculationContext context(doc);

	for (size_t i = 0; i < threads; ++i)
		context.schedule(std::bind(&EvaluationAlgorithm::evaluateAll, std::placeholders::_1));

	context.calculate(threads);
}
