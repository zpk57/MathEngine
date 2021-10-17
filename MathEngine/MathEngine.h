#pragma once

#include "../Data/Definitions.h"

// MathEngine is a global interface. No business here. 
class MathEngine
{
public:
	static void evaluateAll(const DocumentPtr& doc, size_t threads);
};
