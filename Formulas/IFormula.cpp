
#include "IFormula.h"
#include "../Data/Cell.h"
#include <stdexcept>

namespace {
	void load()
	{
		volatile size_t i = 0;

		while (i < 100000)
			++i;
	}
}

void IFormula::setup(const CellPtr& cell)
{
	m_cell = cell;

	m_cell->setFormula(shared_from_this());
}

void IFormula::reset()
{
	m_cell->resetRelations();

	m_evaluated = false;
}

void IFormula::evaluate()
{
	if (m_evaluated)
		throw std::runtime_error("attempt to evaluate already evaluated formula of cell " + m_cell->name());

	m_value = evaluateImpl();

//    load();

	m_evaluated = true;
}

const Result& IFormula::getValue() const
{
	if (!m_evaluated)
		throw std::runtime_error("attempt to get value for non evaluated formula of cell " + m_cell->name());

	return m_value;
}
