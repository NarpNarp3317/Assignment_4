#pragma once
#include <vector>
#include <map>
#include "PotionBottle.h"
#include "PotionRecipe.h"
#include "SearchResult.h"


class RecipeManager
{
public:
	RecipeManager();

private:

	vector<PotionRecipe> _recipes;
	//vector<PotionBottle> _potion_list;// this is for when potion needs to be used. when use potion is called, // maybe this was supposed to be in stock manager... fuck

public:

	bool AddPotionRecipe(PotionRecipe newrecipe);

	vector<PotionRecipe> GetRecipes();// returns whole recipes
	PotionRecipe GetRecipeUsingName(string potion_name);

	void Make_and_Add_PotionRecipe(string potion_name, map<string, int>ingredients, string effect, int price);
	
	PotionRecipe Find_Recipe_with_SameIngredients(map<string, int>ingredients);

	vector<SearchResult> SearchPotionRecipes(const vector<string>& keywords);
	string ConvertIntoOneString(PotionRecipe recipe);

	vector<string> ConvertForStatus();

	void BURN_THE_ALEXANDRIA();// clear all of the recipes


	~RecipeManager();// when the manager is gone;
};