#pragma once

#include "../Data/Definitions.h"

// Easy graph parser. Very slow.
class TextParser
{
public:
	static DocumentPtr parse(const std::string& filepath);
};
