
#include "Summary.h"
#include "../Data/Cell.h"

Summary::~Summary()
{
}

void Summary::addArgument(const CellPtr& cell)
{
	m_cell->bindToChild(cell);
}

Result Summary::evaluateImpl()
{
	auto& items = m_cell->getChildren().raw();

	Result result = 0;

	for (auto& itemIt : items)
		result += rawEdge(itemIt)->cell()->formula()->getValue();

	return result;
}
