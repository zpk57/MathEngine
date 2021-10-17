
#include "Document.h"
#include "IFormula.h"
#include "Cell.h"
#include <stdexcept>

Document::~Document()
{
	for (auto& cellIt : m_data)
		cellIt.second->cleanup();
}

const CellPtr& Document::getCell(const std::string& name)
{
	return getCellImpl(name);
}

CellPtr& Document::getCellImpl(const std::string& name)
{
	auto& item = m_data[name];

	if (!item)
		item = std::make_shared<Cell>(name);

	return item;
}
