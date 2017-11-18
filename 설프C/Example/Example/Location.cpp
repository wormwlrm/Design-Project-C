#include "Location.h"


Location::Location()
{
}

Location::Location(int _LocationIndex, float _CoordX, float _CoordY, Sight _SightOfThisLocation)
{
	LocationIndex = _LocationIndex;
	CoordX = _CoordX;
	CoordY = _CoordY;
	SightOfThisLocation = _SightOfThisLocation;
}

Location::~Location()
{
}

void Location::printLocationInfo()
{
	cout << "위치 : " << setw(2) << LocationIndex << "(" << CoordX << ", " << CoordY << ") " << "\t만족도 : " << SightOfThisLocation.getSatisfaction() << " / 소요시간 : " << setw(3) << SightOfThisLocation.getTime() << endl;
}