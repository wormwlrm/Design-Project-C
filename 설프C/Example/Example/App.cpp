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
		cout << "1. 관광지 위주" << endl;
		cout << "2. 만족도 위주" << endl;
		cout << "3. 프로그램 종료" << endl;
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			cout << "사용자 시간 입력 : ";
			cin >> UserTime;
			search_Sights(UserTime);
			break;
		case 2:
			cout << "사용자 시간 입력 : ";
			cin >> UserTime;
			search_Satisfaction(UserTime);
			break;
		case 3:
			ExitProgram = true;
			break;
		default:
			cout << "다시 입력하세요" << endl;
			break;
		}
	}
}

void App::Greed(int here, int&This_Time, int Input_Time, int* visited, vector<int>& router1)
{
	// 현재 위치에서 가장 소요 시간이 적은 위치으로 이동 
	// 거기서 에 도착 가능한가를 검사

	int index;
	if (here == 28)//현재위치가 도착지이면 리턴
	{
		return;
	}

	int shortest;//가장 시간이 적게 걸리는 노드 탐색
	for (unsigned int i = 0; i < Adj2[here].size(); i++) //shortest 초기화 for문
	{
		if (here != i && *(visited + i) != 1 && i != 28)
		{
			shortest = Adj2[here].at(i).second;
			index = i;
			break;
		}
	}
	for (unsigned int i = 0; i < Adj2[here].size(); i++)  //shortest보다 더 작은게 있다면 갱신
	{
		if (shortest > Adj2[here].at(i).second && here != i && *(visited + i) != 1 && i != 28)  
		{
			shortest = Adj2[here].at(i).second;
			index = i;
		}
	}

	int Temp_time = This_Time + shortest;  //임시시간 = 현재까지 걸린시간 + 이번노드의 소요시간 

	if (Temp_time + D[index][28] > Input_Time) //만약 그 노드에서 도착지까지 가는 시간이 입력시간보다 많다면 경로 리턴 
	{
		router1.push_back(28);
		This_Time += D[here][28];
		return;
	}

	else if (*(visited + index) == 0 && Temp_time + D[index][28] <= Input_Time)  //아니라면 경로에 집어넣고 현재위치 갱신
	{
		*(visited + index) = 1;
		router1.push_back(index);
		This_Time = Temp_time;
		here = index;
	}

	bool isFalse = false; //모든 지역에 방문했는지 확인하는 곳
	for (int i = 0; i < 28; i++)
	{
		if (*(visited + i) == 0)
			isFalse = true;
	}
	if (isFalse == false)  // 모든 지역에 방문했다면 도착지로 간 후 리턴
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
	int visited[29] = { 1, 0 }; //출발지는 이미 방문했다고 설정
	vector<int> router1;
	router1.push_back(0);  //경로에 출발지를 넣어둔다

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
	cout << "들린 관광지 : " << router1.size() - 2 << endl;
	
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

void App::BackTracking(int Before, int Current, int Remain, int& MaxSatisfaction, int& VisitCount, int *visited, int(*D)[29], int(*P)[29]/*현재 위치, 남은 시간, 방문 배열, 거리 배열*/)
{
	Remain = Remain - ((D[Before][Current]) + LocationsList.at(Current)->getSightOfThisLocation()->getTime()); // 관광지 방문, 남은 시간 감소
	if (D[Current][28] > Remain) // 남은 시간 내에 도착지에 도착할 수 없으면
	{
		*(visited + Current) = 0; // 방문한 거 취소
		Remain = Remain + ((D[Before][Current]) + LocationsList.at(Current)->getSightOfThisLocation()->getTime()); // 방문 시간 반환
		return;
	}
	if (Current == 28) // 도착하면
	{
		*(visited + 28) = VisitCount;
		int TotalSatisfaction = 0;
		vector<int> SightVisited; // 관광지를 방문한 노드를 기록하는 벡터
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
			cout << endl << "누적 만족도는 " << TotalSatisfaction << "입니다." << endl;
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
			if (TimeCost[i][j] != -1) // 연결되어 있다면
			{
				pair<int, int> temp(j, TimeCost[i][j]); // i는 인접노드인 j로 갈 수 있고, 거리는 TimeCost[i][j]
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
	// D[i][j]의 숫자는 i에서 j로 가는 최소 거리를 의미한다.
	// P[i][j]는 i에서 j로 가는 경로를 구할 때, j에 도착하기 한 칸 전 지역의 인덱스를 의미한다. 숫자가 0이면 인접 노드라는 의미이다.

	int i, j, k;
	for (i = 0; i < 29; i++)
		for (j = 0; j < 29; j++)
		{
			D[i][j] = TimeCost[i][j]; // D 행렬 = W 행렬
			if (D[i][j] == -1) // 연결되지 않은 상태는
				D[i][j] = 99999; // 거리를 무한대로 설정

			P[i][j] = 0; // 경로를 0으로 초기화
			if (i == j) // 자기 자신으로 가는 길은
				P[i][j] = -1; // -1로 설정
		}

	for (i = 0; i < 29; i++) // i라는 점을 경유해서
	{
		for (j = 0; j < 29; j++) // j에서
		{
			for (k = 0; k < 29; k++) // k로 갈 때
			{
				if (D[j][k] > D[j][i] + D[i][k] || D[j][k] == -1) // 경유해서 가는 것이 더 빠르고 연결된 상태면
				{
					P[j][k] = i; // i는 k로 도착하기 직전에 방문하는 인덱스
					D[j][k] = D[j][i] + D[i][k]; // 더 빠른 거리를 갱신
				}
			}
		}
	}
}

vector<int> App::Dijkstra(int start, int vn) // 다익스트라함수
{
	vector<int> dist(vn, INT_MAX); // 정점수만큼 거리벡터 생성
	dist[start] = 0; //시작점 0으로 초기화

	priority_queue<pair<int, int>> shortest; //우선순위 큐 생성
	int* path = new int[vn];
	for (int i = 0; i < vn; i++)
	{
		path[i] = -1;
	}

	shortest.push(make_pair(0, start)); //우선순위큐에 (0,시작점) 삽입
	while (!shortest.empty())
	{
		int cost = -shortest.top().first; //비용
		int here = shortest.top().second; // 현재 위치
		shortest.pop(); //삭제

		if (dist[here] < cost) { //현재 위치의 거리 < 루트노드의 비용

			continue;
		}
		for (unsigned int i = 0; i < Adj[here].size(); i++) //이웃노드의 갯수만큼 포문 생성
		{
			int there = Adj[here][i].first; //연결된 이웃노드
			int nextDist = cost + Adj[here][i].second; //비용 + 연결된 이웃노드의 비용
			path[i] = there;
			if (dist[there] > nextDist) //dist의 거리 > 계산된 거리 
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
	ifstream loadLocationInfo("위치정보.txt");
	int _Index, _Satis, _Time;
	float _CoordX, _CoordY;
	string tempS;
	for (int i = 0; i < 5; i++) // 가장 첫 다섯 단어는 설명이라 제외
	{
		loadLocationInfo >> tempS;
	}
	for (int i = 0; i < 29; i++) // 총 29개의 위치를 넣음
	{
		loadLocationInfo >> _Index >> _Satis >> _CoordX >> _CoordY >> _Time;

		Sight* TempSight; // 관광지 생성
		TempSight = new Sight(_Satis, _Time);

		Location* TempLocation; // 지역 생성
		TempLocation = new Location(_Index, _CoordX, _CoordY, *TempSight);

		LocationsList.push_back(TempLocation); // 지역 벡터에 추가
	}
	loadLocationInfo.close();
}

void App::load_TimeCost_File()
{
	ifstream loadLeadTime("위치별소모시간.txt");
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

