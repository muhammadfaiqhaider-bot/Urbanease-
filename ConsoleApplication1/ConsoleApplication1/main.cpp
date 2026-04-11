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
        
        ifstream test("data.txt");
        if (!test.is_open())
        {
            cout << "File not found! Switching to generate..." << endl;
            choice = 2;
        }
        test.close();
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
    else
    {
        stores = loadAllStores(storeCount);
    }

    // confirm data loaded
    cout << "Data ready! " << storeCount << " stores in system." << endl;

    // cleanup
    delete[] stores;
    return 0;
}


