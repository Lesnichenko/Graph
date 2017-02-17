#include "Graph.h"      // ����������� ����� Graph.h
#include <fstream>      // ���������� ��������� �����-������
#include <iostream>     // ���������� ����������� �����-������
#include <sstream>      // ���������� ���������� �����-������
#include <limits>       // ���������� ��� ���������� �����
#include <algorithm>    // ���������� ����������� ����������

using namespace std;	// ����������� ������ ��� ������ � ��������� �������

Graph::Graph()			// �������� �������� ������� �����
{						// ������ �������� ������� �����
	type = ' ';			// ��� ����� ������
	weighted = false;	// ���� �� ����������
	oriented = false;	// ���� �� ���������������
	N = 0;				// � ����� ��� ������ 
	M = 0;				// � ����� ��� �����
}						// ���������� �������� ������� �����

void Graph::readGraph(string fileName)							// ������� ������ ����� � �����
{																// ������ ������� ������
	ifstream file(fileName.c_str());							// ������� ������ ����� � ���������� ������� ���� � ������ "fileName"
	if (!file.is_open())										// ���� �� ������� ������� ���� 
	{															 // ������ ����������
		cout << "���������� ������� ����" << fileName << "\n";	 // ����� ������ � ��������� ������
		return;													 // ����� �� ��������
	}															// � ������ 
	else														// ���� ���� ��������
		cout << "������ ����� �� ����� " << fileName << "...\n"; // �� ������� � ����������� ���������� �������
	file >> type;												// ����������, ����� ��� ����������� ������������� ����� ������ � �����
	switch (type)												// �� ���� ����� ���������� 
	{															// ����� ����� ������������
	case('C') :													// ���� � ����� ������ ����, �������������� � ���� ������� ���������
	{															// ��
		adjMatrix.clear();										// �������� ������� ���������� ������� ���������
		file >> N;												// ������� ���������� ������
		file >> oriented;										// ������� ��������� ����������������� �����
		file >> weighted;										// ������� ��������� ������������ �����
		for (int i = 0; i < N; i++)								// ������� ��� ������� ���������
		{														 // ������ �� �������
			vector<int> row;									 // ������ ��� �������� ������� ������
			for (int j = 0; j < N; j++)							  // ������ �� ��������
			{													  // ������ �����
				int a;											  // ������� ��������� ���� int ��� �������� �������� �����
				file >> a;										  // ������� ������� �����
				row.push_back(a);								  // ��������� ��������� ����� � row
			}													  // ����� �����
			adjMatrix.push_back(row);							 // ��������� ��������� ������ � ������� ���������
		}														 //
		break;													// ����� �� switch
	}															// � ������
	case('L') :													// ���� � ����� ������ ����, �������������� � ���� ������ ���������
	{															// ��
		adjList.clear();										// �������� ������� ���������� ������ ���������
		file >> N;												// ������� ���������� ������
		file >> oriented;										// ������� ��������� ����������������� �����
		file >> weighted;										// ������� ��������� ������������ �����
		file.ignore(numeric_limits<streamsize>::max(), '\n');	// ���������� ������ ������ ����� �� ����� ������
		for (int from = 0; from < N; from++)					// ������� N ������ ������
		{														 //
			string rowStr;										 // ������ ��� �������� ������ ������ ������� �������
			getline(file, rowStr);								 // ������� ������� ������
			istringstream iss(rowStr);							 // ��������� ����� ����� (��� ��������� row �� ��������� ������)
			set< pair<int, int> > row;							 // ���������� ��� �������� ������ ������� �������
			while (!iss.eof() && !iss.str().empty())			 // ������ �� rowStr
			{													  //
				int to = 0;										  // ���������� ��� �������� ������ �������� �������
				iss >> ws >> to;								  // ������� �������� �������
				int weight = 0;									  // ���������� ��� �������� ���� �����
				if (weighted)									  // ���� ������ ���������� ����
				{												   // ��
					iss >> ws >> weight;						   // ������� ��� �����
				}												   // �����
				row.insert(make_pair(to, weight));				  // ��������� ��������� ����� � ������ ������
				iss.ignore(128);								  // ������������ ���������� ������� � ������
			};													  // ���������� �����
			adjList[from] = row;								 // �������� ������ ������ ��������� ������� � ������ ���������
		}														//
		break;													// ����� �� switch
	}															// � ������
	case('E') :													// ���� � ����� ������ ����, �������������� � ���� ������ �����
	{															//
		edgList.clear();										// �������� ������� ���������� ������ �����
		file >> N;												// ������� ���������� ������
		file >> M;												// ������� ���������� �����
		file >> oriented;										// ������� ��������� ����������������� �����
		file >> weighted;										// ������� ��������� ������������ �����
		file.ignore(numeric_limits<streamsize>::max(), '\n');	// ���������� ������ ������ ����� �� ����� ������
		for (int i = 0; i < M; i++)								// ������� M �����
		{														 // ������ �����
			string rowStr;										 // ������ ��� �������� �������� �����
			getline(file, rowStr);								 // ������� ������� ������
			istringstream iss(rowStr);							 // ��������� ����� ����� (��� ��������� row �� ��������� ������)
			tuple<int, int, int> row;							 // ���������� ��� �������� �������� �����
			while (!iss.eof() && !rowStr.empty())				 // ������ �� rowStr
			{													  // ������ �����
				int from = 0;									  // ������� ���������� ��� ������ ������ �����
				iss >> from;									  // ������� ������ �����
				int to = 0;										  // ������� ���������� ��� ������ ����� �����
				iss >> to;										  // ������� ����� �����
				int weight = 0;									  // ���������� ��� �������� ���� �����
				if (weighted)									  // ���� ������ ���������� ����
				{												   // ��
					iss >> weight;								   // ������� ��� �����
				}												   // ����� ��������� ��������� ����� � ������ ������
				get<0>(row) = from;								  // �� ����� �������
				get<1>(row) = to;								  // � ����� �������
				get<2>(row) = weight;							  // � �� ���
			}													 // ����� �����
			edgList.insert(row);								// �������� ����� � ������ �����
		}														// ����� �����
		break;													// ����� switch
	}															// � ������
	default:													// ����������� 
	{															 // ���-�� ���� ��
		cout << "���������� ���������� ��� ������������� �����\n"; // �������� �� ������
		return;													 // �����
		break;													 // �� ������
	}															// ����
	}															// ��� ������ ������ ��
	cout << "������ ����� ... ���������\n";						// ����� ��������� ������ ��������
	printGraph();												// ���������� ����
}																// ���������� ������ �������� ������ �����

void Graph::addEdge(int from, int to, int weight)
{
	cout << "���������� ����� �� " << from << " � " << to << ", � ����� " << weight << "...\n";
	switch (type)
	{
	case('C'):// ���� ������� ������������� - ������� ���������
		{
			if (weight == 0)// ���� �������� ��������� weight ����� 0, ��� ����� �������� �������� �����
			{
				cout << "���������� �������� ����� ��" << from << " � " << to << ", ��� ����� ����� ����\n";
				return;
			}
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// ��������� ��������� � ����������� �������
			{
				cout << "\n���������� �������� ����� ��" << from << " � " << to << ", ����� �� ������� �������\n";
				return;
			}
			adjMatrix[from][to] = weight;// ���������� � ��������������� ������� �������� ����
			adjMatrix[to][from] = weight;// ���������� �������� ������������� �������� (�������� ������� ���������)
			break;
		}
	case('L'):// ���� ������� ������������� - ������ ���������
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// �������� ����������� - ��������� �� ������ ������ ������� � ������ ���������
				fromIt = adjList.find(from);// ����� � ������ ��������� ������ �����
				if (fromIt == adjList.end())// ���� �� �������
				{	
					cout << "\n���������� �������� ����� ��" << from << " � " << to << ", ����� �� �������\n";// �������� �� ������
					return;
				}
				set< pair<int, int> >::iterator toIt;// �������� ��������� - ��������� �� �������� ������� � ������ ������ ���������
				if (weighted)// ���� ���� ����������
				{
					toIt = fromIt->second.find(make_pair(to, weight));// ����� ������� ������� �������, ��������� ��������� ���
				}
				else    // ���� ���� ������������
				{
					toIt = fromIt->second.find(make_pair(to, 0));// ����� ������� ������� �������, ��������� � �������� ���� 0
				}
				
				if (toIt != fromIt->second.end())// ���� ������� ���-�� �����
				{
					cout << "\n���������� �������� ����� ��" << from << " � " << to << ", ����� ��� ����������\n";// �������� �� ������
					return;
				}
				if (weighted)// ���� ���� ����������
				{
					fromIt->second.insert(make_pair(to, weight));// �������� ����� �������� �������, ��������� ����� ��������� ���
				}
				else    // ���� ���� ������������
				{
					fromIt->second.insert(make_pair(to, 0));// �������� ����� �������� �������, ��������� ����� ��� 0
				}
				if (!oriented)// ���� ���� �����������������, �� �������� ����� ����� � �������� �����������
				{
					if (weighted)// ���� ���� ����������
					{
						adjList[to].insert(make_pair(from, weight));// ������������ ��������� ���
					}
					else    // ���� ���� ������������
					{
						adjList[to].insert(make_pair(from, 0));// ������������ ��� 0
					}
				}
				break;
			}
	case('E'): // ���� ������� ������������� - ������� �����
			{
				set< tuple<int, int, int> >::iterator itForward = edgList.end();// �������� ��������� - ��������� �� ����� � ������ �����
				set< tuple<int, int, int> >::iterator itBackward = edgList.end();
				itForward = find_if(edgList.begin(), edgList.end(),// ���������, ���������� �� ����������� �����
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
					if (itForward != edgList.end() || itBackward != edgList.end())// ���� ���-�� �����
					{
						cout << "\n���������� �������� ����� ��" << from << " � " << to << ", ����� ��� ����������\n";// �������� �� ������
						return;
					}
					if (weighted)// �������� ��������� �����
					{
						edgList.insert(make_tuple(from, to, weight));
					}
					else
					{
						edgList.insert(make_tuple(from, to, 0));
					}
					break;
				}
				default:// ���� ������ ���
				{
					cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
					return;
					break;
				}
	}
	M++;// ��������� ������� �����
	cout << "���������� ����� ... ���������\n";
	printGraph();// ���������� ����
}

void Graph::removeEdge(int from, int to)
{
	cout << "�������� ����� �� " << from << " � " << to << "...\t";
	switch (type)
	{
	case('C'):// ���� ������� ������������� - ������� ���������
		{
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// ��������� ��������� � ����������� �������
			{
				cout << "\n���������� ������� ����� �� " << from << " � " << to << ", ����� �� �������\n";
				return;
			}
			adjMatrix[from][to] = 0;// ���������� � ��������������� ������� �������� ���� � 0
			adjMatrix[to][from] = 0;// ���������� �������� ������������� �������� (�������� ������� ���������) � 0
			break;
		}
	case('L'):// ���� ������� ������������� - ������ ���������
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// �������� ����������� - ��������� �� ������ ������ ������� � ������ ���������
				set< pair<int, int> >::iterator toIt;// �������� ��������� - ��������� �� �������� ������� � ������ ������ ���������
				fromIt = adjList.find(from);// ����� � ������ ��������� ������ �����
				if (fromIt != adjList.end())// ���� �������
				{
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// ����� ����� ������� �������, ���������� ������ �����, ������� ���������� �������
						[&to](const pair<int, int>& edge)
					{
						if (edge.first == to) return true;
						return false;
					});
					if (toIt != fromIt->second.end())// ���� ������� ���-�� �����
					{
						fromIt->second.erase(toIt);// ������� ��������� �����
					}
				}
				if (!oriented)// ���� ���� �����������������, �� ������� ����� ����� � �������� �����������
				{
					fromIt = adjList.find(to);// ����� � ������ ��������� ������ �����
					if (fromIt == adjList.end())// ���� �� �������
					{
						return;// ������� �� ����������, ������� ������
					}
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// ����� ����� ������� �������, ���������� ������ �����, ������� ���������� �������
						[&from](const pair<int, int>& edge)
					{
						if (edge.first == from) return true;
						return false;
					});
					if (toIt == fromIt->second.end())// ���� �� ������� ������ �����
					{
						
						cout << "\n���������� ������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������ (� ����������������� ����� ����� ������ ���� � ����� ������������)
						return;
					}
					fromIt->second.erase(toIt);// ������� ��������� �����
				}
				break;
			}
	case('E'): // ���� ������� ������������� - ������� �����
				{
					set< tuple<int, int, int> >::iterator itForward = edgList.end();// �������� ��������� - ��������� �� ����� � ������ �����
					itForward = find_if(edgList.begin(), edgList.end(),// ���������, ���������� �� ��������� �����
						[&from, &to](const tuple<int, int, int>& edge){
						if (get<0>(edge) == from && get<1>(edge) == to) return true;
						return false;
					});
					if (itForward != edgList.end())// ���� ���-�� �����, �� ������� ��������� �����
					{
						edgList.erase(itForward);
					}
					if (itForward == edgList.end())// ���� ������ ������ ���
					{
						cout << "\n���������� ������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������
						return;
					}
					break;
				}
	default:// ���� ������ ���
				{
					cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
					return;
					break;
				}
	}
	M--;// ��������� ������� �����
	cout << "�������� ����� ... ���������\n";
	printGraph();// ���������� ����
}

int Graph::changeEdge(int from, int to, int newWeight)
{
	cout << "�������� ��� ����� �� " << from << " � " << to << ", �� ����� ��� " << newWeight << "...\n";
	if (!weighted)// ���� ���� ������������
	{
		cout << "\t� ���������, �� �� ������ �������� ��� ����� ������������� �����\n";// �������� �� ������ (� ����� ��� �����, �������������� ������)
		return -1;
	}
	int oldWeight = 0;
	switch (type)
	{
	case('C'):// ���� ������� ������������� - ������� ���������
		{
			if (max(from, to) > adjMatrix.size() || min(from, to) < 0)// ��������� ��������� � ����������� �������
			{
				cout << "\n���������� �������� ����� �� " << from << " � " << to << ", ����� �� �������\n";
				return -1;
			}
			oldWeight = adjMatrix[from][to];// ��������� ������� �������� ����
			adjMatrix[from][to] = newWeight;// ���������� � ��������������� ������� �������� ���� � newWeight
			adjMatrix[to][from] = newWeight;// ���������� �������� ������������� �������� (�������� ������� ���������) � newWeight
			break;
		}
	case('L'):// ���� ������� ������������� - ������ ���������
			{
				map< int, set< pair<int, int> > >::iterator fromIt;// �������� ����������� - ��������� �� ������ ������ ������� � ������ ���������
				fromIt = adjList.find(from);// ����� � ������ ��������� ������ �����
				if (fromIt == adjList.end())// ���� �� �������
				{
					cout << "\n���������� �������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������
					return -1;
				}
				fromIt->second.insert(make_pair(1, 2));
				set< pair<int, int> >::iterator toIt;// �������� ��������� - ��������� �� �������� ������� � ������ ������ ���������
				toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// ����� ����� ������� �������, ���������� ������ �����, ������� ���������� ��������
					[&to](const pair<int, int>& edge)
				{
					if (edge.first == to) return true;
					return false;
				});
				if (toIt == fromIt->second.end())// ���� �� ������� ������ �����
				{
					
					cout << "\n���������� �������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������
					return -1;
				}
				oldWeight = toIt->second;// ��������� ������� �������� ����
				pair<int, int> copy = *toIt;// ��������� ����� ��������� ���
				copy.second = newWeight;
				fromIt->second.erase(toIt);
				fromIt->second.insert(copy);
				if (!oriented)// ���� ���� �����������������, �� �������� ����� ����� � �������� �����������
				{
					fromIt = adjList.find(to);// ����� � ������ ��������� ������ �����
					if (fromIt == adjList.end())// ���� �� �������
					{
						return -1;// ������� �� ����������, ������� ������
					}
					toIt = find_if(fromIt->second.begin(), fromIt->second.end(),// ����� ����� ������� �������, ���������� ������ �����, ������� ���������� �������
						[&from](const pair<int, int>& edge)
					{
						if (edge.first == from) return true;
						return false;
					});
					if (toIt == fromIt->second.end())// ���� �� ������� ������ �����
					{
						
						cout << "\n���������� �������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������ (� ����������������� ����� ����� ������ ���� � ����� ������������)
						return -1;
					}
					pair<int, int> copy = *toIt;// ��������� ����� ��������� ���
					copy.second = newWeight;
					fromIt->second.erase(toIt);
					fromIt->second.insert(copy);
					break;
				}
			}
	case('E'):// ���� ������� ������������� - ������� �����
				{
					set< tuple<int, int, int> >::iterator itForward = edgList.end();// �������� ��������� - ��������� �� ����� � ������ �����
					set< tuple<int, int, int> >::iterator itBackward = edgList.end();
					itForward = find_if(edgList.begin(), edgList.end(),// ���������, ���������� �� ���������� �����
						[&from, &to](const tuple<int, int, int>& edge){
						if (get<0>(edge) == from && get<1>(edge) == to) return true;
						return false;
					});
					if (!oriented)// ��� ������������������ ��������� ����� ����� � �������� �����������
					{
						itBackward = find_if(edgList.begin(), edgList.end(),
							[&from, &to](const tuple<int, int, int>& edge){
							if (get<0>(edge) == to && get<1>(edge) == from) return true;
							return false;
						});
					}
					if (itForward != edgList.end())// ���� ���-�� �����, �� �������� ��������� �����
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
					if (itForward == edgList.end() && itBackward == edgList.end())// ���� ������ ������ ���
					{
						cout << "\n���������� �������� ����� �� " << from << " � " << to << ", ����� �� �������\n";// �������� �� ������
						return -1;
					}
					break;
				}
			default:// ���� ������ ���
			{
				cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
				return 0;
				break;
			}
	}
	cout << "��������� ���� ����� ... ���������\n";
	printGraph();// ���������� ����
	return oldWeight;// ������� ������� �������� ����
}

void Graph::transformToAdjList()
{
	cout << "�������������� ����� �� ";
	switch (type)// �������������� � ����������� �� ����
	{
	case('C') :
	{
		cout << " ������� ��������� � ������ ��������� ...\n";
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
		cout << " c������ ��������� � ������ ��������� ...\n";
		break;
	}
	case('E') :
	{
		cout << " c������ ����� � ������ ���������...\n";
		adjList.clear();
		for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
		{
			adjList[get<0>(*it)].insert(make_pair(get<1>(*it), get<2>(*it)));
		}
		edgList.clear();
		break;
	}
	default:// ���� ������ ���
	{
		cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
		return;
		break;
	}
	}
	type = 'L';
	cout << "�������������� � ������ ��������� ... ���������\n";
	printGraph();
}

void Graph::transformToAdjMatrix()
{
	cout << "�������������� ����� ��  ";
	switch (type)// �������������� � ����������� �� ����
	{
	case('C') :
	{
		cout << " ������� ��������� � ������� ��������� ...\t";
		break;
	}
	case('L') :
	{
		cout << " c������ ��������� � ������� ��������� ...\t";
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
		cout << " ������ ����� � ������� ��������� ...\t";
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
	default:// ���� ������ ���
	{
		cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
		return;
		break;
	}
	}
	type = 'C';
	cout << "�������������� � ������� ��������� ... ���������\n";
	printGraph();
}

void Graph::transformToListOfEdges()
{
	cout << "�������������� ����� �� ";
	switch (type)// �������������� � ����������� �� ����
	{
	case('C'):
		{
			cout << " ������� ��������� � ������ ����� ...\n";
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
			cout << " c������ ��������� � ������ ����� ...\n";
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
			cout << " ������ ����� � ������ ����� ...\n";
			break;
		}
	default:// ���� ������ ���
	{
		cout << "\n���������� ���������� ��� ������������� �����\n";// �������� �� ������
		return;
		break;
	}
	}
	type = 'E';
	cout << "�������������� � ������ ����� ... ���������\n";
	printGraph();
}

bool Graph::is_weighted()
{
	return weighted;
}

void Graph::printGraph()
{
	cout << "����� ����� (";
	if (oriented)// ���������� ���� �����������������
	{
		cout << "���������������, ";
	}
	else
	{
		cout << "�� ���������������, ";
	}
	if (weighted)// ���������� ���� ������������
	{
		cout << "����������, ";
	}
	else
	{
		cout << "�� ����������, ";
	}
	if (type == 'C')// ���� ������� ������������� - ������� ���������
	{
		cout << "������� ���������) ...\n";
		// ������ �� �������
		for (size_t i = 0; i<adjMatrix.size(); i++)
		{
			// ������ �� ��������
			for (size_t j = 0; j<adjMatrix[i].size(); j++)
			{
				// ���������� ������� �������
				cout << adjMatrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
	else    // ���� ������� ������������� - ������ ���������
		if (type == 'L')
		{
			cout << "������ ���������) ...\n";
			// ������ �� �������
			for (map< int, set< pair<int, int> > >::iterator fromIt = adjList.begin(); fromIt != adjList.end(); fromIt++)
			{
				// ������ �� ��������
				for (set< pair<int, int> >::iterator toIt = fromIt->second.begin(); toIt != fromIt->second.end(); toIt++)
				{
					cout << toIt->first;// ���������� ����� �������� �����
					if (weighted)// ���� ���� ����������
					{
						cout << " " << toIt->second;// ���������� ��� �������� �����
					}
					cout << " ";
				}
				cout << "\n";
			}
		}
		else    // ���� � ����� ������ ����, �������������� � ���� ������ �����
			if (type == 'E')
			{
				cout << "������ �����) ...\n";
				// ������ �� �������
				for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
				{
					cout << get<0>(*it) << " ";// ���������� ������ �������� �����
					cout << get<1>(*it);// ���������� ����� �������� �����
					if (weighted)// ���� ���� ����������
					{
						cout << " " << get<2>(*it);// ���������� ��� �������� �����
					}
					cout << "\n";
				}
			}
			else    // ���� � ����� ���-�� ����
			{
				cout << "���������� ���������� ��� ������������� �����\n";// �������� �� ������
				return;
			}
}

void Graph::writeGraph(string fileName)
{
	ofstream file(fileName.c_str());// ������� ������ ����� � ���������� ������� ���� � ������ "fileName"
	if (!file.is_open())// ���� �� ������� ������� ����, ������ ����������
	{
		cout << "���������� ������� ���� " << fileName << "\n";
		return;
	}
	cout << "������ ����� � ���� " << fileName << " ...\n";
	
	file << type << " ";// ��������� ��� �������� �������������

	
	if (type == 'C')// ���� ������� ������������� - ������� ���������
	{
		file << adjMatrix.size() << "\n";// ��������� ���������� ������
		file << oriented << " ";// ��������� ���� �����������������
		file << weighted << "\n";// ��������� ���� ������������
		// ������ �� �������
		for (size_t i = 0; i<adjMatrix.size(); i++)
		{
			// ������ �� ��������
			for (size_t j = 0; j<adjMatrix[i].size(); j++)
			{
				// ��������� ������� �������
				file << adjMatrix[i][j] << " ";
			}
			file << "\n";
		}
	}
	else    // ���� ������� ������������� - ������ ���������
		if (type == 'L')
		{
			file << N << "\n";// ��������� ���������� ������
			file << oriented << " ";// ��������� ���� ����������������� �����
			file << weighted << "\n";// ��������� ���� ������������ �����
			// ������ �� �������
			for (map< int, set< pair<int, int> > >::iterator fromIt = adjList.begin(); fromIt != adjList.end(); fromIt++)
			{
				// ������ �� ��������
				for (set< pair<int, int> >::iterator toIt = fromIt->second.begin(); toIt != fromIt->second.end(); toIt++)
				{
					// ���������� ����� �������� �����
					file << toIt->first;
					// ���� ���� ����������
					if (weighted)
					{
						// ���������� ��� �������� �����
						file << " " << toIt->second;
					}
					file << " ";
				}

				file << "\n";
			}
		}
		else    // ���� ������� ������������� - ������ �����
			if (type == 'E')
			{
				file << N << " ";// ��������� ���������� ������
				file << M << "\n";// ��������� ���������� �����
				file << oriented << " ";// ��������� ���� ����������������� �����
				file << weighted << "\n";// ��������� ���� ������������ �����
				// ������ �� �������
				for (set< tuple<int, int, int> >::iterator it = edgList.begin(); it != edgList.end(); it++)
				{
					// ��������� ������ �������� �����
					file << get<0>(*it) << " ";
					// ��������� ����� �������� �����
					file << get<1>(*it);
					// ���� ���� ����������
					if (weighted)
					{
						// ��������� ��� �������� �����
						file << " " << get<2>(*it);
					}
					file << "\n";
				}
			}
			else    // ���� � ����� ���-�� ����
			{
				// �������� �� ������
				cout << "���������� ���������� ��� ������������� �����\n";
				return;
			}

	cout << "������ ����� � ���� ... ���������\n";
}
