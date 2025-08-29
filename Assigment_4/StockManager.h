#pragma once
#include <vector>
#include <map>
#include <string>
#include "PotionBottle.h"

using namespace std;

class StockManager
{
public:
	StockManager(int _maxCapacity, int _currentCapacity );

private:

	map<string, int> _potionStorage;// using potion name as key and find potion count (key: name, value:count)
	map<string, int> _ingredientStorage;// store the ingredients in storage// ingredients wont have limits

	int _maxCapacity;
	int _currentCapacity;

public:
	void StorePotion(PotionBottle newPotion);// add new potion in potion storage;

	map<string, int> PutIngredientsOnBasket();// like shopping in a mall, try to put same amount of ingredients on a basket.
											// --> the basket could be filled with lists of ingredients, or the basket could be lighter or empty;

};