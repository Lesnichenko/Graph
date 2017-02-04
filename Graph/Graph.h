#ifndef GRAPH_H
#define GRAPH_H

#include <string> // ���������� ��� ������������� �����

using namespace std;

class Graph {
public:
	// ����������� � ���������� ������
	Graph();
	~Graph();

	// ��������� ���� �� ����� fileName
	void readGraph(string fileName);

	// ��������� ����� � ����� weight ����� from � to
	void addEdge(int from, int to, int weight);

	// ������� ����� ����� from � to
	void removeEdge(int from, int to);

	// �������� ��� ����� ����� ��������� from � to �� newWeight
	// ���������� ������� �������� ����
	int changeEdge(int from, int to, int newWeight);

	// ��������������� ���� �
	void transformToAdjList();      // ������ ���������
	void transformToAdjMatrix();    // ������� ���������
	void transformToListOfEdges();  // ������ �����
	
	// ��������� ���� � ���� fileName
	void writeGraph(string fileName);

	// ���������� ���� ������������ �����
	bool is_weighted();
private:
	char type;      // ��� �������� �������������
	int N;          // ���������� ������
	int M;          // ���������� �����
	bool weighted;  // � ������ true, ���� ���� ����������, ����� false
	bool oriented;  // � ������ true, ���� ���� ���������������, ����� false
};
#endif