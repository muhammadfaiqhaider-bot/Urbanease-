#pragma once
#include <iostream>
using namespace std;

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



//==============================================
//=================ANALYTICS CLASS==============
//==============================================





class Analytics
{
private:
	double* monthlySales;
	double* monthlyCosts;
	int* monthlyCustomers;
	double compositeScore;

public:
	Analytics();
	Analytics(const Analytics& obj);
	
	// Getters
	double getmonthlyScores(int index) const;
	double getmonthlyCosts(int index) const;
	double getmonthlyCustomers(int index) const;
	double getcompositeScore()const;
	// Setters
	void setmonthlySales(int index, double value);
	void setmonthlyCosts(int index, double value);
	void setmonthlyCustomers(int index, int value);
	// Calculations
	double getTotalannualSale()const;
	double getTotalProfit()const;
	double getAverageMonthlyGrowth()const;
	
	
	// composite score

	void computeCompositeScore();
	
	
	// operator Overloading
	double operator [](int index)const;
	Analytics operator + (const Analytics& obj);
	bool operator < (const Analytics& obj)const;
	bool operator>(const Analytics& obj) const;


	friend ostream& operator<<(ostream& out, const Analytics& obj)
	{
		out << "Total Sales: " << obj.getTotalannualSale() << endl;
		out << "Total Profit: " << obj.getTotalProfit() << endl;
		out << "Composite Score: " << obj.compositeScore << endl;
		return out;
	}


	// Destructor
	~Analytics()
	{
		delete[]monthlySales;
		delete[]monthlyCosts;
		delete[]monthlyCustomers;
	}
};




class Forecast
{
private:
	double predictedSales;
	double confidenceLevel;
	bool warningFlag;
	int monthOffset;

public:
	Forecast();
	Forecast(double pre, double conf, bool flag, int mof);
	// Getters
	double getPredicetedSale();
	double getConfidenceLevel();
	bool getWarningFlag();
	int getmonthOffset();

	//Setters
	void setPredicetedSale(double sale);
	void setConfidencelevel(double cLevel);
	void setWarningFlag(bool flag);
	void setmonthOffset(int mos);
	// Copy Constructor
	Forecast(const Forecast& obj);
	

	// Operator overloading
	Forecast operator +(const Forecast& obj);
	Forecast& operator ++();
	Forecast operator ++(int);


	void computeForecast(const Analytics& a);
	
	
	friend ostream& operator<< (ostream& out, const Forecast& obj)
	{
		out << "Prediction Sales : " << obj.predictedSales << endl;
		out << "Confidence Level : " << obj.confidenceLevel << endl;
		out << "Warning Flag : " << obj.warningFlag << endl;
		return out;
	}



	~Forecast() {};
};