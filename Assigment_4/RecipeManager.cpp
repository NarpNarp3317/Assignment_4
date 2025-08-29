#include "RecipeManager.h"
#include <iostream>

RecipeManager::RecipeManager()
{
	// default recipes
	PotionRecipe Red_Potion("Red Potion", { {"salt",2},{"red pepper", 2}, {"tomato",5} }, "User health++", 3);
	PotionRecipe Blue_Potion("Blue Potion", { {"wild berry",5},{"lemon", 1}, {"sugar",5} }, "User is faster for next 5 min", 3);
	PotionRecipe Yellow_Potion("Yellow Potion", { {"chilly powder",2},{"lsd", 2}, {"meth",1} }, "Bell! \a", 3);

	_recipes =// adding default recipes
	{
		Red_Potion,Blue_Potion,Yellow_Potion
	};
}


void RecipeManager::AddPotionRecipe(PotionRecipe newrecipe)
{
	_recipes.push_back(newrecipe);
}

void RecipeManager::Make_and_Add_PotionRecipe(string potion_name, map<string, int> ingredients, string effect, int price)
{
	PotionRecipe newRecipe(potion_name, ingredients, effect, price);

	// after new potion recipe is made, store it on the recipe stock;
	AddPotionRecipe(newRecipe);
}

PotionRecipe RecipeManager::Find_Recipe_with_SameIngredients(map<string, int>ingredients)
{
	for (PotionRecipe recipe : _recipes)
	{
		if (ingredients == recipe._ingredients)// if the comparing ingredient list shares the same list from the recipe storage,
		{
			return recipe;
		}
	}// if the loop is done// no list with same ingredient list was found;
	PotionRecipe Nullrecipe("",{},"",0);// for temporary way, make potion with name ""
	return  Nullrecipe ;//return nothing// couldnt find the way(could use pointer, but for now, this way)
}

void RecipeManager::BURN_THE_ALEXANDRIA()// all is lost
{
	while (!_recipes.empty())// burn the recipe one by one till it gets empty
	{
		cout << _recipes.back()._potionName << " got destroyed!" << endl;// _recipes.back() the last index, infront of end()
		_recipes.pop_back();
	}

	//_recipes.clear(); --> not dramatic enough
}

RecipeManager::~RecipeManager()// good bye :^)
{
	BURN_THE_ALEXANDRIA();
}
