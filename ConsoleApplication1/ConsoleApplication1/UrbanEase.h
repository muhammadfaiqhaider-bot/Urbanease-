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




class Person
{
protected:
	string name;
	int age;
	string CNIC;
public:
	Person();
	Person(string n, int ag, string cnic);
	Person(const Person& obj);
	

	string getName() const;	
	string getCNIC() const;
	int getAge()const;
	

	void setName(string na);	
	void setAge(int ag);
	void setCNIC(string cnic);
	

	virtual double getSalary() const = 0;      
	virtual string getRole() const = 0;        
	virtual void display() const = 0;         

	bool operator==(const Person& obj) const;
	

	friend ostream& operator << (ostream& out, Person& obj)
	{
		out << obj.CNIC << endl;
		out << obj.name << endl;
		out << obj.age << endl;
		return out;

	}

	virtual ~Person()
	{}
};


class Employee : public Person
{
protected:
	double basicSalary;
	string department;

public:
	// Constructors
	Employee();
	Employee(string na, int ag, string cnic, double sal, string dep);
	Employee(const Employee& obj);


	double getBaseSalary() const;
	string getDepartment() const;
	

	void setBaseSalary(double sal);
	void setDepartment(string dep);
	

	virtual double getSalary() const override
	{
		return basicSalary;
	}
	virtual string getRole() const override
	{
		return "Employee";
	}
	virtual void display() const override
	{
		cout << "Role: " << getRole() << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "CNIC: " << CNIC << endl;
		cout << "Department: " << department << endl;
		cout << "Salary: " << basicSalary << endl;
	}

	Employee& operator++();
	Employee operator++(int);
	

	Employee& operator--();
	Employee operator--(int);
	
	virtual ~Employee() {}
};



class Manager : public Employee
{
protected:
	double bonus;
	string region;
public:
	Manager();
	
	Manager(string na, int ag, string cnic, double sal, string dep, double bo, string reg);
	

	Manager(const Manager& obj);
	
	double getBonus()const;
	
	string getRegion()const;
	

	void setBonus(double bo);
	
	void setRegion(string reg);
	


	virtual double getSalary() const override
	{
		return basicSalary + bonus;
	}

	virtual string getRole() const override
	{
		return "Manager";
	}

	virtual void display() const override
	{
		cout << "Role: " << getRole() << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "CNIC: " << CNIC << endl;
		cout << "Department: " << department << endl;
		cout << "Basic Salary: " << basicSalary << endl;
		cout << "Bonus: " << bonus << endl;
		cout << "Total Salary: " << getSalary() << endl;
		cout << "Region: " << region << endl;
	}


	virtual ~Manager()
	{

	}
};