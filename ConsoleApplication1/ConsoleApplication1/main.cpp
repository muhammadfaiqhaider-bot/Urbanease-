#include <iostream>
#include "UrbanEase.h"
#include "Extra.h"

using namespace std;

int main()
{
    Store* stores = nullptr;
    int storeCount = 0;

    int choice = showMenu();

    // Check if loading or generating
    if (choice == 1)
    {
        stores = loadAllStores(storeCount);
        if (stores == nullptr) choice = 2; // Fallback if file load failed
    }

    if (choice == 2)
    {
        cout << "Enter number of stores (min 100): ";
        cin >> storeCount;
        while (storeCount < 100)
        {
            cout << "Minimum 100 stores required! Enter again: ";
            cin >> storeCount;
        }
        stores = generateStores(storeCount);
        saveAllStores(stores, storeCount);
    }

    if (stores == nullptr) return 1;

    // 1. Run Clustering
    performKMeans(stores, storeCount);

    // 2. Run Ranking
    Report nationalReport("National Sales Report", storeCount);
    for (int i = 0; i < storeCount; i++)
    {
        stores[i].getAnalytics().computeCompositeScore();
        nationalReport.addStore(&stores[i]);
    }
    nationalReport.sortOnCompositeScore();

    ++nationalReport; // Increment operator requirement
    nationalReport.printTopStore(10);
    nationalReport.printBottom(5);

    // 3. Run Forecast for a store
    stores[0].getForecast().computeForecast(stores[0].getAnalytics());
    cout << "\nForecast for " << stores[0].getStoreName() << ":\n" << stores[0].getForecast() << endl;

    // 4. Show Polymorphism
    Person* ptr = &stores[0].getManager();
    ptr->display();

    delete[] stores;
    return 0;
}