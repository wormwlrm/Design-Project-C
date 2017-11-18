#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Sight
{
public:
	Sight();
	Sight(int _Satisfaction, int _Time);
	~Sight();

	int getSatisfaction() { return Satisfaction; };
	int getTime() { return Time; };
	void setSatisfaction(int _Satisfaction) { Satisfaction = _Satisfaction; };
	void setTime(int _Time) { Time = _Time; };

protected:
	int Satisfaction; // 관광지의 만족도
	int Time; // 관광지 방문에 걸리는 시간
};

