#pragma once

#include "IFormula.h"

// Summary formula, implements summation of child cells.
class Summary : public IFormula
{
public:
	virtual ~Summary();

	void addArgument(const CellPtr& cell);

private:
	virtual Result evaluateImpl() override;
};
