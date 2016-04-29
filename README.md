﻿# TO DO

## Содержание

* [Постановка задачи](#Постановка-задачи)
* [Руководство пользователя](#Руководство-пользователя)
	* [Алгоритм Дейкстры](#Алгоритм-Дейкстры)
	* [Алгоритм Крускала](#Алгоритм-Крускала)
* [Руководство программиста](#Руководство-программиста)
	* [Используемые инструменты](#Используемые-инструменты)
	* [Общая структура проета](#Общая-структура-проекта)
	* [Описание структуры программы](#Описание-структуры-программы)
	* [Описание структур данных](#Описание-структур-данных)
		* [Д-куча](#Д-куча)
		* [Приоритетная очередь](#Приоритетная-очередь)
		* [Разделенные множества](#Разделенные-множества)
	* [Описание алгоритмов](#Описание-алгоритмов)
		* [Пирамидальная сортировка](#Пирамидальная-сортировка)
		* [Алгоритм Дейкстры](#Алгоритм-Дейкстры)
		* [Алгоритм Крускала](#Алгоритм-Крускала)
* [Заключение](#Заключение)
* [Литература](#Литература)
* [Приложение 1: Представление графа](#Приложение-1-:-Представление-Графа)

##Постановка задачи

// TO DO

##Руководство пользователя
###Алгоритм Дейкстры

####Запуск приложения и ввод данных

Программа предназначена для поиска кратчийших путей во взвешенном неориентированном графе от некоторой вершины, называемой текущей, до всех остальных вершин графа.
Для запуска приложения нужно открыть исполняемый файл sample_Dijkstra.exe.
Программа попросит ввести количество вершин графа и ребра с весом. Также будет запрошен номер вершины, являющейся стартовой. Результатом будет вывод списка расстояний от стартовой вершины до каждой из следующих вершин в порядке возрастания номера.

#####Пример:

Рассмотрим граф:
// IMG


// TO DO

###Алгоритм Крускала

####Запуск приложения и ввод данных

Программа предназначена для построения минимального остовного дерева для взвешенного неориентированного графа. 
Для запуска приложения нужно открыть исполняемый файл sample_Kruskal.exe.
Программа попросит ввести количество вершин графа и ребра с весом. Результатом работы программы будет вывод списка ребер, составляющих минимальное остовное дерево.


// TO DO

##Руководство программиста
###Используемые инструменты

- Среда разработки Microsoft Visual Studio Community (2015);
- Фреймворк для написания автоматических тестов Google Test;
- Система контроля версий Git;

###Общая структура проекта

* [`gtest`](https://github.com/Alexander-Khlybov/lab4/tree/master/gtest) - библиотека GoogleTest;
* [`src`](https://github.com/Alexander-Khlybov/lab4/tree/master/src) - директория для размещения файлов исходноо кода;
* [`include`](https://github.com/Alexander-Khlybov/lab4/tree/master/include) - директория для размещения заголовочных файлов;
* [`sample`](https://github.com/Alexander-Khlybov/lab4/tree/master/samples) - директория для размещения исходных кодов приложений;
* [`test`](https://github.com/Alexander-Khlybov/lab4/tree/master/test) - директория для размещения тестов;
* [`sln`](https://github.com/Alexander-Khlybov/lab4/tree/master/sln/) - директория с файлими решений (на данный момент Visual Studio 2015);
* [`Rept`](https://github.com/Alexander-Khlybov/lab4/tree/master/Rept) - директория с материалами для отчета;
* Служебные файлы:
  * `.gitignore` - перечень расширений файлов, игнорируемых Git при добавлении файлов в репозиторий;


###Описание структуры программы

Программа состоит из 8 проектов:

* `gtest` - фреймворк Google Test;
* `d-heap_lib` - статическая библиотека, содержащая объявление и реализацию шаблонного класса D_HEAP;
* `disjoint-set_lib` - статическая библиотека, содержащая объявление и реализацию шаблонного класса DISJOINT_SET;
* `priority_queue_lib` - статическая библиотека, содержащая объявление и реализацию шаблонного класса PRIORITY_QUEUE;
* `sampleDijkstra` - консольное приложение для демонстрации работы [*алгоритма Дейкстры*](#Алгоритм-Дейкстры);
* `sample_Kruskal` - консольное приложение для демонстрации работы [*алгоритма Крускала*](#Алгоритм-Крускала);
* `sample_d-heap` - консольное приложение для демонстрации работы [*пирамидальной сортировки*](#Пирамидальная-сортировка);
* `test` - консольно приложение для проверки правильности реализации классов *D_HEAP*, *PRIORITY_QUEUE*, *DISJOINT_SET*.

###Описание структур данных
####Д-куча
Д-куча - завершенное d-арное дерево, содержащее набор однотипных элементов, со следующими свойствами:
- Каждый узел, не являющийся листом, за исключением, быть может, одного имеет ровно d потомков. Один узел, являющийся исключением, может иметь от 1 до d-1 потомка;
- Если h - глубина дерева, то для любого i = 1, ..., k-1 такое дерево имеет ровно d^i узлов глубины i;
- Количество узлов глубины k в дереве глубины k может варьироваться от 1 до d**k;
- Каждый узел имеет вес. Иначе говоря, каждому узлу дерева присвоен ключ такого типа данных, на котором определен порядок сравнения;
- Ключ элемента, приписанного узлу i, не превосходит ключа любого из своих потомков.

// IMG

В лабораторной работе Д-куча представлена классом D_HEAP, содержащим нижеизложенные public-методы:
- `D_HEAP(int, int)` - конструктор. Принимает на вход стартовый размер вектора памяти для хранения d-кучи и арность;
- `D_HEAP(const D_HEAP<KeyType>&)` - конструктор копирования;
- `~D_HEAP (void)` - деструктор;
- `operator==(const D_HEAP<KeyType>&)const` - перегруженный оператор сравнения на равенство (требуется для проведения тестов);
- `operator!=(const D_HEAP<KeyType>&)const` - перегруженный оператор сравнения на неравенство (требуется для проведения тестов);
- `getSizeTree(void)const` - возвращает количество узлов, содержащихся в д-куче;
- `getNodeKey(int)const` - возврацает ключ узла, номер которого передан в качестве параметра;
- `getSizeReservedMem(void)const` - возвращает размер свободной памяти в выделенном ранее векторе памяти;
- `getD(void)const` - возвращает арность кучи;
- `swap(int, int)` - меняет местами узлы, индексы которых переданы в качестве параметров;
- `siftDown(int)` - выполняет погружение узла с индексом, указанным в качестве аргумента;
- `siftUp(int)` - выполняет всплытие узла с индексом, указанным в качестве аргумента;
- `insert(const KeyType&, mem_rc flag = ALLOW_MEMORY_REALLOCATION_WCV, int size = 0)` - производит вставку узла, переданного первым аргументом в дерево. Вторым параметром указывается правило обработки ситуации, когда вставляется узел в полное дерево:
	- ALLOW_MEMORY_REALLOCATION_WYV - разрешить выделить дополнительную память при вставке узла в полное дерево. Размер добавляемой памяти указывается в качестве третьего параметра;
	- - ALLOW_MEMORY_REALLOCATION_WCV - разрешить выделить дополнительную память при вставке узла в полное дерево, однако третий аргумент метода в этом случае игнорируется, выделение же памяти будет таковым, что появляется место минимум под один узел, максимум под d узлов. Текущее значение выделения памяти будет таковым, чтобы выполнялись указанные условия и одно дополнительное: новый размер вектора памяти делится на арность кучи;
	- PROHIBIT_MEMORY_REALLOCATION - запретить выделение дополнительной памяти при вставке узла в полное дерево.
- `deleteMinElem(void)` - удаление узла с минимальным весом;
- `deleteElem(int)` - удаление узла дерева по индексу хранения в векторе памяти.
- `heapify(void)` - окучивание;
- `getTree(void)const` - возвращает вектор значений, содержащихся в векторе памяти, что хранит исходное дерево (требуется для тестирования);
- `operator<<(...)` - печать массива, хранящего значения узлов.

Класс реализован шаблонным, что позволяет хранить любого рода данные, для которых определен порядок сравнения.

Представленный набор методов достаточен для проведения тестирования корректности представления и работы класса, а также для реализации иных структур данных, в частности, приоритетной очереди. Пример использования д-кучи описан в разделе  [*Пирамидальная сортировка*](#Пирамидальная-сортировка)

####Приоритетная очередь

Приоритетная очередь - динамическая структура данных, хранящая набор однотипных элементов с определенным отношением порядка на этих данных. Сам порядок определяет отношение преобладания одного элемента над другим. В данной лабораторной работе старшинство приоритета отдается меньшему по порядку значению.

Для хранения и реализации приоритетной очереди улобно использовать д-кучу.

// IMG

В лабораторной работе Д-куча представлена классом D_HEAP, содержащим нижеизложенные public-методы:

- `PRIORITY_QUEUE(int)` - конструктор; в качестве аргумента принимает арность дерева хранения очереди (по умелчанию эзначение равно трем);
- `PRIORITY_QUEUE(const PRIORITY_QUEUE<KeyType>&)` - конструктор копирования;
- `~PRIORITY_QUEUE(void)` - деструктор;
- `getSize(void)const` - возвращает количество элементов в очереди;
- `getHeap(void)` - водвращает д-кучу, хранящую элементы очереди (требуется для проведения тестирования);
- `operator==(const PRIORITY_QUEUE<KeyType>&)const` - перегруженный опеатор сравнения на равенство (требуется для тестирования);
- `operator!=(const PRIORITY_QUEUE<KeyType>&)const` - перегруженный оператор сравнения на неравенство;
- `isEmpty(void)const` - проверка очереди на пустоту (возвращает 1, если очередь пуста, иначе 0);
- `pop(void)` - удаляет первый в очереди элемент;
- `push(const KeyType&)` - добавляет элемент в очередь;
- `back(void) const` - возвращает первый элемент в очереди (без удаления);
- `operator<<(...)` - печать узлов очереди.

Класс реализован шаблонным, что позволяет хранить любого рода данные, для которых определен порядок сравнения.

Представленный набор методов достаточен для проведения тестирования корректности представления и работы класса, а также использования его в иных алгоритмах. Пример использования приоритетной очереди описан в разделе  [*Алгоритм Дейкстры*](#Алгоритм-Дейкстры).

####Разделенные множества
Разледенные множества - абстрактный тип данных, предназначенный для представления коллекции k попарно непересекающихся можеств.

В данной лабораторной работе разделенные множества реализуются на древесной структуре.

// IMG

- `DISJOINT_SET<KeyType>(int)` - конструктор; принимает в качестве аргумента максимальное суммарное количество элементов множеств;
- `DISJOINT_SET<KeyType>(const DISJOINT_SET<KeyType>&)` - конструктор копирования;
- `~DISJOINT_SET<KeyType>(void)` - деструктор;
- `createSet(int)` - создает одноэлементное множество с элементом, указанным в качестве аргумента;
- `uniteSets(int, int)` - объединяет два множества (множества передаются номером главного элемента);
- `findSet(int)` - возвращает главный элемент множества, если элемент принадлежит какому-либо множеству, иначе -1;
- `getNumberOfSets(void)const` - возвращает текущее количество множеств (требуется для тестирования);
- `getUniversalSet(void)const` - возвращает вектор, хранящий структуру множеств (требуется для тестирования);
- `getSet(int)const` - возвращает вектор элементов, содержащихся в множестве, которое указано в качестве аргумента (множество задается главным элементом);
- `operator<<(...)` - выводит вектор, содержащий структуру множеств.

Представленный набор методов достаточен для проведения тестирования корректности представления и работы класса, а также использования его в иных алгоритмах. Пример использования разделенных множеств описан в разделе  [*Алгоритм Крускала*](#Алгоритм-Крускала).

###Описание алгоритмов
####Пирамидальная сортировка

Консольное приложение, содержащее пример работы алгоритма собирается из проекта `sample_d-heap`. Сортировка является методом `sort` класса *D_HEAP* (возвращает отсортированный вектор значений).

#####Алгоритм пирамидальной сортировки:
1. Вектор значений переписывается в д-кучу;
2. Минимальный элемент д-кучи меняется с последним;
3. Декрементируется размер д-кучи;
4. Погружение нулевого элемента;
5. Если размер кучи положителен, переход к п.2, иначе алгоритм завершается;

Таким образом вощвращаемый вектор значений будет отсортирован по невозрастанию.

####Алгоритм Дейкстры

Поиск кратчайших путей от текущей вершины до каждой вершины графа.

Консольное приложение, содержащее пример работы алгоритма собирается из проекта `sample_Dijkstra`.

#####Алгоритм:
1. Задается взвешенный граф из n вершин;
2. Задается стартовая вершина CUR;
3. Создается вектор для отметки посещения вершины V (все элементы зануляются, V[CUR] = CUR);
4. Создается результирующий вектор расстояний DIST (все элементы устремлены в бесконечность, DIST[CUR] = 0);
5. Создается приоритетная очередь, в которую кладется расстояние от текущей вершины до неё же;
6. Пока очередь не пуста:
	1. Вынимается минимальный элемент;
	2. Если метка вынутого элемента больше метки, хранящейся в массиве DIST, переход к следующему шагу;
	3. По всем ребрам от текущей вершины: Если результирующее расстояние от смежной вершины больше, чем результирующее расстояние до вынутой в пункте 6.1 вершины в сумме с меткой ребра, вынутогов пункте 6.3, выполняем:
		1. В вектор V по номеру смежной вершины кладется значение вершины, вынутой на этапе 6.1;
		2. В вектор DIST по номету смежной вершины пишется новое значение расстояния, равное сумме результирующего расстояния до вынутой в пункте 6.1 вершины и меткои ребра, вынутогов пункте 6.3;
		3. Обработанное ребро кладется в очередь.

Результатом работы алгоритма становится вектор расстояний до каждой вершины графа (DIST) и вектор обхода вершин графа для получения указанных значений (V).

####Алгоритм Крускала

Построение минмального остовного дерева для взвешенного графа.

Консольное приложение, содержащее пример работы алгоритма собирается из проекта `sample_Kruskal`.

#####Алгоритм:
1. Задается взвешенный неориентированный граф из n вершин;
2. Создается приоритетная очередь из ребер графа (приоритет по метке ребра);
3. Содрается n одноэлементных множеств (используется класс DISJOINT_SET);
4. Вынимаем ребро из приоритетной очереди;
5. Объединяем множества, содержащие вершины, что принадлежат вынутому ребру;
6. Добавляем вынутое ребро в результирующий набор ребер;
7. Если объект класса DISJOINT_SET состоит из более чем одного множества, переход к пункту 4, иначе алгоритм завершается.

В результате работы алгоритма имеется набор ребер, составляющих минимальное остовное дерево данного графа.

##Заключение

// TO DO

##Литература

// TO DO

##Приложение 1: Представление графа

// TO DO
