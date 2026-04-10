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

	compositeScore = (c * 0.5) + (a * 0.3) + (b * 0.2);
	
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









//==============================================
//============Forecast Class====================
//==============================================


Forecast::Forecast()
{
	predictedSales = 0;
	confidenceLevel = 0;
	warningFlag = false;
	monthOffset = 0;
}

Forecast::Forecast(double pre, double conf, bool flag, int mof)
{
	predictedSales = pre;
	confidenceLevel = conf;
	warningFlag = flag;
	monthOffset = mof;
}

Forecast::Forecast(const Forecast& obj)
{
	predictedSales = obj.predictedSales;
	confidenceLevel = obj.confidenceLevel;
	warningFlag = obj.warningFlag;
	monthOffset = obj.monthOffset;
}

double Forecast::getPredicetedSale() 
{
	return predictedSales;
}
double Forecast::getConfidenceLevel()
{
	return confidenceLevel;
}
bool Forecast::getWarningFlag()
{
	return warningFlag;
}
int Forecast::getmonthOffset()
{
	return monthOffset;
}


void Forecast :: setPredicetedSale(double sale)
{
	predictedSales = sale;
}
void Forecast::setConfidencelevel(double cLevel)
{
	confidenceLevel = cLevel;
}
void Forecast :: setWarningFlag(bool flag)
{
	warningFlag = flag;
}
void Forecast :: setmonthOffset(int mos)
{
	monthOffset = mos;
}



 Forecast Forecast :: operator +(const Forecast& obj)
{
	Forecast temp;
	temp.predictedSales = predictedSales + obj.predictedSales;
	temp.confidenceLevel = (confidenceLevel + obj.confidenceLevel) / 2;
	temp.warningFlag = (warningFlag || obj.warningFlag);
	return temp;
}

 Forecast& Forecast::operator++()
{
	monthOffset++;
	return *this;
}
Forecast Forecast :: operator ++(int)
{
	Forecast temp = *this;
	monthOffset++;
	return temp;
}

void Forecast :: computeForecast(const Analytics& a)
{
	
	double lastMonth = a.getmonthlyScores(23);  
	double secondLast = a.getmonthlyScores(22);   
	double ThirdLast = a.getmonthlyScores(21); 

	double temp = lastMonth + secondLast + ThirdLast;
	temp = temp / 3;
	double recentTrend = lastMonth - ThirdLast;
	temp = temp + (recentTrend * 0.3);
	setPredicetedSale(temp);


	if (temp < lastMonth)
	{
		setWarningFlag(true);
	}
	else
	{
		setWarningFlag(false);
	}
	
	double avg = 0;
	for (int i = 18; i < 24; i++)
	{
		avg += a.getmonthlyScores(i);
	}
	avg = avg / 6;


	double totalDeviation = 0;
	for (int i = 18; i < 24; i++)
	{
		double Dev = a.getmonthlyScores(i) - avg;
		if (Dev < 0)
		{
			Dev = -Dev;
		}
		totalDeviation += Dev;
	}
	double avgDeviation = totalDeviation / 6;

	double confidence = 100 - (avgDeviation / temp * 100);
	if (confidence < 0)
	{
		confidence = 0;
	}
	if (confidence > 100)
	{
		confidence = 100;
	}

	setConfidencelevel(confidence);

}


//===================================
//=========PERSON CLASS==============
//===================================



Person :: Person()
{
	name = "";
	age = 0;
	CNIC = "";
}
Person:: Person(string n, int ag, string cnic)
{
	name = n;
	CNIC = cnic;
	age = ag;
}

Person::Person(const Person& obj)
{
	name = obj.name;
	CNIC = obj.CNIC;
	age = obj.age;
}


string Person::getName() const
{
	return name;
}
string Person::getCNIC() const
{
	return CNIC;
}
int Person::getAge()const
{
	return age;
}


void Person::setName(string na)
{
	name = na;
}
void Person::setAge(int ag)
{
	age = ag;
}
void Person::setCNIC(string cnic)
{
	CNIC = cnic;
}




bool Person ::  operator==(const Person& obj) const
{
	return CNIC == obj.CNIC;
}







//===================================
//=========EMPLOYEE CLASS==============
//===================================





Employee :: Employee()
{
	basicSalary = 0;
	department = "";
}

Employee :: Employee(string na, int ag, string cnic, double sal, string dep)
{
	name = na;
	CNIC = cnic;
	age = ag;
	basicSalary = sal;
	department = dep;
}

// Copy Constructor
Employee::Employee(const Employee& obj)
{
	name = obj.name;
	CNIC = obj.CNIC;
	age = obj.age;
	basicSalary = obj.basicSalary;
	department = obj.department;
}

// Getters
double Employee::getBaseSalary() const
{
	return basicSalary;
}
string Employee::getDepartment() const
{
	return department;
}

// Setters
void Employee::setBaseSalary(double sal)
{
	basicSalary = sal;
}
void Employee::setDepartment(string dep)
{
	department = dep;
}



// Increment Operators
Employee& Employee ::operator++()
{
	basicSalary = basicSalary * 1.10;
	return *this;
}
Employee Employee ::operator++(int)
{
	Employee temp = *this;
	basicSalary = basicSalary * 1.10;
	return temp;
}

// Decrement Operators
Employee& Employee ::operator--()
{
	basicSalary = basicSalary * 0.90;
	return *this;
}
Employee Employee ::operator--(int)
{
	Employee temp = *this;
	basicSalary = basicSalary * 0.90;
	return temp;
}









//===================================
//=========MANAGER CLASS==============
//===================================







Manager :: Manager()
{
	bonus = 0;
	region = "";
}
Manager::Manager(string na, int ag, string cnic, double sal, string dep, double bo, string reg)
{
	name = na;
	age = ag;
	CNIC = cnic;
	basicSalary = sal;
	department = dep;
	bonus = bo;
	region = reg;
}

Manager::Manager(const Manager& obj)
{
	name = obj.name;
	age = obj.age;
	CNIC = obj.CNIC;
	basicSalary = obj.basicSalary;
	department = obj.department;
	bonus = obj.bonus;
	region = obj.region;
}

double Manager::getBonus()const
{
	return bonus;
}
string Manager::getRegion()const
{
	return region;
}

void Manager::setBonus(double bo)
{
	bonus = bo;
}
void Manager::setRegion(string reg)
{
	region = reg;
}








