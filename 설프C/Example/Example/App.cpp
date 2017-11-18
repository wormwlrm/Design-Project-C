#include "App.h"

App::App()
{
	load_LocationInfo_File();
	load_TimeCost_File();
	set_Adjacent();
	floyd_Algorithm();
}

App::~App()
{

}

void App::run()
{
	bool ExitProgram = false;
	int Choice;
	int Start = 0, End = 0;
	int UserTime;
	while (!ExitProgram)
	{
		cout << "1. ������ ����" << endl;
		cout << "2. ������ ����" << endl;
		cout << "3. ���α׷� ����" << endl;
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			cout << "����� �ð� �Է� : ";
			cin >> UserTime;
			search_Sights(UserTime);
			break;
		case 2:
			cout << "����� �ð� �Է� : ";
			cin >> UserTime;
			search_Satisfaction(UserTime);
			break;
		case 3:
			ExitProgram = true;
			break;
		default:
			cout << "�ٽ� �Է��ϼ���" << endl;
			break;
		}
	}
}

void App::Greed(int here, int&This_Time, int Input_Time, int* visited, vector<int>& router1)
{
	// ���� ��ġ���� ���� �ҿ� �ð��� ���� ��ġ���� �̵� 
	// �ű⼭ �� ���� �����Ѱ��� �˻�

	int index;
	if (here == 28)//������ġ�� �������̸� ����
	{
		return;
	}

	int shortest;//���� �ð��� ���� �ɸ��� ��� Ž��
	for (unsigned int i = 0; i < Adj2[here].size(); i++) //shortest �ʱ�ȭ for��
	{
		if (here != i && *(visited + i) != 1 && i != 28)
		{
			shortest = Adj2[here].at(i).second;
			index = i;
			break;
		}
	}
	for (unsigned int i = 0; i < Adj2[here].size(); i++)  //shortest���� �� ������ �ִٸ� ����
	{
		if (shortest > Adj2[here].at(i).second && here != i && *(visited + i) != 1 && i != 28)  
		{
			shortest = Adj2[here].at(i).second;
			index = i;
		}
	}

	int Temp_time = This_Time + shortest;  //�ӽýð� = ������� �ɸ��ð� + �̹������ �ҿ�ð� 

	if (Temp_time + D[index][28] > Input_Time) //���� �� ��忡�� ���������� ���� �ð��� �Է½ð����� ���ٸ� ��� ���� 
	{
		router1.push_back(28);
		This_Time += D[here][28];
		return;
	}

	else if (*(visited + index) == 0 && Temp_time + D[index][28] <= Input_Time)  //�ƴ϶�� ��ο� ����ְ� ������ġ ����
	{
		*(visited + index) = 1;
		router1.push_back(index);
		This_Time = Temp_time;
		here = index;
	}

	bool isFalse = false; //��� ������ �湮�ߴ��� Ȯ���ϴ� ��
	for (int i = 0; i < 28; i++)
	{
		if (*(visited + i) == 0)
			isFalse = true;
	}
	if (isFalse == false)  // ��� ������ �湮�ߴٸ� �������� �� �� ����
	{
		router1.push_back(28);
		return;
	}
	Greed(here, This_Time, Input_Time, visited, router1);
}

void App::search_Sights(int Input_Time)
{
	if (Input_Time < 180)
	{
		return;
	}
	int Cost = 0;
	int visited[29] = { 1, 0 }; //������� �̹� �湮�ߴٰ� ����
	vector<int> router1;
	router1.push_back(0);  //��ο� ������� �־�д�

	stack<string> S;
	string Route;
	string tempS;
	Greed(0, Cost, Input_Time, visited, router1);

	for (unsigned int i = 0; i < router1.size() - 1; i++)
	{
		int temp = router1.at(router1.size() - i - 1);
		tempS =  "[" + to_string(router1.at(router1.size() - i - 1)) + "]";
		S.push(tempS);
		S.push(" - ");
		while (temp != router1.at(router1.size() - i - 2))
		{
			temp = P[router1.at(router1.size() - i - 2)][temp];
			tempS = to_string(temp);
			if (temp == 0)
				break;
			S.push(tempS);
			S.push(" - ");
		}
	}
	S.push("[0]");
	while (!S.empty())
	{
		Route.append(S.top());
		S.pop();
	}
	cout << Route << endl;;
	cout << "�鸰 ������ : " << router1.size() - 2 << endl;
	
	Result.first = Route;
	Result.second = to_string(router1.size() - 2);
}

void App::search_Satisfaction(int UserTime)
{
	int visited[29] = { 0, 0 };
	visited[0] = 1;
	int MaxSatisfaction = 0;
	int Remain = UserTime;
	int VisitCount = 1;
	BackTracking(0, 0, Remain, MaxSatisfaction, VisitCount, visited, D, P);
}

void App::BackTracking(int Before, int Current, int Remain, int& MaxSatisfaction, int& VisitCount, int *visited, int(*D)[29], int(*P)[29]/*���� ��ġ, ���� �ð�, �湮 �迭, �Ÿ� �迭*/)
{
	Remain = Remain - ((D[Before][Current]) + LocationsList.at(Current)->getSightOfThisLocation()->getTime()); // ������ �湮, ���� �ð� ����
	if (D[Current][28] > Remain) // ���� �ð� ���� �������� ������ �� ������
	{
		*(visited + Current) = 0; // �湮�� �� ���
		Remain = Remain + ((D[Before][Current]) + LocationsList.at(Current)->getSightOfThisLocation()->getTime()); // �湮 �ð� ��ȯ
		return;
	}
	if (Current == 28) // �����ϸ�
	{
		*(visited + 28) = VisitCount;
		int TotalSatisfaction = 0;
		vector<int> SightVisited; // �������� �湮�� ��带 ����ϴ� ����
		for (int i = 0; i < 29; i++)
		{
			if (*(visited + i) == VisitCount && VisitCount > 0)
			{
				SightVisited.push_back(i);
				TotalSatisfaction = TotalSatisfaction + LocationsList.at(i)->getSightOfThisLocation()->getSatisfaction();
				i = 0;
				VisitCount--;
			}
		}
		SightVisited.push_back(0);

		stack<string> S;
		string tempS;
		for (unsigned int i = 0; i < SightVisited.size() - 1; i++)
		{
			int temp = SightVisited.at(i);
			tempS = "[" + to_string(SightVisited.at(i)) + "]";
			S.push(tempS);
			S.push(" - ");
			while (temp != SightVisited.at(i + 1))
			{
				temp = P[SightVisited.at(i + 1)][temp];
				if (temp == 0)
					break;
				tempS = to_string(temp);
				S.push(tempS);
				S.push(" - ");
			}
		}
		S.push("[0]");
		string Route;
		while (!S.empty())
		{
			Route.append(S.top());
			S.pop();
		}
		if (TotalSatisfaction >= MaxSatisfaction)
		{
			MaxSatisfaction = TotalSatisfaction;
			cout << endl << "���� �������� " << TotalSatisfaction << "�Դϴ�." << endl;
		}
		Result.first = Route;
		Result.second = to_string(TotalSatisfaction);
		return;
	}
	*(visited + Current) = VisitCount++;
	for (int i = 0; i < 29; i++)
	{
		if (*(visited + i) == 0)
		{
			BackTracking(Current, i, Remain, MaxSatisfaction, VisitCount, visited, D, P);
		}
	}
}

void App::set_Adjacent()
{
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			if (TimeCost[i][j] != -1) // ����Ǿ� �ִٸ�
			{
				pair<int, int> temp(j, TimeCost[i][j]); // i�� ��������� j�� �� �� �ְ�, �Ÿ��� TimeCost[i][j]
				Adj[i].push_back(temp);
			}
		}
	}

	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 29; j++) {
			for (unsigned int x = 0; x < LocationsList.size(); x++) {
				if (LocationsList.at(x)->getLocationIndex() == j)
				{
					pair<int, int> temp(j, Dijkstra(i, 29).at(j) + LocationsList.at(x)->getSightOfThisLocation()->getTime());
					Adj2[i].push_back(temp);
				}
			}
		}
	}
}

void App::floyd_Algorithm()
{
	// D[i][j]�� ���ڴ� i���� j�� ���� �ּ� �Ÿ��� �ǹ��Ѵ�.
	// P[i][j]�� i���� j�� ���� ��θ� ���� ��, j�� �����ϱ� �� ĭ �� ������ �ε����� �ǹ��Ѵ�. ���ڰ� 0�̸� ���� ����� �ǹ��̴�.

	int i, j, k;
	for (i = 0; i < 29; i++)
		for (j = 0; j < 29; j++)
		{
			D[i][j] = TimeCost[i][j]; // D ��� = W ���
			if (D[i][j] == -1) // ������� ���� ���´�
				D[i][j] = 99999; // �Ÿ��� ���Ѵ�� ����

			P[i][j] = 0; // ��θ� 0���� �ʱ�ȭ
			if (i == j) // �ڱ� �ڽ����� ���� ����
				P[i][j] = -1; // -1�� ����
		}

	for (i = 0; i < 29; i++) // i��� ���� �����ؼ�
	{
		for (j = 0; j < 29; j++) // j����
		{
			for (k = 0; k < 29; k++) // k�� �� ��
			{
				if (D[j][k] > D[j][i] + D[i][k] || D[j][k] == -1) // �����ؼ� ���� ���� �� ������ ����� ���¸�
				{
					P[j][k] = i; // i�� k�� �����ϱ� ������ �湮�ϴ� �ε���
					D[j][k] = D[j][i] + D[i][k]; // �� ���� �Ÿ��� ����
				}
			}
		}
	}
}

vector<int> App::Dijkstra(int start, int vn) // ���ͽ�Ʈ���Լ�
{
	vector<int> dist(vn, INT_MAX); // ��������ŭ �Ÿ����� ����
	dist[start] = 0; //������ 0���� �ʱ�ȭ

	priority_queue<pair<int, int>> shortest; //�켱���� ť ����
	int* path = new int[vn];
	for (int i = 0; i < vn; i++)
	{
		path[i] = -1;
	}

	shortest.push(make_pair(0, start)); //�켱����ť�� (0,������) ����
	while (!shortest.empty())
	{
		int cost = -shortest.top().first; //���
		int here = shortest.top().second; // ���� ��ġ
		shortest.pop(); //����

		if (dist[here] < cost) { //���� ��ġ�� �Ÿ� < ��Ʈ����� ���

			continue;
		}
		for (unsigned int i = 0; i < Adj[here].size(); i++) //�̿������ ������ŭ ���� ����
		{
			int there = Adj[here][i].first; //����� �̿����
			int nextDist = cost + Adj[here][i].second; //��� + ����� �̿������ ���
			path[i] = there;
			if (dist[there] > nextDist) //dist�� �Ÿ� > ���� �Ÿ� 
			{
				dist[there] = nextDist;
				shortest.push(make_pair(-nextDist, there));
				path[i] = there;
			}
		}
	}
	return dist;
}

void App::load_LocationInfo_File()
{
	ifstream loadLocationInfo("��ġ����.txt");
	int _Index, _Satis, _Time;
	float _CoordX, _CoordY;
	string tempS;
	for (int i = 0; i < 5; i++) // ���� ù �ټ� �ܾ�� �����̶� ����
	{
		loadLocationInfo >> tempS;
	}
	for (int i = 0; i < 29; i++) // �� 29���� ��ġ�� ����
	{
		loadLocationInfo >> _Index >> _Satis >> _CoordX >> _CoordY >> _Time;

		Sight* TempSight; // ������ ����
		TempSight = new Sight(_Satis, _Time);

		Location* TempLocation; // ���� ����
		TempLocation = new Location(_Index, _CoordX, _CoordY, *TempSight);

		LocationsList.push_back(TempLocation); // ���� ���Ϳ� �߰�
	}
	loadLocationInfo.close();
}

void App::load_TimeCost_File()
{
	ifstream loadLeadTime("��ġ���Ҹ�ð�.txt");
	int temp;
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			loadLeadTime >> temp;
			TimeCost[i][j] = temp;
		}
	}
	loadLeadTime.close();
}

