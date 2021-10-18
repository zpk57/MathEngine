#pragma once

#include "../Data/Definitions.h"

// Formula interface. Provides calculation. No any MT here.
class IFormula : public std::enable_shared_from_this<IFormula>
{
public:
	virtual ~IFormula() = default;

	void setup(const CellPtr& cell);

	void reset();

	void evaluate();

	const Result& getValue() const;

private:
	virtual Result evaluateImpl() = 0;

protected:
	bool	m_evaluated = false;
	Result	m_value;
	CellPtr m_cell;
};
