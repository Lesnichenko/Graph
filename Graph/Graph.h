#ifndef GRAPH_H
#define GRAPH_H

#include <string>	// библеотека для использования строк
#include <vector>   // Вектор - массив, который может изменять свой размер
#include <set>      // Множество - набор элементов одного типа
#include <map>      // Отображение - набор элементов "ключ-значение"
#include <tuple>    // Кортеж - N элементов, рассматриваемых как единое целое

using namespace std;

class Graph {
public:
	// Конструктор и Деструктор класса
	Graph();

	// Считывает граф из файла fileName
	void readGraph(string fileName);

	// Добавляет ребро с весом weight между from и to
	void addEdge(int from, int to, int weight);

	// Удаляет ребро между from и to
	void removeEdge(int from, int to);

	// Изменяет вес ребра между вершинами from и to на newWeight
	// Возвращает прежнее значение веса
	int changeEdge(int from, int to, int newWeight);

	// Преобразовывает граф в
	void transformToAdjList();      // список смежности
	void transformToAdjMatrix();    // матрицу смежности
	void transformToListOfEdges();  // список ребер
	
	// Сохраняет граф в файл fileName
	void writeGraph(string fileName);

	// Возвращает флаг взвешенности графа
	bool is_weighted();
private:
	void printGraph();// Выводит граф на печать
	char type;      // Тип текущего представления
	int N;          // Количество вершин
	int M;          // Количество ребер
	bool weighted;  // В случае true, если граф взвешенный, иначе false
	bool oriented;  // В случае true, если граф ориентированный, иначе false

	vector< vector< int > > adjMatrix;            // Матрица смежности
	map< int, set< pair< int, int > > > adjList;  // Список смежности
	set< tuple< int, int, int > > edgList;        // Список ребер
};
#endif