#pragma once

#include "Definitions.h"
#include <unordered_map>

// Document body. Retains all cells.
class Document
{
	using  Data = std::unordered_map<std::string, CellPtr>;

public:
	~Document();

	const CellPtr& getCell(const std::string& name);

	const Data& raw() { return m_data; }

private:
	CellPtr& getCellImpl(const std::string& name);

private:
	Data m_data;
};
