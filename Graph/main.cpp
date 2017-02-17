#include "Graph.h"  // Подключить описание класса Graph
#include <iostream> // Ввод-вывод
#include <fstream>  // Файловый ввод-вывод
#include <ctime>	// Библеотеки для 
#include <cmath>	// измерения времени операций

using namespace std;

double timeS, timeF;

clock_t start() // Старт Времени
{ 
	timeS = (double) clock(); 
	return clock(); 
}

clock_t finish() // Завершение времени и вывод результата в консоль
{ 
	timeF = (double) clock(); 
	cout << "Время выполненеие: " << (timeF - timeS) / CLOCKS_PER_SEC<< " секунд.\n\n";
	return clock(); 
}

int main(void)
{
	setlocale(LC_ALL, "Russian"); // подключение русских символов
	Graph graph;	// Создаем пустой граф
	string choice;	// Переменная для хранения пользовательского выбора
	do	// Опрашивать пользователя и выполнять требуемое
	{	// Показать основное меню
		cout << "Выберете действие из списка?\n";
		cout << "1|-> Чтение графа из файла\n";
		cout << "2|-> Сохранить граф в файл\n";
		cout << "3|-> Добавить ребро\n";
		cout << "4|-> Изменить ребро\n";
		cout << "5|-> Удалить ребро\n";
		cout << "6|-> Преобразование в список смежности\n";
		cout << "7|-> Преобразование в матрицу смежности\n";
		cout << "8|-> Преобразование в список ребер\n";
		cout << "0|-> Выход\n";
		cout << "Ваш выбор: ";
		cin >> choice; // Получить выбор пользователя
		if (choice == "1")
		{
			cout << "Чтение графа ...\n";
			string fileName; // Переменная для хранения имени файла
			cout << "\tВведите имя файла (Готовый: test.txt) > "; // Получить имя файла от пользователя
			cin >> fileName;
			start();
			graph.readGraph(fileName); // Считать граф из указанного файла
			finish();
		}
		else if (choice == "2")
		{
			cout << "Сохранение графа ...\n";
			string fileName;// Переменная для хранения имени файла
			cout << "\tВведите имя файла (Готовый: save.txt) > ";// Получить имя файла от пользователя
			cin >> fileName;
			start();
			graph.writeGraph(fileName);// Сохранить граф в указанный файл
			finish();
		}
		else if (choice == "3")
		{
			cout << "Добавление ребра ...\n";
			int from = 0;// Переменные для хранения номеров вершин и веса ребра
			int to = 0;
			int weight = 0;
			cout << "\tВведите \"из\" какой вершины (Счет от 0) > ";// Получить номер первой вершины от пользователя
			cin >> from;
			cout << "\tВведите \"в\" какую вершину (Счет от 0) > ";// Получить номер второй вершины от пользователя
			cin >> to;
			if (graph.is_weighted())// Если граф взвешенный
			{
				cout << "\tВведите вес ребра > ";// Получить значение веса нового ребра от пользователя
				cin >> weight;
			}
			start();
			graph.addEdge(from, to, weight);// Добавить ребро с указанными параметрами
			finish();
		}
		else if (choice == "4")
		{
			cout << "Изменение ребра ...\n";
			int from = 0;// Переменные для хранения номеров вершин и веса ребра
			int to = 0;
			int newWeight = 0;
			int oldWeight = 0;
			cout << "\tВведите \"из\" какой вершины (Счет от 0) > ";// Получить номер первой вершины от пользователя
			cin >> from;
			cout << "\tВведите \"в\" какую вершину (Счет от 0) > ";// Получить номер второй вершины от пользователя
			cin >> to;
			cout << "\tВведите новое значение веса ребра (Целое) > ";// Получить новое значение веса редактируемого ребра от пользователя
			cin >> newWeight;
			start();
			oldWeight = graph.changeEdge(from, to, newWeight);// Редактировать ребро с указанными параметрами	
			cout << "\tПрошлое значение веса ребра " << from << "-" << to << " было " << oldWeight << "\n";// Напечатать прежнее значение веса
			finish();
		}
		else if (choice == "5")
		{
			cout << "Удаление ребра ...\n";
			int from = 0;// Переменные для хранения номеров вершин
			int to = 0;
			cout << "\tВведите \"из\" какой вершины (Счет от 0) > ";// Получить номер первой вершины от пользователя
			cin >> from;
			cout << "\tВведите \"в\" какую вершину (Счет от 0) > ";// Получить номер второй вершины от пользователя
			cin >> to;
			start();
			graph.removeEdge(from, to);// Удалить указанное ребро
			finish();
		}
		else if (choice == "6")
		{
			start();
			graph.transformToAdjList();
			finish();
		}
		else if (choice == "7")
		{
			start();
			graph.transformToAdjMatrix();
			finish();
		}
		else if (choice == "8")
		{
			start();
			graph.transformToListOfEdges();
			finish();
		}
	} while (choice != "0");
	return 0;
}
