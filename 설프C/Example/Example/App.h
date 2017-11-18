#pragma once
#include "Location.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
using namespace std;

class App
{
public:
	App();
	~App();
	void run(); // ���� �Լ�

public:
	// �����ڿ� ���Ǵ� �Լ�
	void load_LocationInfo_File(); // ��ġ���� ���� �ε�
	void load_TimeCost_File(); // �Ҹ�ð� ���� �ε�
	void set_Adjacent(); // ���� ��� ����Ʈ�� ����

	// ��쿡 ���� ȣ��Ǵ� Ž�� �Լ�
	void search_Sights(int Input_Time); // �ð� �� �ִ��� ���� ������ �湮
	void search_Satisfaction(int UserTime); // �ð� �� �ִ��� ���� ������ ȹ��

	// �⺻ Ž�� �˰���
	vector<int> Dijkstra(int start, int vn); // �켱���� ť�� �̿��� ���ͽ�Ʈ�� �˰���
	void floyd_Algorithm(); // �÷��̵� �˰���
	void BackTracking(int Before, int Current, int Remain, int& VisitCount, int& TotalSatisfaction, int *Visited, int(*D)[29], int(*P)[29]);
	void Greed(int here, int&This_Time, int Input_Time, int* visited, vector<int>& router);
	pair<string, string> Result; // GUI�� ����� �����

private:
	int TimeCost[29][29]; // �ҿ� �ð�
	vector<Location*> LocationsList; // ��ġ ����

private:
	int D[29][29]; // Distance�� ���Ӹ�, �÷��̵� �˰������� ���� ��� �� ���� ª�� �Ÿ�
	int P[29][29]; // Path�� ���Ӹ�, �÷��̵� �˰������� ���� ��� �� ���
	vector<pair<int, int>> Adj[29]; // ���� ���
	vector<pair<int, int>> Adj2[29]; // ���� ��� + ������ �湮	
};