
#include "IO/Parser.h"
#include "MathEngine/MathEngine.h"

int main()
{
	auto doc = TextParser::parse("input.txt");

	if (!doc)
		return 1;

	MathEngine::evaluateAll(doc, 10);

	return 0;
}
