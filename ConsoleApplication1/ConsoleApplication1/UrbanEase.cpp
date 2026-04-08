#include <iostream>
#include "UrbanEase.h"

using namespace std;


Coordinates :: Coordinates(double lon, double lat)
{
	longitude = lon;
	latitude = lat;
}
Coordinates :: Coordinates()
{
	longitude = 0;
	latitude = 0;
}
// Copy Constructor

Coordinates :: Coordinates(const Coordinates& obj)
{
	longitude = obj.longitude;
	latitude = obj.latitude;
}

// Getters
double Coordinates :: getLon() const
{
	return longitude;
}
double Coordinates :: getLat() const
{
	return latitude;
}
// Setter
void Coordinates :: setLon(double longi)
{
	longitude = longi;
}
void Coordinates :: setLat(double lati)
{
	latitude = lati;
}

//== Operator overloading
bool Coordinates ::  operator == (const Coordinates& obj)
{
	if (longitude == obj.longitude && latitude == obj.latitude)
	{
		return true;
	}
	else
	{
		return false;
	}

}