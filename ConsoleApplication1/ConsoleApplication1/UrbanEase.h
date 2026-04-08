#pragma once


class Coordinates
{
private:
	double longitude;
	double latitude;
public:
	// Constructors
	Coordinates(double lon, double lat);
	Coordinates();
	// Copy Constructor
	Coordinates(const Coordinates& obj);
	// Getters
	double getLon() const;
	double getLat() const;
	// Setter
	void setLon(double longi);
	void setLat(double lati);
	//== Operator overloading
	bool  operator == (const Coordinates& obj);
	// << Friend Operator
	friend ostream& operator<<(ostream& out, const Coordinates& obj)
	{
		out << "(" << obj.latitude << ", " << obj.longitude << ")";
		return out;
	}
	// Destructor
	~Coordinates() {}
};