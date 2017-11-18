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
	void run(); // 실행 함수

public:
	// 생성자에 사용되는 함수
	void load_LocationInfo_File(); // 위치정보 파일 로드
	void load_TimeCost_File(); // 소모시간 파일 로드
	void set_Adjacent(); // 인접 노드 리스트를 세팅

	// 경우에 따라 호출되는 탐색 함수
	void search_Sights(int Input_Time); // 시간 내 최대한 많은 관광지 방문
	void search_Satisfaction(int UserTime); // 시간 내 최대한 많은 만족도 획득

	// 기본 탐색 알고리즘
	vector<int> Dijkstra(int start, int vn); // 우선순위 큐를 이용한 다익스트라 알고리즘
	void floyd_Algorithm(); // 플로이드 알고리즘
	void BackTracking(int Before, int Current, int Remain, int& VisitCount, int& TotalSatisfaction, int *Visited, int(*D)[29], int(*P)[29]);
	void Greed(int here, int&This_Time, int Input_Time, int* visited, vector<int>& router);
	pair<string, string> Result; // GUI로 출력할 결과값

private:
	int TimeCost[29][29]; // 소요 시간
	vector<Location*> LocationsList; // 위치 정보

private:
	int D[29][29]; // Distance의 줄임말, 플로이드 알고리즘으로 구한 노드 간 가장 짧은 거리
	int P[29][29]; // Path의 줄임말, 플로이드 알고리즘으로 구한 노드 간 경로
	vector<pair<int, int>> Adj[29]; // 인접 행렬
	vector<pair<int, int>> Adj2[29]; // 인접 행렬 + 관광지 방문	
};