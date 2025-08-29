#pragma once
//#include <vector> change it into a map
#include <map>
#include <string>
#include "PotionBottle.h"

using namespace std;
/*
class PotionRecipe
{
public:
	
	PotionRecipe(string potion_name, vector<string> ingredients);

private:
	string _potion_name;
	//string recipe_name;
	vector<string> _ingredients;
	string _recipe;

public:
	string GetName();// return name;
	vector<string> GetIngredients();// return required ingredients


	string GetRecipe();// get string of recipe

	// this is work of recipe manager

	void MakeRecipe()// set string of recipe
	{
		this->recipe = recipe_name + "\n"
			+ "Ingredients :";


		for (string ingredient : ingredients)// for each loop
		{
			recipe += " " + ingredient;
		}
		
		recipe += "\n\n";
		// add instructions

		recipe += "--------------" + "\n";


	}
	*/
// this seems better when it is struct rather than class

struct PotionRecipe
{
	PotionRecipe(string name, map<string, int> ingredients, string effect, int price)
	{
		_potionName = name;
		_ingredients = ingredients;
		_effect = effect;
		_price = price;
	}


	string _potionName;
	map<string, int> _ingredients;


	//-------- what potion by recipe would have -----//

	string _effect;// optional i guess?
	int _price;// price per potion
	
	//PotionBottle* _created_Potion;//address of what this recipe creates// creating potion would be done in alchemy workshop with recipe
};