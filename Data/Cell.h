#pragma once

#include "Definitions.h"
#include "EdgeContainer.h"

// Cell object. Provides relations, atomic synschronization and formula owning. No any calculations here.

class Cell : public std::enable_shared_from_this<Cell>
{
public:
	Cell(const std::string& name);

	const std::string& name() const;

// Formula content.
	const IFormulaPtr& formula();
	void setFormula(const IFormulaPtr& formula);
	void cleanup();

// Atomic resolving.
	bool isResolved();
	bool setResolved();
	void resetRelations();
	bool decreasePendings(); // Returns true when there are no more pending edges.

// Relations.
	const EdgeContainer& getChildren() const;
	const EdgeContainer& getDependents() const;

	void bindToChild(const CellPtr& child);
	void unbindChild(const CellPtr& child);

private:
	void bindToDependent(const CellPtr& parent);
	void unbindDependent(const CellPtr& parent);

private:
	std::string m_name;
	IFormulaPtr m_formula;

	EdgeContainer	   m_children;
	EdgeContainer	   m_dependents;
	std::atomic_bool   m_resolved{ false };
	std::atomic_size_t m_pendingEdges{ 0 };
};
