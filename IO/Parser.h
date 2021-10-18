#pragma once

#include "../Data/Definitions.h"

// Easy graph parser. Very slow.
class DocParser
{
public:
	static DocumentPtr parse(const std::string& filepath);
};
