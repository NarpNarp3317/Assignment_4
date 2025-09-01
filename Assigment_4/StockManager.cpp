#include "StockManager.h"
#include <iostream>
#include "IngredientDetector.h"

StockManager::StockManager(int maxCapacity)
{
	_maxCapacity = maxCapacity;
	_currentCapacity = 0;// default is 0// no potion is in storage
	_max_ingredientCounts = 30;// default is 30;

	_real_PotionList = {};
	_potionStorage = {};
	//----add default ingredients for start -------//
	_ingredientStorage = {};
}

//================ Storage ======================//
void StockManager::SetMaxCapacity(int newmax)
{
	_maxCapacity = newmax;
}

int StockManager::GetMaxCapacity()
{
	return _maxCapacity;
}

void StockManager::SetCurrentCapacity(int current_count)
{
	_currentCapacity = current_count;
}

int StockManager::GetCurrentCapacity()
{
	return _currentCapacity;
}

map<string, int> StockManager::GetPotionStorage()
{
	return _potionStorage;
}

map<string, int> StockManager::GetIngredientStorage()
{
	return _ingredientStorage;
}

vector<PotionBottle> StockManager::GetActualPotionList()
{
	return _real_PotionList;
}



void StockManager::AddIngredients()
{
	IngredientDetector string_manager;// use the ingredient detector for string management
	string writenstring="";
	bool isrunning = true;

	while (isrunning)
	{
		cout << "Type in New Ingredient: ";
		cin >> writenstring;

		if( writenstring == "")
		{
			cout << "Error, No ingredient detected. Try Again." << endl;
			return;// end function
		}

		string_manager.MakeIngredientList(writenstring);
		// this works because default of ingredient with no number can be also detected as 1*(), wont use the count anyway
		// this will detect chunk of text and make a word, and trimo out the unnecessary ' 's
		
		// put them in the storage if it is NEW ingredient
		for (pair<const string, int>& pair : string_manager.GetSortedIngredients())//ranged loop for the lists of new ingredients
		{
			if (_ingredientStorage.find(pair.first) != _ingredientStorage.end())// search if storage has already has same ingredient;
			{
				cout << (_ingredientStorage.find(pair.first))->first << " is not a new ingredient." << endl;
			}
			else
			{
				_ingredientStorage[pair.first] = _max_ingredientCounts;// add new key to the ingredient storage and set the count as the defualt of max ingredient count"30"
				cout << "New ingredient, " << (_ingredientStorage.find(pair.first))->first << " is added in storage." << endl;
			}
		}// end of the loop
	}
}

bool StockManager::RemovePotion(PotionBottle removedPotion)
// if this potion is used, if it return true, print out the wanted script, but if it return false, print out the reason why it failed in this function
{
	string potion_name = removedPotion.GetName();

	map<string,int>::iterator it=_potionStorage.find(potion_name);//find the potion by name;
	if (it != _potionStorage.end())// if potion is found
	{
		if (it->second > 0)//the key is found and potion count is above 0
		{
			_potionStorage[potion_name] -= 1;// decrement the value of removed potion
			_currentCapacity -= 1;// decrement current capacity;
			return true;
		}
		else// the key exist but potion count is 0// no potion to be removed
		{
			cout << "There is no more " << potion_name << " in the storage." << endl;
			return false;
		}
	}
	else// if no key was found in the map storage
	{
		cout << "No potion with name of " << potion_name << " was found." << endl;
		return false;
	}
}

bool StockManager::StorePotion(PotionBottle newPotion)
{
	string name = newPotion.GetName();

	if (_currentCapacity < _maxCapacity)// if there is enough space for one more potion
	{
		_potionStorage[name] += 1;// map will automatically create new name key if there was no same key before. MAGIC
		_currentCapacity += 1;//increment current_c too. this will be used to check capacity without using map;

		return true;//removed successfully
	}
	else// if there is no more space for extra potion
	{
		cout << "Not enough storage for " << name << "." << endl;
		return false;
	}
}

map<string, int> StockManager::PutIngredientsOnBasket(map<string, int> shoppinglist)// like shopping!
{
	map<string, int> shoppingcart = {};// start with empty shoppingcart

	if (shoppinglist.empty())// empty list
	{
		cout << "Error, No ingredients detected." << endl;
		return shoppingcart;// return as empty
	}
	else// if there is something in a list
	{
		/*
		for (auto& pair: shoppinglist)// google answer fuck
		{

		}
		pair<string, int> A_pair;
		pair<string, int> &B_pair = A_pair;
		// reference is declared in the ranged loop; the simplified syntax does not show the full code but it 
		for ( pair<const string, int>& pair : shoppinglist)// this is the reason!!!!!!//
		{
			pair.first;
		}
		*/
		/*
		map<string, int> ::iterator list_it = shoppinglist.begin();
		while (list_it != shoppinglist.end())// List_it++ inside the loop till before it meets the end
		{

		}
		*/

		for(map<string, int> ::iterator list_it= shoppinglist.begin(); list_it != shoppinglist.end(); list_it++)
			// from the start till before end, move to next one by incrementing the iterator!!!!
			//(it->first) this means by entering what iterator is pointing at(which is struct called pair, and bring out the first( the key value) 
		{
			//auto sotrage_it = _ingredientStorage.find(it->first);
			map<string, int> ::iterator sotrage_it = _ingredientStorage.find(list_it->first);

			if (sotrage_it != _ingredientStorage.end())// if there are/is ingredient in stock( count not found yet), try to put it on the shopping cart
			{
				if (sotrage_it->second >= list_it->second)// when there are enough ingredients to take
				{
					sotrage_it->second -= list_it->second;// deduct the amount that shopping cart takes out

					shoppingcart[list_it->first] = list_it->second;// add the exact amount of count(value/second) for the ingredient(key/first)
				}
				else if (sotrage_it->second < list_it->second)// when there are not enough ingredients for the shopping list
				{
					//take all of current ingredient from the storage
					/*
					sotrage_it->second = 0;// no more 

					shoppingcart[list_it->first] = sotrage_it->second;
					*/ //error!!! the order is fliped store the storage amount first!!! and then make it 0;

					shoppingcart[list_it->first] = sotrage_it->second;// put all of the ingredients in shopping cart;
					sotrage_it->second = 0;// no more ingredient in storage
				}
			}
		}//------- end of the loop

		return shoppingcart;
	}
}

void StockManager::SetRefillAmount(int newamount)
{
	_max_ingredientCounts = newamount;
}

void StockManager::RefillIngredients()
{
	// map is balically array of pair<key, value>;
	// // like before, iterator points the address ,which mean it can get what it is pointing(*). == ()->
	// in pair,iterator->key==first, iterator->value== second.

	/*
	// bring as reference
	for (auto& a : _ingredientStorage)// auto would be the "pair"<string, int>
	{
		a.second = _max_ingredientCounts;// set every value 
	}

	for (auto a : _ingredientStorage)// auto would be 
	{
		
	}
	*/

	for (map<string, int> ::iterator pair_pointer = _ingredientStorage.begin(); pair_pointer != _ingredientStorage.end(); pair_pointer++)// increment iterator so that the list can be countinously move on
	{
		pair_pointer->second = _max_ingredientCounts;// set every value 
	}
}

/*
void StockManager::PrintoutStatus()
{
	
	
}

void StockManager::PrintoutIngredientStatus()
{
}

void StockManager::PrintoutPotionStatus()
{
}
*/
// print out is for printer obj

StockManager::~StockManager()// burn it all
{
}

