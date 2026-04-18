#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>  
#include <string> 
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



//+++++++++++++++++++++++++++++++
//  Analytics Class
//+++++++++++++++++++++++++++++++





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
	double getPredicetedSale()const;
	double getConfidenceLevel()const;
	bool getWarningFlag()const;
	int getmonthOffset()const;

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
	
	
	friend ostream& operator<<(ostream& out, const Forecast& obj)
	{
		

		
		string salesLine = "  Prediction Sales : " + to_string((int)obj.predictedSales);
		out <<  salesLine  << endl;


		string confLine = "  Confidence Level : " + to_string(obj.confidenceLevel).substr(0, 5) + "%";
		out <<  confLine  << endl;

	
		string warnLine = "  Warning Flag     : ";
		warnLine += (obj.warningFlag ? "YES - DECLINE EXPECTED!" : "NO");
		out << warnLine  << endl;

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
		cout << "  Role: " << getRole() << endl;
		cout << "  Name: " << name << endl;
		cout << "  Age: " << age << endl;
		cout << "  CNIC: " << CNIC << endl;
		cout << "  Department: " << department << endl;
		cout << "  Basic Salary: " << basicSalary << endl;
		cout << "  Bonus: " << bonus << endl;
		cout << "  Total Salary: " << getSalary() << endl;
		cout << "  Region: " << region << endl;
	}


	virtual ~Manager()
	{

	}
};







class Store
{
private:
	string ID;
	string storeName;
	string city;
	Coordinates location;   // Composition Happening Here because Store class is main thing that contains all classes
	Analytics analytic;     // Store contains these attributes Location, Analatyics, Forecasting, Manager
	Forecast forecast;      // And if remove store location .......all of them will be removed that's why its composition 
	Manager manager;        // Because every class depends on Store for there exsistence.....
	Employee* staff;
	int staffCount;

public:
	Store();
	Store(string id, string name, string c, Coordinates loc, Manager mgr, int scount);	
	Store(const Store& obj);
	

	// Getters
	string getStoreID()const;
	string getStoreName()const;
	string getCity()const;
	Coordinates& getLocation();
	Analytics& getAnalytics();
	Forecast& getForecast();	
	Manager& getManager();
	int getStaffCount()const;
	Employee& getStaff(int index);
	const Analytics& getAnalytics() const;
	


	// Setters
	void setStoreID(string id);	
	void setStoreName(string name);	
	void setCityName(string cname);
	void setManager(const Manager& mgr);
	void setStaff(int count);
	bool operator == (const Store& obj);
	
	void saveToFile(ofstream& out) const;
	void loadFromFile(ifstream& in);


	friend ostream& operator <<(ostream& out, Store& obj)
	{
		out << "Summary " << endl;
		out << "ID: " << obj.ID << endl;
		out << "Store Name: " << obj.storeName << endl;
		out << "City: " << obj.city << endl;
		out << "Location: " << obj.location << endl;
		out << "Anlaytics: " << obj.analytic << endl;
		out << "Manager: " << obj.manager << endl;
		out << "Total Number of Staff: " << obj.staffCount << endl;
		out << "Staff Details: ";
		for (int i = 0; i < obj.staffCount; i++)
		{
			out << obj.staff[i] << endl;
		}
		return out;

	}


	~Store()
	{
		delete[]staff;
	}
};

























class Cluster
{
private:
	string clusterName;
	Store** stores;
	int storeCount;
	int capacity;
	double Revenue;
	int subClusterCount;
	Cluster* subClusters;

public:
	// Default Constructor
	Cluster();
	Cluster(string name, int capac);
	Cluster(const Cluster& obj);
	

	// Destructor
	~Cluster() {
		
		if (stores != nullptr) {
			delete[] stores;
			stores = nullptr; 
		}

		
		if (subClusters != nullptr) {
			
			delete[] subClusters;
			subClusters = nullptr;
		}
	}

	void addStore(Store* s);
	


	void computeTotalRevenue();
	

	void SubClusters(int k);
	

	// Getters
	Store* getStore(int index) const;
	
	int getStoreCount() const;

	double getTotalRevenue() const;
	
	string getClusterName() const;
	
	Cluster* getSubCluster(int index) const;
	
	int getSubClusterCount() const;

	
	

	Cluster operator+(const Cluster& obj);
	Cluster& operator=(const Cluster& obj);
	

	// operator
	friend ostream& operator<<(ostream& out, const Cluster& obj)
	{
		out << "Cluster Name: " << obj.clusterName << endl;
		out << "No. of Stores: " << obj.storeCount << endl;
		out << "Total Revenue: " << obj.Revenue << endl;
		out << "Stores:" << endl;
		for (int i = 0; i < obj.storeCount; i++)
		{
			out << "  ID: " << obj.stores[i]->getStoreID() << "  Name: " << obj.stores[i]->getStoreName() << endl;
		}

		if (obj.subClusters != nullptr)
		{
			out << "Sub Clusters:" << endl;
			{
				for (int i = 0; i < obj.subClusterCount; i++)
					out << obj.subClusters[i];
			}

		}
		return out;
	}
};













class Report
{
private:
	string title;
	Store** rankedStores;
	int storeCount;
	int storeCapacity;
	int rankCount;

public:
	Report();
	Report(string tit, int cap);
	Report(const Report& obj);
	


	void addStore(Store* st);
	void sortOnCompositeScore();
	void sortOnProfit();
	void sortOnGrowth();
	void printTopStore(int n)const;
	void printBottom(int n) const;
	

	Report operator++(int);
	Report& operator++();
	

	friend ostream& operator<<(ostream& out, const Report& obj)
	{

		out << "REPORT: " << obj.title << endl;
		out << "Total Stores: " << obj.storeCount << endl;
		for (int i = 0; i < obj.storeCount; i++)
		{
			out << "Rank " << i + 1 << ": " << obj.rankedStores[i]->getStoreName() << endl;
			out << " | Score: " << obj.rankedStores[i]->getAnalytics().getcompositeScore() << endl;
			out << " | Profit: " << obj.rankedStores[i]->getAnalytics().getTotalProfit() << endl;

		}
		return out;
	}



	~Report()
	{
		delete[] rankedStores;
		rankedStores = nullptr;
	}
};