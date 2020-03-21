# Фрактал. Треугольник Серпинского.

Один из двумерных аналогов множества Кантора, предложенный польским математиком Вацлавом Серпинским в 1915 году.

![Визуализация Diamond-Square](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/ts.png "Орк")

# Построение итеративным методом

Середины сторон равностороннего треугольника T<sub>0</sub> соединяются отрезками. Получаются 4 новых треугольника. Из исходного треугольника удаляется внутренность срединного треугольника. Получается множество T<sub>1</sub>, состоящее из 3 оставшихся треугольников «первого ранга». Поступая точно так же с каждым из треугольников первого ранга, получим множество T<sub>2</sub>, состоящее из 9 равносторонних треугольников второго ранга. Продолжая этот процесс бесконечно, получим бесконечную последовательность T<sub>0</sub> &sup; T<sub>1</sub>  &sup; &hellip; &sup; T<sub>n</sub> &sup; &hellip;, пересечение членов которой есть треугольник Серпинского.

# Программная реализация

Данная программа, написанная на языке C++ с использованием библиотеки Qt, рисует реугольник Серпинского по вышеописанному алгоритму.

Значение _n_ указывает количество итераций при построении. Опция _"Автоматически подбирать значения n"_ подбирает значение _n_ таким образом, что бы размер последнего треугольника был не меньше "видимого" треугольника.

Опция _"Поставить точки на плоскости"_ позволяет установить три любые точки (вершины треугольника) на координатной плоскости, через которые будет постороен треугольник.

Опция _"Включить заливку"_ позволяет закрасить включаемые в множество трегольники выбранным цветом.

Опция _"Отрисовывать сетку"_ рисует сетку на координатной плоскости.

Кнопка _"Обновить"_ применит настройки и перерисует картику.

Кнопка _"Очистить"_ очистит плоскость.

Кнопка _"Сохранить"_ сохранит картинку на локальный компьютер.

# Примеры работы

![Пример 1](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/7.png "Орк")

![Пример 2](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/8.png "Орк")

![Пример 3](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/12.png "Орк")

![Пример 4](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/13.png "Орк")

![Пример 5](https://raw.githubusercontent.com/Sergkon99/fractal/master/img/14.png "Орк")
