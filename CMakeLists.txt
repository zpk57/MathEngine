# CMakeList.txt: проект CMake для MathEngine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("MathEngine")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (MathEngine "main.cpp" "MathEngine/MathEngine.cpp" "MathEngine/MathEngine.h" "Data/Cell.h" "Data/Cell.cpp" "Data/Definitions.h" "Data/EdgeContainer.h" "Data/IFormula.h" "Formulas/Summary.h" "Formulas/Summary.cpp" "Formulas/ConstValue.h" "Formulas/ConstValue.cpp" "Data/IFormula.cpp" "Data/Document.h" "Data/Document.cpp" "IO/Parser.h" "IO/Parser.cpp" "Data/EdgeContainer.cpp" "Scheduling/ThreadPool.cpp" "Scheduling/ThreadPool.h" "MathEngine/EvaluationAlgorithm.h" "MathEngine/EvaluationAlgorithm.cpp" "MathEngine/CalculationContext.h" "MathEngine/CalculationContext.cpp" "Data/Edge.h" "Data/Edge.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
