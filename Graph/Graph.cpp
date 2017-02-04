#include "Graph.h"
#include <fstream>
#include <iostream>


Graph::Graph() // Описание создания пустого графа
{
	type = ' ';			// Тип графа пустой
	weighted = false;	// Граф не взвешенный
	oriented = false;	// Граф не ориентированный
	N = 0;				// У Графа нет вершин 
	M = 0;				// У Графа нет ребер
}

void readGraph(string fileName) 
{
	// Создаю объект типа файла и попытаться открыть файл с именем "fileName"
	ifstream file(fileName.c_str());

	// Если не удалось открыть файл
	if (!file.is_open())
	{
		cout << "Файл невозможно открыть!" << fileName << "\n";
		return;
	}
}

void addEdge(int from, int to, int weight) {}

void removeEdge(int from, int to) {}

int changeEdge(int from, int to, int newWeight) {}

void transformToAdjList() {}

void transformToAdjMatrix() {}

void transformToListOfEdges() {}

void writeGraph(string fileName) {}

bool is_weighted() {}