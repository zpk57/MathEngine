
#include "IO/Parser.h"
#include "IO/Writter.h"
#include "MathEngine/MathEngine.h"

#include <chrono>
#include <iostream>

int main()
{
	auto doc = DocParser::parse("input.txt");

	if (!doc)
		return 1;

	auto start = std::chrono::system_clock::now();

	MathEngine::evaluateAll(doc, 8);

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;

	DocWritter::write(doc, "output.txt");

	doc.reset();

	return 0;
}
