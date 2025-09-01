#pragma once
#include <vector>
#include <map>
#include <string>
#include "PotionBottle.h"

using namespace std;

class StockManager
{
public:
	StockManager(int maxCapacity);

private:

	map<string, int> _potionStorage;// using potion name as key and find potion count (key: name, value:count)
	vector<PotionBottle> _real_PotionList;// this is only for using potion. only add, and use the potion's info by comparing the key

	map<string, int> _ingredientStorage;// store the ingredients in storage// ingredients wont have limits

	int _maxCapacity;
	int _currentCapacity;
	int _max_ingredientCounts;// if refilling ingredient is activated, this amount of ingredient will be set to be this.

public:


	void SetMaxCapacity(int newmax);
	int GetMaxCapacity();

	void SetCurrentCapacity(int current_count);
	int GetCurrentCapacity(); // may be this is for printing out status//nope

	//void SetPotionStorage(map<string, int> updated_storage);// set wont be necessary
															// modify potion and ingrdient storage ONLY with remove, store or reset fucntion
	
	//---- these are for printing out the list using printer
	map<string, int> GetPotionStorage();
	map<string, int> GetIngredientStorage();
	vector<PotionBottle> GetActualPotionList();


	void AddIngredients();

	bool RemovePotion(PotionBottle removedPotion);// removing potion can be done in many situations. to printout the situation, use bool return of this function
	bool StorePotion(PotionBottle newPotion);// add new potion in potion storage;// returns bool for the same reason why remove potion does it too

	map<string, int> PutIngredientsOnBasket(map<string, int> shoppinglist);// like shopping in a mall, try to put same amount of ingredients on a basket.
											// --> the basket could be filled with lists of ingredients, or the basket could be lighter or empty;

	void SetRefillAmount(int newamount);//change the ingredient counts
	void RefillIngredients();// set all ingretient value to ingredient counts

	/*
	void PrintoutStatus();
	//sepertate sections of status for individual print out

	void PrintoutIngredientStatus();
	void PrintoutPotionStatus();
	*/
	~StockManager();
};