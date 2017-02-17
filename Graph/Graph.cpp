#include "Graph.h"      // Подключение файла Graph.h
#include <fstream>      // Библеотека файлового ввода-вывода
#include <iostream>     // Библеотека консольного ввода-вывода
#include <sstream>      // Библеотека строкового ввода-вывода
#include <limits>       // Библеотека для диапазонов типов
#include <algorithm>    // Библеотека стандартных алгоритмов

using namespace std;	// Подключение команд для работы с командной строкой

Graph::Graph()			// Описание создания пустого графа
{						// Начало создания пустого графа
	type = ' ';			// Тип графа пустой
	weighted = false;	// Граф не взвешенный
	oriented = false;	// Граф не ориентированный
	N = 0;				// У Графа нет вершин 
	M = 0;				// У Графа нет ребер
}						// Завершение создания пустого графа

void Graph::readGraph(string fileName)							// Функция чтения графа с файла
{																// Начала функции чтения
	ifstream file(fileName.c_str());							// Создать объект файла и попытаться открыть файл с именем "fileName"
	if (!file.is_open())										// Если не удалось открыть файл 
	{															 // Выдать исключение
		cout << "Невозможно открыть файл" << fileName << "\n";	 // Вывод ошибки в командную строку
		return;													 // Выход из функиции
	}															// В случае 
	else														// Если файл открылся
		cout << "Чтение графа из файла " << fileName << "...\n"; // То выводит о продолжение выполнения функции
	file >> type;												// Определить, какой тип внутреннего представления графа описан в файле
	switch (type)												// По типу графа определяем 
	{															// Какой метод использовать
	case('C') :													// Если в файле описан граф, представленный в виде матрицы смежности
	{															// То
		adjMatrix.clear();										// Очистить текущее содержимое матрицы смежности
		file >> N;												// Считать количество вершин
		file >> oriented;										// Считать индикатор ориентированности графа
		file >> weighted;										// Считать индикатор взвешенности графа
		for (int i = 0; i < N; i++)								// Считать всю матрицу смежности
		{														 // Бежать по строкам
			vector<int> row;									 // Вектор для хранения текущей строки
			for (int j = 0; j < N; j++)							  // Бежать по столбцам
			{													  // Начало цикла
				int a;											  // Создаем переменую типа int для передачи значения ребра
				file >> a;										  // Считать текущее ребро
				row.push_back(a);								  // Сохранить считанное ребро в row
			}													  // Конец цикла
			adjMatrix.push_back(row);							 // Сохранить считанную строку в матрицу смежности
		}														 //
		break;													// Выход из switch
	}															// В случае
	case('L') :													// Если в файле описан граф, представленный в виде списка смежности
	{															// То
		adjList.clear();										// Очистить текущее содержимое списка смежности
		file >> N;												// Считать количество вершин
		file >> oriented;										// Считать индикатор ориентированности графа
		file >> weighted;										// Считать индикатор взвешенности графа
		file.ignore(numeric_limits<streamsize>::max(), '\n');	// Установить курсор чтения файла на новую строку
		for (int from = 0; from < N; from++)					// Считать N связей вершин
		{														 //
			string rowStr;										 // Строка для хранения списка связей текущей вершины
			getline(file, rowStr);								 // Считать текущую строку
			istringstream iss(rowStr);							 // Строковый поток ввода (для разбиения row по отдельным числам)
			set< pair<int, int> > row;							 // Переменная для хранения связей текущей вершины
			while (!iss.eof() && !iss.str().empty())			 // Бежать по rowStr
			{													  //
				int to = 0;										  // Переменная для хранения номера соседней вершины
				iss >> ws >> to;								  // Считать соседнюю вершину
				int weight = 0;									  // Переменная для хранения веса ребра
				if (weighted)									  // Если описан взвешенный граф
				{												   // То
					iss >> ws >> weight;						   // Считать вес ребра
				}												   // После
				row.insert(make_pair(to, weight));				  // Сохранить считанные связи в список связей
				iss.ignore(128);								  // Игнорировать оставшиеся символы в строке
			};													  // Завершение цикла
			adjList[from] = row;								 // Добавить список связей считанной вершины в список смежности
		}														//
		break;													// Выход из switch
	}															// В случае
	case('E') :													// Если в файле описан граф, представленный в виде списка ребер
	{															//
		edgList.clear();										// Очистить текущее содержимое списка ребер
		file >> N;												// Считать количество вершин
		file >> M;												// Считать количество ребер
		file >> oriented;										// Считать индикатор ориентированности графа
		file >> weighted;										// Считать индикатор взвешенности графа
		file.ignore(numeric_limits<streamsize>::max(), '\n');	// Установить курсор чтения файла на новую строку
		for (int i = 0; i < M; i++)								// Считать M ребер
		{														 // Начало цикла
			string rowStr;										 // Строка для хранения текущего ребра
			getline(file, rowStr);								 // Считать текущую строку
			istringstream iss(rowStr);							 // Строковый поток ввода (для разбиения row по отдельным числам)
			tuple<int, int, int> row;							 // Переменная для хранения текущего ребра
			while (!iss.eof() && !rowStr.empty())				 // Бежать по rowStr
			{													  // Начала цикла
				int from = 0;									  // Создаем переменную для номера начала ребра
				iss >> from;									  // Считать начало ребра
				int to = 0;										  // Создаем переменную для номера конца ребра
				iss >> to;										  // Считать конец ребра
				int weight = 0;									  // Переменная для хранения веса ребра
				if (weighted)									  // Если описан взвешенный граф
				{												   // То
					iss >> weight;								   // Считать вес ребра
				}												   // После сохранить считанные связи в список связей
				get<0>(row) = from;								  // Из какой вершины
				get<1>(row) = to;								  // В какую вершину
				get<2>(row) = weight;							  // И ее вес
			}													 // Конец цикла
			edgList.insert(row);								// Добавить ребро в список ребер
		}														// Конец цикла
		break;													// Выход switch
	}															// В случае
	default:													// Встречается 
	{															 // что-то иное то
		cout << "Невозможно распознать тип представления графа\n"; // Сообщить об ошибке
		return;													 // Выход
		break;													 // из функии
	}															// Если
	}															// все прошло удачно то
	cout << "Чтение графа ... Выполнено\n";						// Вывод окончание работы функиции
	printGraph();												// Напечатать граф
}																// Завершение работы функиции чтения графа

void Graph::addEdge(int from, int to, int weight)
{
	cout << "Добавление ребра из " << from << " в " << to << ", с весом " << weight << "...\n";
	switch (type)
	{
	case('C'):// Если текущее представление - матрица смежности
		{
			if (weight == 0)// Если значение параметра weight равно 0, это будет означать удаление ребра
			{
				cout << "Невозможно добавить ребро из" << from << " в " << to << ", вес ребра равен нулю\n";
				return;
			}
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// Проверить попадание в размерность матрицы
			{
				cout << "\nНевозможно добавить ребро из" << from << " в " << to << ", выход за пределы матрицы\n";
				return;
			}
			adjMatrix[from][to] = weight;// Установить в соответствующем столбце значение веса
			adjMatrix[to][from] = weight;// Установить значение симметричного элемента (свойство матрицы смежности)
			break;
		}
	case('L'):// Если текущее представление - список смежности
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// Итератор отображения - указывает на список связей вершины в списке смежности
				fromIt = adjList.find(from);// Найти в списке смежности начало ребра
				if (fromIt == adjList.end())// Если не найдено
				{	
					cout << "\nНевозможно добавить ребро из" << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке
					return;
				}
				set< pair<int, int> >::iterator toIt;// Итератор множества - указывает на соседние вершины в списке связей множества
				if (weighted)// Если граф взвешенный
				{
					toIt = fromIt->second.find(make_pair(to, weight));// Найти соседей текущей вершины, используя указанный вес
				}
				else    // Если граф невзвешенный
				{
					toIt = fromIt->second.find(make_pair(to, 0));// Найти соседей текущей вершины, используя в качестве веса 0
				}
				
				if (toIt != fromIt->second.end())// Если удалось что-то найти
				{
					cout << "\nНевозможно добавить ребро из" << from << " в " << to << ", ребро уже существует\n";// Сообщить об ошибке
					return;
				}
				if (weighted)// Если граф взвешенный
				{
					fromIt->second.insert(make_pair(to, weight));// Вставить новую соседнюю вершину, назначить ребру указанный вес
				}
				else    // Если граф невзвешенный
				{
					fromIt->second.insert(make_pair(to, 0));// Вставить новую соседнюю вершину, назначить ребру вес 0
				}
				if (!oriented)// Если граф неориентированный, то добавить также ребро в обратном направлении
				{
					if (weighted)// Если граф взвешенный
					{
						adjList[to].insert(make_pair(from, weight));// Использовать указанный вес
					}
					else    // Если граф невзвешенный
					{
						adjList[to].insert(make_pair(from, 0));// Использовать вес 0
					}
				}
				break;
			}
	case('E'): // Если текущее представление - спискок ребер
			{
				set< tuple<int, int, int> >::iterator itForward = edgList.end();// Итератор множества - указывает на ребро в списке ребер
				set< tuple<int, int, int> >::iterator itBackward = edgList.end();
				itForward = find_if(edgList.begin(), edgList.end(),// Проверить, существует ли добавляемое ребро
						[from](const tuple<int, int, int>& edge)
					{
						if (get<0>(edge) == from) return true;
						return false;
					});
					if (!oriented)
					{
						itBackward = find_if(edgList.begin(), edgList.end(),
							[to](const tuple<int, int, int>& edge)
						{
							if (get<0>(edge) == to) return true;
							return false;
						});
					}
					if (itForward != edgList.end() || itBackward != edgList.end())// Если что-то нашли
					{
						cout << "\nНевозможно добавить ребро из" << from << " в " << to << ", ребро уже существует\n";// Сообщить об ошибке
						return;
					}
					if (weighted)// Добавить требуемое ребро
					{
						edgList.insert(make_tuple(from, to, weight));
					}
					else
					{
						edgList.insert(make_tuple(from, to, 0));
					}
					break;
				}
				default:// Если другой тип
				{
					cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
					return;
					break;
				}
	}
	M++;// Увеличить счетчик ребер
	cout << "Добавление ребра ... Выполнено\n";
	printGraph();// Напечатать граф
}

void Graph::removeEdge(int from, int to)
{
	cout << "Удаление ребра из " << from << " в " << to << "...\t";
	switch (type)
	{
	case('C'):// Если текущее представление - матрица смежности
		{
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// Проверить попадание в размерность матрицы
			{
				cout << "\nНевозможно удалить ребро из " << from << " в " << to << ", ребро не найдено\n";
				return;
			}
			adjMatrix[from][to] = 0;// Установить в соответствующем столбце значение веса в 0
			adjMatrix[to][from] = 0;// Установить значение симметричного элемента (свойство матрицы смежности) в 0
			break;
		}
	case('L'):// Если текущее представление - список смежности
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// Итератор отображения - указывает на список связей вершины в списке смежности
				set< pair<int, int> >::iterator toIt;// Итератор множества - указывает на соседние вершины в списке связей множества
				fromIt = adjList.find(from);// Найти в списке смежности начало ребра
				if (fromIt != adjList.end())// Если найдено
				{
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// Найти среди соседей вершину, являющуюся концом ребра, которое необходимо удалить
						[&to](const pair<int, int>& edge)
					{
						if (edge.first == to) return true;
						return false;
					});
					if (toIt != fromIt->second.end())// Если удалось что-то найти
					{
						fromIt->second.erase(toIt);// Удалить требуемое ребро
					}
				}
				if (!oriented)// Если граф неориентированный, то удалить также ребро в обратном направлении
				{
					fromIt = adjList.find(to);// Найти в списке смежности начало ребра
					if (fromIt == adjList.end())// Если не найдено
					{
						return;// Вершина не существует, удалять нечего
					}
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// Найти среди соседей вершину, являющуюся концом ребра, которое необходимо удалить
						[&from](const pair<int, int>& edge)
					{
						if (edge.first == from) return true;
						return false;
					});
					if (toIt == fromIt->second.end())// Если не удалось ничего найти
					{
						
						cout << "\nНевозможно удалить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке (в неориентированном графе ребро должно быть в обоих направлениях)
						return;
					}
					fromIt->second.erase(toIt);// Удалить требуемое ребро
				}
				break;
			}
	case('E'): // Если текущее представление - спискок ребер
				{
					set< tuple<int, int, int> >::iterator itForward = edgList.end();// Итератор множества - указывает на ребро в списке ребер
					itForward = find_if(edgList.begin(), edgList.end(),// Проверить, существует ли удаляемое ребро
						[&from, &to](const tuple<int, int, int>& edge){
						if (get<0>(edge) == from && get<1>(edge) == to) return true;
						return false;
					});
					if (itForward != edgList.end())// Если что-то нашли, то удалить требуемое ребро
					{
						edgList.erase(itForward);
					}
					if (itForward == edgList.end())// Если совсем ничего нет
					{
						cout << "\nНевозможно удалить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке
						return;
					}
					break;
				}
	default:// Если другой тип
				{
					cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
					return;
					break;
				}
	}
	M--;// Уменьшить счетчик ребер
	cout << "Удаление ребра ... Выполнено\n";
	printGraph();// Напечатать граф
}

int Graph::changeEdge(int from, int to, int newWeight)
{
	cout << "Изменить вес ребра из " << from << " в " << to << ", на новый вес " << newWeight << "...\n";
	if (!weighted)// Если граф невзвешенный
	{
		cout << "\tК сожалению, вы не можете изменить вес ребра невзвешенного графа\n";// Сообщить об ошибке (у ребер нет весов, модифицировать нечего)
		return -1;
	}
	int oldWeight = 0;
	switch (type)
	{
	case('C'):// Если текущее представление - матрица смежности
		{
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// Проверить попадание в размерность матрицы
			{
				cout << "\nНевозможно изменить ребро из " << from << " в " << to << ", ребро не найдено\n";
				return -1;
			}
			oldWeight = adjMatrix[from][to];// Сохранить прежнее значение веса
			adjMatrix[from][to] = newWeight;// Установить в соответствующем столбце значение веса в newWeight
			adjMatrix[to][from] = newWeight;// Установить значение симметричного элемента (свойство матрицы смежности) в newWeight
			break;
		}
	case('L'):// Если текущее представление - список смежности
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// Итератор отображения - указывает на список связей вершины в списке смежности
				fromIt = adjList.find(from);// Найти в списке смежности начало ребра
				if (fromIt == adjList.end())// Если не найдено
				{
					cout << "\nНевозможно изменить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке
					return -1;
				}
				fromIt->second.insert(make_pair(1, 2));
				set< pair<int, int> >::iterator toIt;// Итератор множества - указывает на соседние вершины в списке связей множества
				toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// Найти среди соседей вершину, являющуюся концом ребра, которое необходимо изменить
					[&to](const pair<int, int>& edge)
				{
					if (edge.first == to) return true;
					return false;
				});
				if (toIt == fromIt->second.end())// Если не удалось ничего найти
				{
					
					cout << "\nНевозможно изменить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке
					return -1;
				}
				oldWeight = toIt->second;// Сохранить прежнее значение веса
				pair<int, int> copy = *toIt;// Назначить ребру указанный вес
				copy.second = newWeight;
				fromIt->second.erase(toIt);
				fromIt->second.insert(copy);
				if (!oriented)// Если граф неориентированный, то изменить также ребро в обратном направлении
				{
					fromIt = adjList.find(to);// Найти в списке смежности начало ребра
					if (fromIt == adjList.end())// Если не найдено
					{
						return -1;// Вершина не существует, удалять нечего
					}
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// Найти среди соседей вершину, являющуюся концом ребра, которое необходимо удалить
						[&from](const pair<int, int>& edge)
					{
						if (edge.first == from) return true;
						return false;
					});
					if (toIt == fromIt->second.end())// Если не удалось ничего найти
					{
						
						cout << "\nНевозможно изменить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке (в неориентированном графе ребро должно быть в обоих направлениях)
						return -1;
					}
					pair<int, int> copy = *toIt;// Назначить ребру указанный вес
					copy.second = newWeight;
					fromIt->second.erase(toIt);
					fromIt->second.insert(copy);
					break;
				}
			}
	case('E'):// Если текущее представление - спискок ребер
				{
					set< tuple<int, int, int> >::iterator itForward = edgList.end();// Итератор множества - указывает на ребро в списке ребер
					set< tuple<int, int, int> >::iterator itBackward = edgList.end();
					itForward = find_if(edgList.begin(), edgList.end(),// Проверить, существует ли изменяемое ребро
						[&from, &to](const tuple<int, int, int>& edge){
						if (get<0>(edge) == from && get<1>(edge) == to) return true;
						return false;
					});
					if (!oriented)// Для неориентированного проверить также ребро в обратном направлении
					{
						itBackward = find_if(edgList.begin(), edgList.end(),
							[&from, &to](const tuple<int, int, int>& edge){
							if (get<0>(edge) == to && get<1>(edge) == from) return true;
							return false;
						});
					}
					if (itForward != edgList.end())// Если что-то нашли, то изменить требуемое ребро
					{
						tuple<int, int, int> copy = *itForward;
						oldWeight = get<2>(copy);
						get<2>(copy) = newWeight;
						edgList.erase(itForward);
						edgList.insert(copy);
					}
					if (itBackward != edgList.end())
					{
						tuple<int, int, int> copy = *itBackward;
						oldWeight = get<2>(copy);
						get<2>(copy) = newWeight;
						edgList.erase(itBackward);
						edgList.insert(copy);
					}
					if (itForward == edgList.end() && itBackward == edgList.end())// Если совсем ничего нет
					{
						cout << "\nНевозможно изменить ребро из " << from << " в " << to << ", ребро не найдено\n";// Сообщить об ошибке
						return -1;
					}
					break;
				}
			default:// Если другой тип
			{
				cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
				return 0;
				break;
			}
	}
	cout << "Изменение веса ребра ... Выполнено\n";
	printGraph();// Напечатать граф
	return oldWeight;// Вернуть прежнее значение веса
}

void Graph::transformToAdjList()
{
	cout << "Преобразование графа из ";
	switch (type)// Конвертировать в зависимости от типа
	{
	case('C') :
	{
		cout << " матрицы смежности в список смежности ...\n";
		adjList.clear();
		for (size_t i = 0; i < adjMatrix.size(); i++)
		{
			for (size_t j = 0; j < adjMatrix[i].size(); j++)
			{
				if (adjMatrix[i][j] != 0)
				{
					adjList[i].insert(make_pair(j, adjMatrix[i][j]));
				}
			}
		}
		adjMatrix.clear();
		break;
	}
	case('L') :
	{
		cout << " cписока смежности в список смежности ...\n";
		break;
	}
	case('E') :
	{
		cout << " cписока ребер в список смежности...\n";
		adjList.clear();
		for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
		{
			adjList[get<0>(*it)].insert(make_pair(get<1>(*it), get<2>(*it)));
		}
		edgList.clear();
		break;
	}
	default:// Если другой тип
	{
		cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
		return;
		break;
	}
	}
	type = 'L';
	cout << "Преобразование в список смежности ... Выполнено\n";
	printGraph();
}

void Graph::transformToAdjMatrix()
{
	cout << "Преобразование графа из  ";
	switch (type)// Конвертировать в зависимости от типа
	{
	case('C') :
	{
		cout << " матрицы смежности в матрицу смежности ...\t";
		break;
	}
	case('L') :
	{
		cout << " cписока смежности в матрицу смежности ...\t";
		adjMatrix.clear();
		adjMatrix.resize(adjList.size(), vector<int>(adjList.size(), 0));
		for (map< int, set< pair< int, int > > >::iterator i = adjList.begin(); i != adjList.end(); i++)
		{
			for (set< pair< int, int > >::iterator j = i->second.begin(); j != i->second.end(); j++)
			{
				adjMatrix[i->first][j->first] = j->second;
			}
		}
		adjList.clear();
		break;
	}
	case('E') :
	{
		cout << " список ребер в матрицу смежности ...\t";
		adjMatrix.clear();
		adjMatrix.resize(N, vector<int>(N, 0));
		for (set< tuple< int, int, int > >::iterator it = edgList.begin(); it != edgList.end(); it++)
		{
			adjMatrix[get<0>(*it)][get<1>(*it)] = get<2>(*it);
			if (!oriented)
			{
				adjMatrix[get<1>(*it)][get<0>(*it)] = get<2>(*it);
			}
		}
		edgList.clear();
		break;
	}
	default:// Если другой тип
	{
		cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
		return;
		break;
	}
	}
	type = 'C';
	cout << "Преобразование в матрицу смежности ... Выполнено\n";
	printGraph();
}

void Graph::transformToListOfEdges()
{
	cout << "Преобразование графа из ";
	switch (type)// Конвертировать в зависимости от типа
	{
	case('C'):
		{
			cout << " матрицы смежности в список ребер ...\n";
			edgList.clear();
			for (int i = 0; i < adjMatrix.size(); i++)
			{
				for (int j = 0; j < adjMatrix[i].size(); j++)
				{
					if (adjMatrix[i][j] != 0)
					{
						set< tuple< int, int, int > >::iterator it =
							find_if(edgList.begin(), edgList.end(), [this, i, j](const tuple< int, int, int >& elem)
						{
							if (get<0>(elem) == i && get<1>(elem) == j) return true;
							if (!oriented)
							{
								if (get<0>(elem) == j || get<1>(elem) == i) return true;
							}
							return false;
						});
						if (it == edgList.end())
						{
							edgList.insert(make_tuple(i, j, adjMatrix[i][j]));
						}
					}
				}
			}
			adjMatrix.clear();
			break;
		}
	case('L'):
		{
			cout << " cписока смежности в список ребер ...\n";
			edgList.clear();
			for (map< int, set< pair< int, int > > >::iterator i = adjList.begin(); i != adjList.end(); i++)
			{
				for (set< pair< int, int > >::iterator j = i->second.begin(); j != i->second.end(); j++)
				{
					edgList.insert(make_tuple(i->first, j->first, j->second));
				}
			}
			adjList.clear();
			break;
		}
	case('E'):
		{
			cout << " списка ребер в список ребер ...\n";
			break;
		}
	default:// Если другой тип
	{
		cout << "\nНевозможно распознать тип представления графа\n";// Сообщить об ошибке
		return;
		break;
	}
	}
	type = 'E';
	cout << "Преобразование в список ребер ... Выполнено\n";
	printGraph();
}

bool Graph::is_weighted()
{
	return weighted;
}

void Graph::printGraph()
{
	cout << "Вывод графа (";
	if (oriented)// Отобразить флаг ориентированности
	{
		cout << "Ориентированный, ";
	}
	else
	{
		cout << "Не ориентированный, ";
	}
	if (weighted)// Отобразить флаг взвешенности
	{
		cout << "Взвешенный, ";
	}
	else
	{
		cout << "Не взвешенный, ";
	}
	if (type == 'C')// Если текущее представление - матрица смежности
	{
		cout << "Матрица смежности) ...\n";
		// Бежать по строкам
		for (size_t i = 0; i<adjMatrix.size(); i++)
		{
			// Бежать по столбцам
			for (size_t j = 0; j<adjMatrix[i].size(); j++)
			{
				// Напечатать текущий элемент
				cout << adjMatrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
	else    // Если текущее представление - список смежности
		if (type == 'L')
		{
			cout << "Список смежности) ...\n";
			// Бежать по строкам
			for (map< int, set< pair<int, int> > >::iterator fromIt = adjList.begin(); fromIt != adjList.end(); fromIt++)
			{
				// Бежать по столбцам
				for (set< pair<int, int> >::iterator toIt = fromIt->second.begin(); toIt != fromIt->second.end(); toIt++)
				{
					cout << toIt->first;// Напечатать конец текущего ребра
					if (weighted)// Если граф взвешенный
					{
						cout << " " << toIt->second;// Напечатать вес текущего ребра
					}
					cout << " ";
				}
				cout << "\n";
			}
		}
		else    // Если в файле описан граф, представленный в виде списка ребер
			if (type == 'E')
			{
				cout << "Список ребер) ...\n";
				// Бежать по строкам
				for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
				{
					cout << get<0>(*it) << " ";// Напечатать начало текущего ребра
					cout << get<1>(*it);// Напечатать конец текущего ребра
					if (weighted)// Если граф взвешенный
					{
						cout << " " << get<2>(*it);// Напечатать вес текущего ребра
					}
					cout << "\n";
				}
			}
			else    // Если в файле что-то иное
			{
				cout << "Невозможно распознать тип представления графа\n";// Сообщить об ошибке
				return;
			}
}

void Graph::writeGraph(string fileName)
{
	ofstream file(fileName.c_str());// Создать объект файла и попытаться открыть файл с именем "fileName"
	if (!file.is_open())// Если не удалось открыть файл, кинуть исключение
	{
		cout << "Невозможно открыть файл " << fileName << "\n";
		return;
	}
	cout << "Запись графа в файл " << fileName << " ...\n";
	
	file << type << " ";// Сохранить тип текущего представления

	
	if (type == 'C')// Если текущее представление - матрица смежности
	{
		file << adjMatrix.size() << "\n";// Сохранить количество вершин
		file << oriented << " ";// Сохранить флаг ориентированности
		file << weighted << "\n";// Сохранить флаг взвешенности
		// Бежать по строкам
		for (size_t i = 0; i<adjMatrix.size(); i++)
		{
			// Бежать по столбцам
			for (size_t j = 0; j<adjMatrix[i].size(); j++)
			{
				// Сохранить текущий элемент
				file << adjMatrix[i][j] << " ";
			}
			file << "\n";
		}
	}
	else    // Если текущее представление - список смежности
		if (type == 'L')
		{
			file << N << "\n";// Сохранить количество вершин
			file << oriented << " ";// Сохранить флаг ориентированности графа
			file << weighted << "\n";// Сохранить флаг взвешенности графа
			// Бежать по строкам
			for (map< int, set< pair<int, int> > >::iterator fromIt = adjList.begin(); fromIt != adjList.end(); fromIt++)
			{
				// Бежать по столбцам
				for (set< pair<int, int> >::iterator toIt = fromIt->second.begin(); toIt != fromIt->second.end(); toIt++)
				{
					// Напечатать конец текущего ребра
					file << toIt->first;
					// Если граф взвешенный
					if (weighted)
					{
						// Напечатать вес текущего ребра
						file << " " << toIt->second;
					}
					file << " ";
				}

				file << "\n";
			}
		}
		else    // Если текущее представление - список ребер
			if (type == 'E')
			{
				file << N << " ";// Сохранить количество вершин
				file << M << "\n";// Сохранить количество ребер
				file << oriented << " ";// Сохранить флаг ориентированности графа
				file << weighted << "\n";// Сохранить флаг взвешенности графа
				// Бежать по строкам
				for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
				{
					// Сохранить начало текущего ребра
					file << get<0>(*it) << " ";
					// Сохранить конец текущего ребра
					file << get<1>(*it);
					// Если граф взвешенный
					if (weighted)
					{
						// Сохранить вес текущего ребра
						file << " " << get<2>(*it);
					}
					file << "\n";
				}
			}
			else    // Если в файле что-то иное
			{
				// Сообщить об ошибке
				cout << "Невозможно распознать тип представления графа\n";
				return;
			}

	cout << "Запись графа в файл ... Выполнено\n";
}
