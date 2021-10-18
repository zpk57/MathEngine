#pragma once

#include "IFormula.h"

// Summary formula, implements summation of child cells.
class ConstValue : public IFormula
{
public:
	void setValue(const Result& value);

private:
	virtual Result evaluateImpl() override;

private:
	Result m_value;
};
