#pragma once
#include "Sight.h"

class Location
{
public:
	Location();
	Location(int LocationIndex, float CoordX, float CoordY, Sight SightOfThisLocation);
	~Location();
	void printLocationInfo();

	int getLocationIndex() { return LocationIndex; };
	float getCoordX() { return CoordX; };
	float getCoordY() { return CoordY; };
	Sight* getSightOfThisLocation() { return &SightOfThisLocation; };

private:
	int LocationIndex; // 지역의 인덱스
	float CoordX, CoordY; // 지역의 X, Y 좌표
	Sight SightOfThisLocation; // 지역 내 관광지
};

