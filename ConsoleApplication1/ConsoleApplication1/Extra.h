#pragma once
#include "UrbanEase.h"

Store* generateStores(int count);
void saveAllStores(Store* stores, int count);
Store* loadAllStores(int& count);
int showMenu();