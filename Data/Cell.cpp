#include "Cell.h"
#include "IFormula.h"


Cell::Cell(const std::string& name)
	: m_name(name)
{
}

const std::string& Cell::name() const
{
	return m_name;
}

const IFormulaPtr& Cell::formula()
{
	return m_formula;
}

void Cell::setFormula(const IFormulaPtr& formula)
{
	m_formula = formula;
}

void Cell::cleanup()
{
	m_formula.reset();

	auto thisPtr = shared_from_this();

	for (const auto& childIt : m_children.raw())
		rawEdge(childIt)->cell()->unbindDependent(thisPtr);

	m_children.clear();

	resetRelations();
}

bool Cell::isResolved()
{
	return m_resolved;
}

bool Cell::setResolved()
{
	bool expected = false;
	return m_resolved.compare_exchange_strong(expected, true);
}

void Cell::resetRelations()
{
	m_resolved = false;

	const auto& children = m_children.raw();
	m_pendingEdges = children.size();

	for (const auto& childIt : children)
		rawEdge(childIt)->reset();
}

bool Cell::decreasePendings()
{
	return --m_pendingEdges == 0;
}

const EdgeContainer& Cell::getChildren() const
{
	return m_children;
}

const EdgeContainer& Cell::getDependents() const
{
	return m_dependents;
}

void Cell::bindToChild(const CellPtr& child)
{
	if (m_children.addUnique(child))
		child->bindToDependent(shared_from_this());
}

void Cell::unbindChild(const CellPtr& child)
{
	if (m_children.remove(child))
		child->unbindDependent(shared_from_this());
}

void Cell::bindToDependent(const CellPtr& parent)
{
	m_dependents.add(parent);
}

void Cell::unbindDependent(const CellPtr& parent)
{
	m_dependents.remove(parent);
}
