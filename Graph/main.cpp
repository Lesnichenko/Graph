#include "Graph.h"  // ���������� �������� ������ Graph
#include <iostream> // ����-�����
#include <fstream>  // �������� ����-�����
#include <ctime>	// ���������� ��� 
#include <cmath>	// ��������� ������� ��������

using namespace std;

double timeS, timeF;

clock_t start() // ����� �������
{ 
	timeS = (double) clock(); 
	return clock(); 
}

clock_t finish() // ���������� ������� � ����� ���������� � �������
{ 
	timeF = (double) clock(); 
	cout << "����� �����������: " << (timeF - timeS) / CLOCKS_PER_SEC<< " ������.\n\n";
	return clock(); 
}

int main(void)
{
	setlocale(LC_ALL, "Russian"); // ����������� ������� ��������
	Graph graph;	// ������� ������ ����
	string choice;	// ���������� ��� �������� ����������������� ������
	do	// ���������� ������������ � ��������� ���������
	{	// �������� �������� ����
		cout << "�������� �������� �� ������?\n";
		cout << "1|-> ������ ����� �� �����\n";
		cout << "2|-> ��������� ���� � ����\n";
		cout << "3|-> �������� �����\n";
		cout << "4|-> �������� �����\n";
		cout << "5|-> ������� �����\n";
		cout << "6|-> �������������� � ������ ���������\n";
		cout << "7|-> �������������� � ������� ���������\n";
		cout << "8|-> �������������� � ������ �����\n";
		cout << "0|-> �����\n";
		cout << "��� �����: ";
		cin >> choice; // �������� ����� ������������
		if (choice == "1")
		{
			cout << "������ ����� ...\n";
			string fileName; // ���������� ��� �������� ����� �����
			cout << "\t������� ��� ����� (�������: test.txt) > "; // �������� ��� ����� �� ������������
			cin >> fileName;
			start();
			graph.readGraph(fileName); // ������� ���� �� ���������� �����
			finish();
		}
		else if (choice == "2")
		{
			cout << "���������� ����� ...\n";
			string fileName;// ���������� ��� �������� ����� �����
			cout << "\t������� ��� ����� (�������: save.txt) > ";// �������� ��� ����� �� ������������
			cin >> fileName;
			start();
			graph.writeGraph(fileName);// ��������� ���� � ��������� ����
			finish();
		}
		else if (choice == "3")
		{
			cout << "���������� ����� ...\n";
			int from = 0;// ���������� ��� �������� ������� ������ � ���� �����
			int to = 0;
			int weight = 0;
			cout << "\t������� \"��\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> from;
			cout << "\t������� \"�\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> to;
			if (graph.is_weighted())// ���� ���� ����������
			{
				cout << "\t������� ��� ����� > ";// �������� �������� ���� ������ ����� �� ������������
				cin >> weight;
			}
			start();
			graph.addEdge(from, to, weight);// �������� ����� � ���������� �����������
			finish();
		}
		else if (choice == "4")
		{
			cout << "��������� ����� ...\n";
			int from = 0;// ���������� ��� �������� ������� ������ � ���� �����
			int to = 0;
			int newWeight = 0;
			int oldWeight = 0;
			cout << "\t������� \"��\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> from;
			cout << "\t������� \"�\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> to;
			cout << "\t������� ����� �������� ���� ����� (�����) > ";// �������� ����� �������� ���� �������������� ����� �� ������������
			cin >> newWeight;
			start();
			oldWeight = graph.changeEdge(from, to, newWeight);// ������������� ����� � ���������� �����������	
			cout << "\t������� �������� ���� ����� " << from << "-" << to << " ���� " << oldWeight << "\n";// ���������� ������� �������� ����
			finish();
		}
		else if (choice == "5")
		{
			cout << "�������� ����� ...\n";
			int from = 0;// ���������� ��� �������� ������� ������
			int to = 0;
			cout << "\t������� \"��\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> from;
			cout << "\t������� \"�\" ����� ������� (���� �� 0) > ";// �������� ����� ������ ������� �� ������������
			cin >> to;
			start();
			graph.removeEdge(from, to);// ������� ��������� �����
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
