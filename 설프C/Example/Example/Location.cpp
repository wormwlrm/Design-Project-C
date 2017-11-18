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
	cout << "��ġ : " << setw(2) << LocationIndex << "(" << CoordX << ", " << CoordY << ") " << "\t������ : " << SightOfThisLocation.getSatisfaction() << " / �ҿ�ð� : " << setw(3) << SightOfThisLocation.getTime() << endl;
}