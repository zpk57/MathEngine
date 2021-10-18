
#include "Writter.h"
#include "../Data/Document.h"
#include "../Data/Cell.h"
#include "../Formulas/IFormula.h"

#include <iostream>
#include <fstream>

void DocWritter::write(const DocumentPtr& document, const std::string& filepath)
{
    try {
        std::ofstream fileStream(filepath);

        if (!fileStream.is_open())
            return;

        const auto& rawDoc = document->raw();

        for (const auto& cellIt : rawDoc)
        {
            const auto& cell = cellIt.second;

            fileStream << cell->name() << " = " << std::to_string(cell->formula()->getValue()) << std::endl;
        }

        fileStream.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception on writting: " << e.what() << std::endl;
    }
}