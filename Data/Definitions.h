#pragma once

#include <vector>
#include <memory>
#include <string>

class Cell;
class Edge;
class IFormula;
class EdgeContainer;
class CalculationContext;
class Document;
using CellPtr     = std::shared_ptr<Cell>;
using EdgePtr     = std::unique_ptr<Edge>;
using IFormulaPtr = std::shared_ptr<IFormula>;
using DocumentPtr = std::shared_ptr<Document>;
using Cells       = std::vector<CellPtr>;
using Result      = int64_t;
