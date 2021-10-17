
#include "ConstValue.h"

void ConstValue::setValue(const Result& value)
{
	m_value = value;
}

Result ConstValue::evaluateImpl()
{
	return m_value;
}
