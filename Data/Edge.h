#pragma once

#include "Definitions.h"
#include <atomic>

// Single directed edge with atomic state.
class Edge
{
public:
	Edge(const CellPtr& cell);

	bool tryAcquire();

	void reset();

	const CellPtr& cell() const;

private:
	CellPtr			 m_cell;
	std::atomic_bool m_acquired{ false };
};
