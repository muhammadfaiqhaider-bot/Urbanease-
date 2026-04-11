#include <iostream>
#include "UrbanEase.h"
#include <fstream>   
#include <string> 

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

double Forecast::getPredicetedSale() const
{
	return predictedSales;
}
double Forecast::getConfidenceLevel()const
{
	return confidenceLevel;
}
bool Forecast::getWarningFlag()const
{
	return warningFlag;
}
int Forecast::getmonthOffset()const
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






//===================================
//=========STORE CLASS==============
//===================================



	Store :: Store()
	{
		ID = "";
		storeName = "";
		city = "";
		staffCount = 0;
		staff = nullptr;
	}
	Store::Store(string id, string name, string c, Coordinates loc, Manager mgr, int scount)
	{
		ID = id;
		storeName = name;
		city = c;
		location = loc;
		manager = mgr;
		staffCount = scount;
		staff = new Employee[scount];	

	}
	Store::Store(const Store& obj)
	{
		ID = obj.ID;
		storeName = obj.storeName;
		city = obj.city;
		location = obj.location;
		manager = obj.manager;
		staffCount = obj.staffCount;
		staff = new Employee[staffCount];
		for (int i = 0; i < staffCount; i++)
		{
			staff[i] = obj.staff[i];
		}
	}




	// Getters
	string Store::getStoreID()const
	{
		return ID;
	}
	string Store::getStoreName()const
	{
		return storeName;
	}
	string Store::getCity()const
	{
		return city;
	}
	Coordinates& Store::getLocation()
	{
		return location;
	}
	Analytics& Store:: getAnalytics()
	{
		return analytic;
	}
	Forecast& Store::getForecast()
	{
		return forecast;
	}
	Manager& Store::getManager()
	{
		return manager;
	}
	int Store::getStaffCount()const
	{
		return staffCount;
	}
	Employee& Store::getStaff(int index)
	{
		return staff[index];
	}
	const Analytics& Store::getAnalytics() const
	{
		return analytic;
	}

	// Setters
	void Store::setStoreID(string id)
	{
		ID = id;
	}
	void Store::setStoreName(string name)
	{
		storeName = name;
	}
	void Store::setCityName(string cname)
	{
		city = cname;
	}

	void Store :: setManager(const Manager& mgr)
	{
		manager = mgr;
	}
	void Store :: setStaff(int count)
	{
		staffCount = count;
		delete[] staff;
		staff = new Employee[count];
	}



	bool Store :: operator == (const Store& obj)
	{
		if (ID == obj.ID)
		{
			return true;
		}
		else
		{
			return false;
		}
	}




	void Store::saveToFile(ofstream& out) const
	{
		// Basic info
		out << ID << "\n";
		out << storeName << "\n";
		out << city << "\n";

		// Coordinates
		out << location.getLat() << "\n";
		out << location.getLon() << "\n";

		// Analytics — 24 months each
		for (int i = 0; i < 24; i++)
			out << analytic.getmonthlyScores(i) << "\n";

		for (int i = 0; i < 24; i++)
			out << analytic.getmonthlyCosts(i) << "\n";

		for (int i = 0; i < 24; i++)
			out << analytic.getmonthlyCustomers(i) << "\n";

		// Forecast
		out << forecast.getPredicetedSale() << "\n";
		out << forecast.getConfidenceLevel() << "\n";
		out << forecast.getWarningFlag() << "\n";
		out << forecast.getmonthOffset() << "\n";

		// Manager
		out << manager.getName() << "\n";
		out << manager.getAge() << "\n";
		out << manager.getCNIC() << "\n";
		out << manager.getBaseSalary() << "\n";
		out << manager.getDepartment() << "\n";
		out << manager.getBonus() << "\n";
		out << manager.getRegion() << "\n";

		// Staff
		out << staffCount << "\n";
		for (int i = 0; i < staffCount; i++)
		{
			out << staff[i].getName() << "\n";
			out << staff[i].getAge() << "\n";
			out << staff[i].getCNIC() << "\n";
			out << staff[i].getBaseSalary() << "\n";
			out << staff[i].getDepartment() << "\n";
		}
	}




	void Store::loadFromFile(ifstream& in)
	{
		// Basic info
		getline(in, ID);
		getline(in, storeName);
		getline(in, city);

		
		// Coordinates
		double lat, lon;
		in >> lat >> lon;
		in.ignore();
		location.setLat(lat);
		location.setLon(lon);

		// Analytics — 24 months each
		double sale, cost;
		int customer;
		for (int i = 0; i < 24; i++)
		{
			in >> sale;
			analytic.setmonthlySales(i, sale);
		}
		for (int i = 0; i < 24; i++)
		{
			in >> cost;
			analytic.setmonthlyCosts(i, cost);
		}
		for (int i = 0; i < 24; i++)
		{
			in >> customer;
			analytic.setmonthlyCustomers(i, customer);
		}
		in.ignore();

		// Forecast
		double pSale, conf;
		bool warn;
		int offset;
		in >> pSale >> conf >> warn >> offset;
		in.ignore();
		forecast.setPredicetedSale(pSale);
		forecast.setConfidencelevel(conf);
		forecast.setWarningFlag(warn);
		forecast.setmonthOffset(offset);

		// Manager
		string mName, mCNIC, mDept, mRegion;
		int mAge;
		double mSalary, mBonus;
		getline(in, mName);
		in >> mAge;
		in.ignore();
		getline(in, mCNIC);
		in >> mSalary;
		in.ignore();
		getline(in, mDept);
		in >> mBonus;
		in.ignore();
		getline(in, mRegion);
		manager.setName(mName);
		manager.setAge(mAge);
		manager.setCNIC(mCNIC);
		manager.setBaseSalary(mSalary);
		manager.setDepartment(mDept);
		manager.setBonus(mBonus);
		manager.setRegion(mRegion);

		// Staff
		in >> staffCount;
		in.ignore();
		delete[] staff;
		staff = new Employee[staffCount];
		for (int i = 0; i < staffCount; i++)
		{
			string eName, eCNIC, eDept;
			int eAge;
			double eSalary;
			getline(in, eName);
			in >> eAge;
			in.ignore();
			getline(in, eCNIC);
			in >> eSalary;
			in.ignore();
			getline(in, eDept);
			staff[i].setName(eName);
			staff[i].setAge(eAge);
			staff[i].setCNIC(eCNIC);
			staff[i].setBaseSalary(eSalary);
			staff[i].setDepartment(eDept);
		}
	}









	//=================================
	//========CLUSTER CLASS============
	//=================================




	
		// Default Constructor
		Cluster :: Cluster()
		{
			clusterName = "";
			storeCount = 0;
			capacity = 0;
			Revenue = 0;
			stores = nullptr;    
			subClusterCount = 0;
			subClusters = nullptr;
		}

		// Parameterized Constructor
		Cluster::Cluster(string name, int capac)
		{
			clusterName = name;
			capacity = capac;
			storeCount = 0;        
			Revenue = 0;           
			subClusterCount = 0;   
			subClusters = nullptr; 
			stores = new Store * [capacity];
			for (int i = 0; i < capacity; i++)
			{
				stores[i] = nullptr;
			}			
		}

		
		Cluster:: Cluster(const Cluster& obj)
		{
			clusterName = obj.clusterName;
			capacity = obj.capacity;
			storeCount = obj.storeCount;
			Revenue = obj.Revenue;
			subClusterCount = obj.subClusterCount;

			
			if (obj.stores != nullptr)
			{
				stores = new Store * [capacity];
				for (int i = 0; i < capacity; i++)
				{
					stores[i] = obj.stores[i];
				}				
			}
			else
			{
				stores = nullptr;
			}
				

			if (obj.subClusters != nullptr)
			{
				subClusters = new Cluster[subClusterCount];
				for (int i = 0; i < subClusterCount; i++)
				{
					subClusters[i] = obj.subClusters[i];
				}				
			}
			else
			{
				subClusters = nullptr;
			}
				
		}

		// Destructor
		

	
		void Cluster:: addStore(Store* s)
		{
			if (storeCount < capacity)
			{
				stores[storeCount] = s;
				storeCount++;
			}
			else
				cout << "Region is fulled with Stores. No need for more....." << endl;
		}

	
		void Cluster:: computeTotalRevenue()
		{
			double total = 0;
			for (int i = 0; i < storeCount; i++)
			{
				total += stores[i]->getAnalytics().getTotalannualSale();
			}
			Revenue = total;
		}

		void Cluster:: SubClusters(int k)
		{
			subClusterCount = k;
			subClusters = new Cluster[k];

			subClusters[0] = Cluster("Top", capacity);
			subClusters[1] = Cluster("Average", capacity);
			subClusters[2] = Cluster("Struggling", capacity);

			for (int i = 0; i < storeCount; i++)
			{
				double profit = stores[i]->getAnalytics().getTotalProfit();
				if (profit > 500000)
				{
					subClusters[0].addStore(stores[i]);
				}
					
				else if (profit > 200000)
				{
					subClusters[1].addStore(stores[i]);
				}
					
				else
				{
					subClusters[2].addStore(stores[i]);
				}
				
			}
		}

		// Getters
		Store* Cluster:: getStore(int index) const
		{
			return stores[index];  
		}
		int Cluster:: getStoreCount() const
		{
			return storeCount;
		}
		double Cluster:: getTotalRevenue() const
		{
			return Revenue;
		}
		string Cluster:: getClusterName() const
		{
			return clusterName;
		}
		Cluster* Cluster:: getSubCluster(int index) const
		{
			return &subClusters[index];
		}
		int Cluster:: getSubClusterCount() const
		{
			return subClusterCount;
		}

	
		Cluster Cluster :: operator+(const Cluster& obj)
		{
			int totalCapacity = storeCount + obj.storeCount;
			Cluster temp;
			temp.clusterName = clusterName + "+" + obj.clusterName;
			temp.capacity = totalCapacity;
			temp.stores = new Store * [totalCapacity];

			for (int i = 0; i < storeCount; i++)
				temp.stores[i] = stores[i];

			for (int i = 0; i < obj.storeCount; i++)
				temp.stores[storeCount + i] = obj.stores[i];

			temp.storeCount = totalCapacity;
			temp.Revenue = Revenue + obj.Revenue;
			return temp;
		}

	
		
	

	//=================================
	//========REPORT CLASS============
	//=================================

		
			Report :: Report()
			{
				title = "";
				rankedStores = nullptr;
				storeCount = 0;
				storeCapacity = 0;
				rankCount = 0;
			}
			Report::Report(string tit, int cap)
			{
				title = tit;
				storeCapacity = cap;
				storeCount = 0;
				rankCount = 0;
				rankedStores = new Store * [storeCapacity];
				for (int i = 0; i < storeCapacity; i++)
				{
					rankedStores[i] = nullptr;
				}
			}

			Report::Report(const Report& obj)
			{
				title = obj.title;
				storeCount = obj.storeCount;
				rankCount = obj.rankCount;
				storeCapacity = obj.storeCapacity;
				rankedStores = new Store * [storeCapacity];
				for (int i = 0; i < storeCapacity; i++)
				{
					rankedStores[i] = obj.rankedStores[i];
				}
			}


			void Report::addStore(Store* st)
			{
				if (storeCount < storeCapacity)
				{
					rankedStores[storeCount] = st;
					storeCount++;
				}
				else
				{
					cout << "Capacity is fulled. Can't add more...." << endl;
				}
			}

			void  Report::sortOnCompositeScore()
			{
				for (int i = 0; i < storeCount - 1; i++)
				{
					for (int j = 0; j < storeCount - i - 1; j++)
					{
						if (rankedStores[j]->getAnalytics().getcompositeScore() < rankedStores[j + 1]->getAnalytics().getcompositeScore())

						{
							Store* temp = rankedStores[j];
							rankedStores[j] = rankedStores[j + 1];
							rankedStores[j + 1] = temp;
						}
					}
				}
			}

			void Report::sortOnProfit()
			{
				for (int i = 0; i < storeCount - 1; i++)
				{
					for (int j = 0; j < storeCount - 1 - i; j++)
					{
						if (rankedStores[j]->getAnalytics().getTotalProfit() > rankedStores[j + 1]->getAnalytics().getTotalProfit())
						{
							Store* temp = rankedStores[j];
							rankedStores[j] = rankedStores[j + 1];
							rankedStores[j + 1] = temp;
						}
					}
				}
			}
			
		
			void Report::sortOnGrowth()
			{
				for (int i = 0; i < storeCount-1; i++)
				{
					for (int j = 0; j < storeCount - i - 1;j++)
					{
						if (rankedStores[j]->getAnalytics().getAverageMonthlyGrowth() > rankedStores[j + 1]->getAnalytics().getAverageMonthlyGrowth())
						{
							Store* temp = rankedStores[j];
							rankedStores[j] = rankedStores[j + 1];
							rankedStores[j + 1] = temp;
						}
					}
				}
			}

			void Report::printTopStore(int n)const
			{
				cout << "Top " << n << " stores across all Pakistan" << endl;
				int limit;
				if (n < storeCount)
				{
					limit = n;
				}
				else
				{
					limit = storeCount;
				}
				for (int i = 0; i < limit; i++)
				{
					cout << "  Rank:   " << i + 1 << endl;
					cout << "  ID:     " << rankedStores[i]->getStoreID() << endl;
					cout << "  Name:   " << rankedStores[i]->getStoreName() << endl;
					cout << "  City:   " << rankedStores[i]->getCity() << endl;
					cout << "  Score:  " << rankedStores[i]->getAnalytics().getcompositeScore() << endl;
					cout << "  Profit: " << rankedStores[i]->getAnalytics().getTotalProfit() << endl;
					cout << "----------------------------" << endl;

				}
			}

			void Report::printBottom(int n) const
			{
				cout << "BOTTOM " << n << " STORES " << endl;
				int start = storeCount - n;
				if (start < 0)
				{
					start = 0;
				}
				for (int i = storeCount - 1; i >= start; i--)
				{
					cout << "Rank " << storeCount - i << ":" << endl;
					cout << "  ID:     " << rankedStores[i]->getStoreID() << endl;
					cout << "  Name:   " << rankedStores[i]->getStoreName() << endl;
					cout << "  City:   " << rankedStores[i]->getCity() << endl;
					cout << "  Score:  " << rankedStores[i]->getAnalytics().getcompositeScore() << endl;
					cout << "  Profit: " << rankedStores[i]->getAnalytics().getTotalProfit() << endl;
					cout << "----------------------------" << endl;
				}
			}




			Report Report :: operator++(int)
			{
				Report temp = *this;
				rankCount++;
				return temp;
			}


			Report& Report :: operator++()
			{
				rankCount++;
				return *this;
			}




		











