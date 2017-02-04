#include "Graph.h"
#include <fstream>
#include <iostream>


Graph::Graph() // �������� �������� ������� �����
{
	type = ' ';			// ��� ����� ������
	weighted = false;	// ���� �� ����������
	oriented = false;	// ���� �� ���������������
	N = 0;				// � ����� ��� ������ 
	M = 0;				// � ����� ��� �����
}

void readGraph(string fileName) 
{
	// ������ ������ ���� ����� � ���������� ������� ���� � ������ "fileName"
	ifstream file(fileName.c_str());

	// ���� �� ������� ������� ����
	if (!file.is_open())
	{
		cout << "���� ���������� �������!" << fileName << "\n";
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