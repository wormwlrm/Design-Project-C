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
	int LocationIndex; // ������ �ε���
	float CoordX, CoordY; // ������ X, Y ��ǥ
	Sight SightOfThisLocation; // ���� �� ������
};

