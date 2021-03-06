# MathEngine

Эксплуатация:
1. Собрать.
2. Запустить в директории с входным файлом "input.txt".

О проекте:
1. Проект написан с рассчётом на дальнейшее расширение функциональности, нежели на решение конкретной задачи. Засчёт этого количество абстракций может показаться избыточным. Тем не менее, на его основе легко реализуются любые связанные задачи - расширение набора формул, добавление алгоритмов обхода, частичный пересчёт и т.п.
2. Основной упор делался на эффективный многопоточный обход графа. Вся синхронизация построена на атомарных переменных. Остаётся ещё много задач оптимизаций, в основном размещение данных в памяти и повышение их локальности. Эффективность внешнего функционала (чтение/запись) даже не рассматривается.
3. Алгоритм обхода состоит в обходе графа от вершин, не имеющих зависимостей для вычисления своего значения, в сторону зависимых от них вершин. Идея синхронизации в том, что вычислением вершины связано с потоком, пришедшим в неё по последнему неотмеченному ребру. Это гарантирует, что все зависимости в этот момент будут уже вычислены.
4. Для организации параллельных вычислений было реализовано несколько вариантов:
    а. Каждый поток пытается начать обход от каждой вершины графа, игнорируя уже вычисленные или имеющие зависимости вершины. Такой подход мог бы хорошо работать на графе, имеющим большое количество компонент связности, но даёт плохой эффект от параллельных вычислений на тестовом графе.
    б. Создание отдельной задачи для вычисления каждой вершины. С учётом тестовой нагрузки непосредственно на вычисление вершины, вычисления равномерно распределяются между всеми потоками. Даёт хорошо заметный эффект параллельных вычислений на тестовом графе. Скорость работы линейно коррелирует с количеством потоков.

P.S. Очень громоздко как тестовое задание. Большую часть времени занимает рутинное описание инфраструктуры элементов, относительно низкая доля интеллектуальной деятельности.
