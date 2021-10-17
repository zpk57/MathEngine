#include "EvaluationAlgorithm.h"

#include "../Data/Cell.h"
#include "../Data/Document.h"
#include "../Data/IFormula.h"

void EvaluationAlgorithm::evaluateAll(const CalculationContext& context)
{	
	for (const auto& cellIt : context.document()->raw())
	{
		const auto& cell = cellIt.second;

		if (cell->isResolved())
			continue; // Fast skip for resolved cells.

		if (!cell->getChildren().raw().empty())
			continue; // Do not start from dependent cells.

		const auto& edges = cell->getDependents().raw();
	}
}

void EvaluationAlgorithm::evaluateCell(const CalculationContext& context, const CellPtr& cell)
{
	if (!cell->setResolved())
		return;

	cell->formula()->evaluate();

	const auto& edges = cell->getDependents().raw();

	for (const auto& edgeIt : edges)
	{
		const auto& edge = rawEdge(edgeIt);

		if (!edge->tryAcquire())
			continue; // Skip already acquired edge.

		const auto& depCell = edge->cell();

		if (!depCell->decreasePendings())
			continue; // Skip cell which still has unresolved children.

		evaluateCell(context, depCell);
	}
}
