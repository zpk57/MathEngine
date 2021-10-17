
#include "IFormula.h"
#include "../Data/Cell.h"
#include <stdexcept>


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
	m_value = evaluateImpl();

	m_evaluated = true;
}

const Result& IFormula::getValue() const
{
	if (!m_evaluated)
		throw std::runtime_error("attempt to get value for non evaluated formula of cell " + m_cell->name());

	return m_value;
}
