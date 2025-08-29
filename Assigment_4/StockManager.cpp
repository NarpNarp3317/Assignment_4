#include "StockManager.h"


StockManager::StockManager(int maxCapacity, int currentCapacity)
{
	_maxCapacity = maxCapacity;
	_currentCapacity = currentCapacity;

}

void StockManager::StorePotion(PotionBottle newPotion)
{
	_potionStorage[newPotion.GetName()] += 1;// map will automatically create new name key if there was no same key before. MAGIC
}

map<string, int> StockManager::PutIngredientsOnBasket()
{
	return map<string, int>();
}

