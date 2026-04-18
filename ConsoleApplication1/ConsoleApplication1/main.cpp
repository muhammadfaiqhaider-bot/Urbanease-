#include <iostream>
#include "UrbanEase.h"
#include "Extra.h"

using namespace std;

int main()
{
    Store* stores = nullptr;
    int storeCount = 0;

    int choice = showMenu();


    if (choice == 1)
    {
        stores = loadAllStores(storeCount);
        if (stores == nullptr) choice = 2; 
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

    for (int i = 0; i < storeCount; i++) {
        stores[i].getAnalytics().computeCompositeScore();
    }


    Report nationalReport("National Sales Report", storeCount);
    for (int i = 0; i < storeCount; i++)
    {
        stores[i].getAnalytics().computeCompositeScore();
        nationalReport.addStore(&stores[i]);
    }
    nationalReport.sortOnCompositeScore();

    ++nationalReport; 


label:
    system("cls");
    cout << "=============================================================" << endl;
    cout << "                          SUMMARY" << endl;
    cout << "=============================================================" << endl;
    cout << "1- TOP 10 BEST STORES. " << endl;
    cout << "2- 5 LOWEST REVUNUE GENERATOR STORES. " << endl;
    cout << "3- Forecasting All stores. " << endl;
    cout << "4- Exit ...." << endl;
    int choice2;
    cin >> choice2;
    switch (choice2)
    {
    case 1: system("cls");
        nationalReport.printTopStore(10);
        cout << "Press Y/y to go to main menu.";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            goto label;
        }
        break;
    case 2: system("cls");
        nationalReport.printBottom(5);

        cout << "Press Y/y to go to main menu.";
        char ch1;
        cin >> ch1;
        if (ch1 == 'y' || ch1 == 'Y')
        {
            goto label;
        }
        break;
        break;
    case 3:   system("cls");
        cout << "=======================================================" << endl;
        cout << "         FORECASTING FOR  ALL STORES " << endl;
        cout << "=======================================================" << endl;
        cout << endl;
        for (int i = 0;i < storeCount; i++)
        {
            cout << "                      ---------" << endl;
            cout << "<********************|STORE " << i + 1 << "|***************************>" << endl;
            cout << "                      ---------" << endl;
            stores[i].getForecast().computeForecast(stores[i].getAnalytics());
            cout << "  Forecast for ->[" << stores[i].getStoreName() << " Branch] " << endl;
            cout << stores[i].getForecast();
            cout << " <----------------->" << endl;
            cout << "  MANAGER INFO" << endl;
            cout << " <----------------->" << endl;
            Person* ptr = &stores[i].getManager();
            ptr->display();
            cout << "<--------------------------------------------------------->" << endl;
            cout << endl << endl << endl;
          
            
        }
        cout << "Press Y/y to go to main menu.";
        char ch2;
        cin >> ch2;
        if (ch2 == 'y' || ch2 == 'Y')
        {
            goto label;
        }
        break;
        break;
    case 4:
       
        return 0;
        break;
  
    default: cout << "Enter 1-3" << endl;

    }
    

    cout << endl;
    cout << endl;
    cout << endl;

  
    

    delete[] stores;
    return 0;

}