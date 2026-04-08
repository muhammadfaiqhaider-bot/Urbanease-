#include <iostream>
#include "UrbanEase.h"

using namespace std;

//===================================
//========= Coordinates Class========
//===================================

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





//==============================================
//=================ANALYTICS CLASS==============
//==============================================


// Construcstors
Analytics::Analytics()
{
	monthlySales = new double[24];
	monthlyCosts = new double[24];
	monthlyCustomers = new int[24];
	compositeScore = 0;

	for (int i = 0; i < 24; i++)
	{
		monthlySales[i] = 0;
		monthlyCosts[i] = 0;
		monthlyCustomers[i] = 0;
	}
}

// Deep Copy Constructors
Analytics::Analytics(const Analytics& obj)
{
	monthlySales = new double[24];
	monthlyCosts = new double[24];
	monthlyCustomers = new int[24];
	compositeScore = obj.compositeScore;

	for (int i = 0; i < 24; i++)
	{
		monthlySales[i] = obj.monthlySales[i];
		monthlyCosts[i] = obj.monthlyCosts[i];
		monthlyCustomers[i] = obj.monthlyCustomers[i];
	}
}
// Getters
double Analytics::getmonthlyScores(int index) const
{
	return monthlySales[index];
}
double Analytics::getmonthlyCosts(int index) const
{
	return monthlyCosts[index];
}
double Analytics::getmonthlyCustomers(int index) const
{
	return monthlyCustomers[index];
}
double Analytics::getcompositeScore()const
{
	return compositeScore;
}


// Setters
void Analytics::setmonthlySales(int index, double value)
{
	monthlySales[index] = value;
}
void Analytics::setmonthlyCosts(int index, double value)
{
	monthlyCosts[index] = value;
}
void Analytics::setmonthlyCustomers(int index, int value)
{
	monthlyCustomers[index] = value;
}


// Calculations
double Analytics::getTotalannualSale()const
{
	double sum = 0;
	for (int i = 12; i < 24;i++)
	{
		sum += monthlySales[i];
	}
	return sum;
}

double Analytics::getTotalProfit()const
{
	double profit = 0;
	for (int i = 12; i < 24; i++)
	{
		profit += (monthlySales[i] - monthlyCosts[i]);
	}
	return profit;
}

double Analytics::getAverageMonthlyGrowth()const
{
	double growth = 0;
	for (int i = 12; i < 23; i++)
	{
		growth += monthlySales[i + 1] - monthlySales[i];
	}
	return growth / 11.0;
}


void Analytics::computeCompositeScore()
{
	double a = getTotalannualSale();
	double b = getAverageMonthlyGrowth();
	double c = getTotalProfit();

	double compScore = (c * 0.5) + (a * 0.3) + (b * 0.2);
	
}



// operator Overloading


double Analytics :: operator [](int index)const
{
	return monthlySales[index];
}


Analytics  Analytics :: operator + (const Analytics& obj)
{
	Analytics temp;
	for (int i = 0; i < 24; i++)
	{
		temp.monthlySales[i] = monthlySales[i] + obj.monthlySales[i];
		temp.monthlyCosts[i] = monthlyCosts[i] + obj.monthlyCosts[i];
		temp.monthlyCustomers[i] = monthlyCustomers[i] + obj.monthlyCustomers[i];

	}
	return temp;
}


bool Analytics :: operator < (const Analytics& obj)const
{
	return getcompositeScore() < obj.getcompositeScore();
}


bool Analytics :: operator>(const Analytics& obj) const
{
	return getcompositeScore() > obj.getcompositeScore();
}









