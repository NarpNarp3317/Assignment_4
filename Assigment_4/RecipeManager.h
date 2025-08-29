#pragma once
#include <vector>
#include <map>
#include "PotionBottle.h"
#include "PotionRecipe.h"


class RecipeManager
{
public:
	RecipeManager();

private:

	vector<PotionRecipe> _recipes;

public:

	void AddPotionRecipe(PotionRecipe newrecipe);

	void Make_and_Add_PotionRecipe(string potion_name, map<string, int>ingredients, string effect, int price);
	
	PotionRecipe Find_Recipe_with_SameIngredients(map<string, int>ingredients);

	void BURN_THE_ALEXANDRIA();// clear all of the recipes


	~RecipeManager();// when the manager is gone;
};