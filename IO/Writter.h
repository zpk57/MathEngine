#pragma once

#include "../Data/Definitions.h"

// Easy graph parser. Very slow.
class DocWritter
{
public:
	static void write(const DocumentPtr& document, const std::string& filepath);
};
