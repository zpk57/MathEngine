
#include "Edge.h"

Edge::Edge(const CellPtr& cell)
	: m_cell(cell)
{
}

bool Edge::tryAcquire()
{
	bool expected = false;
	return m_acquired.compare_exchange_strong(expected, true);
}

void Edge::reset()
{
	m_acquired = false;
}

const CellPtr& Edge::cell() const
{
	return m_cell;
}
