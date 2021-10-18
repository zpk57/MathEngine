
#include "Parser.h"
#include "../Data/Document.h"
#include "../Data/Cell.h"
#include "../Formulas/Summary.h"
#include "../Formulas/ConstValue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <stdexcept>

namespace
{
    std::vector<std::string> splitStr(const std::string& in, char delim)
    {
        std::istringstream line(in);
        std::vector<std::string> items;
        std::string tmp;

        while (getline(line, tmp, delim))
            items.push_back(tmp);

        return items;
    }

    void trim(std::string& str)
    {
        static const auto pred = [](const char& c) { return c == ' '; };
        auto it = std::remove_if(str.begin(), str.end(), pred);
        str.erase(it, str.end());
    }

    bool isCellName(const std::string& str)
    {
        std::regex rCellName("^[A-Z][0-9]*$");

        return std::regex_search(str, rCellName);
    }

    bool isValue(const std::string& str)
    {
        std::regex rCellName("^[0-9.]*$");

        return std::regex_search(str, rCellName);
    }

    // Can extend to parse any formulas.
    void parseConstFormula(const DocumentPtr& doc, const CellPtr& cell, std::string& expression)
    {
        Result value = ::atoll(expression.c_str());

        auto formula = std::make_shared<ConstValue>();

        formula->setup(cell);

        formula->setValue(value);

        formula->reset();
    }

    void parseSummaryFormula(const DocumentPtr& doc, const CellPtr& cell, std::string& expression)
    {
        auto items = splitStr(expression, '+');

        if (items.empty())
            throw std::invalid_argument("invalid summary formula expression: " + expression);

        auto formula = std::make_shared<Summary>();

        formula->setup(cell);

        for (const auto& item : items)
        {
            if (!isCellName(item))
                throw std::invalid_argument("invalid summary formula argument: " + item);

            auto cell = doc->getCell(item);

            formula->addArgument(cell);
        }

        formula->reset();
    }

    void parseCellFormula(const DocumentPtr& doc, std::string& expression)
    {
        trim(expression);

        auto items = splitStr(expression, '=');

        if (items.size() != 2)
            throw std::invalid_argument("invalid expression: " + expression);

        auto& name    = items[0];
        auto& formula = items[1];

        if (!isCellName(name))
            throw std::invalid_argument("invalid cell name: " + name);

        auto cell = doc->getCell(name);

        if (isValue(formula))
            parseConstFormula(doc, cell, formula);
        else
            parseSummaryFormula(doc, cell, formula);
    }

    void checkDocConsistency(const DocumentPtr& doc)
    {
        const auto& rawDoc = doc->raw();

        for (const auto& cellIt : rawDoc)
        {
            const auto& cell = cellIt.second;

            if (!cell->formula())
                throw std::invalid_argument("no formula specified for cell: " + cell->name());
        }
    }
}

DocumentPtr DocParser::parse(const std::string& filepath)
{
    std::string   line;
    std::ifstream fileStream(filepath);

    if (!fileStream.is_open())
        return nullptr;

    try {
        auto doc = std::make_shared<Document>();

        while (getline(fileStream, line))
            parseCellFormula(doc, line);

        checkDocConsistency(doc);

        return doc;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception on parsing: " << e.what() << std::endl;
    }

    fileStream.close();

    return nullptr;
}
