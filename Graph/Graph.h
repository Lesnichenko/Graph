#ifndef GRAPH_H
#define GRAPH_H

#include <string> // библеотека для использования строк

using namespace std;

class Graph {
public:
	// Конструктор и Деструктор класса
	Graph();
	~Graph();

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
	char type;      // Тип текущего представления
	int N;          // Количество вершин
	int M;          // Количество ребер
	bool weighted;  // В случае true, если граф взвешенный, иначе false
	bool oriented;  // В случае true, если граф ориентированный, иначе false
};
#endif