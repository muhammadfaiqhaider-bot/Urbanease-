#include <iostream>
#include <string>
#include "UrbanEase.h"
#include "extra.h"
#include <cstdlib>  
#include <ctime>    
#include <cmath>
using namespace std;

Store* generateStores(int count)
{
    srand(time(0));
    Store* stores = new Store[count];


    string name = "";

    for (int i = 0; i < count; i++)
    {
        //Generate ID
        string id = "PAK-";
        int num = i + 1;
        if (num < 10)
        {
            id = id + "0000" + to_string(num);
        }
        else if (num < 1000 && num >= 100)
        {
            id = id + "000" + to_string(num);
        }
        else if (num < 10000 && num >= 1000)
        {
            id = id + "00" + to_string(num);
        }
        else if (num < 100000 && num >= 10000)
        {
            id = id + "0" + to_string(num);
        }
        else
        {
            id = id + to_string(num);
        }


        // Pick Random City
        string cities[] = { "Lahore", "Rawalpindi", "Islamabad" };
        int cityVal = rand() % 3;
        string city = cities[cityVal];

        if (city == "Lahore")
        {
            // Areas (random)
            string area_1[] = { "Bahria Town","Samnabad","Johar Town","DHA-Lahore",
             "Lahore-Cantt", "Johar Town","Gulshan Ravi" };

            name = "Pakistan UrbanEase" + area_1[rand() % 7];
        }
        else if (city == "Rawalpindi")
        {
            string area_2[] = { "Bahria Town", "Westridge","Sadar Rawalpindi", "Tench Bhata",
            "PWD", "Commercial Market","DHA-Islamabad","DHA-Lahore" };

            name = "Pakistan UrbanEase" + area_2[rand() % 8];
        }

        else if (city == "Islamabad")
        {
            string area_3[] = { "Bahria Town", "F6","Gulberg Greens",
            "G6", "G13", "B17","DHA-Islamabad","DHA-Lahore","I8","F10", };

            name = "Pakistan UrbanEase" + area_3[rand() % 10];
        }

        stores[i].setStoreName(name);
        stores[i].setStoreID(id);
        stores[i].setCityName(city);

        // Till Now we Have setted the STORE Name/ID/City in which store locatied.

       
        double latitude = 77.0, longitude = 33.50;
        if (cityVal == 1)
        {
            latitude = 33.0 + (rand() % 100) / 100.0;
            longitude = 73.0 + (rand() % 100) / 100.0;
        }
        else if (cityVal == 0)
        {
            latitude = 31.0 + (rand() % 100) / 100.0;
            longitude = 74.0 + (rand() % 100) / 100.0;
        }

        else if (cityVal == 2) 
        {
            latitude = 32.0 + (rand() % 100) / 100.0; 
            longitude = 73.0 + (rand() % 100) / 100.0;
        }


        //Provide Latitude and Longitude to the Store
        stores[i].getLocation().setLat(latitude);
        stores[i].getLocation().setLon(longitude);



        // Inner Loop for monthly Stats for each Store (last 24 months)
        for (int m = 0; m < 24; m++)
        {
            double sale = 100000 + (rand() % 900000);
            double cost = 50000 + (rand() % 400000);
            int customers = 500 + (rand() % 4500);

            stores[i].getAnalytics().setmonthlySales(m, sale);
            stores[i].getAnalytics().setmonthlyCosts(m, cost);
            stores[i].getAnalytics().setmonthlyCustomers(m, customers);
        }



        string managerNames[] = { "Muhammad Faiq Haider", "Fawad", "Abiha", "Cheema",
                    "Ishmal", "Yusha", "Amna", "Khatija", "Hussain", "Ibrahim","Ahmed", "Zayan" };
        string depts[] = { "Sales", "Tech", "Marketing", "Finance" };

        string mName = managerNames[rand() % 11];
        int managerAge = 18 + (rand() % 4);
        double managerSal = 80000 + (rand() % 70000);
        double managerBonus = 10000 + (rand() % 40000);
        string managerDept = depts[rand() % 4];
        string managerCNIC = "3" + to_string(rand() % 9999) + "-" + to_string(rand() % 9000000 + 1000000) + "-" + to_string(rand() % 9);

        Manager mgr(mName, managerAge, managerCNIC, managerSal, managerDept, managerBonus, city);
        stores[i].setManager(mgr);




        int staffCount = 2 + (rand() % 4);

        string employeeNames[] = { "Bilal", "Hamza", "Asad", "Imran",
                           "Hina", "Nadia", "Sana", "Rabia","Shugufta", "Nawaz Sharif", "Atif" };

        stores[i].setStaff(staffCount);
        for (int s = 0; s < staffCount; s++)
        {
            string employeeName = employeeNames[rand() % 10];
            int employeeAge = 20 + (rand() % 10);
            double employeeSal = 30000 + (rand() % 50000);
            string employeeDept = depts[rand() % 4];
            string employeeCNIC = "3" + to_string(rand() % 9999) + "-" + to_string(rand() % 9000000 + 1000000) + "-" + to_string(rand() % 9);

            stores[i].getStaff(s).setName(employeeName);
            stores[i].getStaff(s).setAge(employeeAge);
            stores[i].getStaff(s).setCNIC(employeeCNIC);
            stores[i].getStaff(s).setBaseSalary(employeeSal);
            stores[i].getStaff(s).setDepartment(employeeDept);

        }


        stores[i].getAnalytics().computeCompositeScore();
    }
    return stores;
}











void saveAllStores(Store* stores, int count)
{
    ofstream file("data.txt");

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // First line = total count
    file << count << "\n";

    // Save each store
    for (int i = 0; i < count; i++)
    {
        stores[i].saveToFile(file);
    }

    file.close();
    cout << count << " stores saved to data.txt" << endl;
}










Store* loadAllStores(int& count)
{
    ifstream file("data.txt");

    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        count = 0;
        return nullptr;
    }

    // Read count from first line
    file >> count;
    file.ignore();

    // Allocate array
    Store* stores = new Store[count];

    // Load each store
    for (int i = 0; i < count; i++)
    {
        stores[i].loadFromFile(file);
    }

    file.close();
    cout << count << " stores loaded from data.txt" << endl;
    return stores;
}






// Extra Function Needs for calculations 
double calculateDistance(Coordinates c1, Coordinates c2) 
{
    double latDiff = c1.getLat() - c2.getLat();
    double lonDiff = c1.getLon() - c2.getLon();
    double ans = sqrt(pow(latDiff, 2) + pow(lonDiff, 2));
    return ans;
}



void performKMeans(Store* stores, int storeCount)
{
    int k = 3;
    Coordinates* centroids = new Coordinates[k];

    // Initializing based on YOUR generation ranges:
    centroids[0] = Coordinates(74.5, 31.5); // Center of Lahore range
    centroids[1] = Coordinates(73.5, 33.5); // Center of Pindi range
    centroids[2] = Coordinates(73.5, 32.5); // Center of Islamabad range

    int* assignments = new int[storeCount];
    for (int i = 0; i < storeCount; i++) assignments[i] = -1;

    for (int iter = 0; iter < 10; iter++) { // 10 iterations is plenty
        // Assignment Step
        for (int i = 0; i < storeCount; i++) {
            double minDist = 1e9;
            int bestK = 0;
            for (int j = 0; j < k; j++) {
                // Using Euclidean Distance
                double d = sqrt(pow(stores[i].getLocation().getLat() - centroids[j].getLat(), 2) +
                    pow(stores[i].getLocation().getLon() - centroids[j].getLon(), 2));
                if (d < minDist) {
                    minDist = d;
                    bestK = j;
                }
            }
            assignments[i] = bestK;
        }

        // Update Step (Mean calculation)
        for (int j = 0; j < k; j++) {
            double sumLat = 0, sumLon = 0;
            int count = 0;
            for (int i = 0; i < storeCount; i++) {
                if (assignments[i] == j) {
                    sumLat += stores[i].getLocation().getLat();
                    sumLon += stores[i].getLocation().getLon();
                    count++;
                }
            }
            if (count > 0) {
                centroids[j].setLat(sumLat / count);
                centroids[j].setLon(sumLon / count);
            }
        }
    }

    // After finding the groups, we populate the actual Cluster objects
    Cluster* cityClusters = new Cluster[k];
    cityClusters[0] = Cluster("Lahore Region", storeCount);
    cityClusters[1] = Cluster("Rawalpindi Region", storeCount);
    cityClusters[2] = Cluster("Islamabad Region", storeCount);

    for (int i = 0; i < storeCount; i++) {
        cityClusters[assignments[i]].addStore(&stores[i]);
    }

    // Print the results using your overloaded <<
    for (int i = 0; i < k; i++) {
        cityClusters[i].computeTotalRevenue();
        cout << cityClusters[i] << endl;
    }

    // Cleanup
    delete[] centroids;
    delete[] assignments;
    delete[] cityClusters;
}












int showMenu()
{
    int choice;
    cout << "==============================" << endl;
    cout << "  Welcome to UrbanEase System " << endl;
    cout << "==============================" << endl;
    cout << "1. Load Existing Data" << endl;
    cout << "2. Generate New Dataset" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}