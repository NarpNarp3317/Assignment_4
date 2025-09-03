#include "RecipeManager.h"
#include "search.h"
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


bool RecipeManager::AddPotionRecipe(PotionRecipe newrecipe)// there could be a situation when recipes cannot be stored.
															//--> for that, make this function return bool so that user of this function can know if function worked or not
{
	_recipes.push_back(newrecipe);
	return true;
}

vector<PotionRecipe> RecipeManager::GetRecipes()
{
	return _recipes;
}

PotionRecipe RecipeManager::GetRecipeUsingName(string potion_name)//instead of actually making and storing class of potions, bring recipes and get info from it
{
	for (const PotionRecipe& recipe : _recipes)
	{
		if (recipe._potionName == potion_name) return recipe;
	}
	return {{},{},{},{}};//empty class
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

vector<SearchResult> RecipeManager::SearchPotionRecipes(const vector<string> &keywords)
{
	vector<SearchResult> final_results = {};
	SearchResult combined_result;
	SearchResult result;
	
	/*
	for (const string& keyword : keywords)//loop for given keywords
	{
		SearchResult combined_result;// to stop duplication

		for (const PotionRecipe& recipe : _recipes)// find matching 
		{
			// make potion name, ingredient, effect, price in one string
			//ex. Redpotion / acid, 2*water, 2*copper / damage++ / 20

			// recipes into one string

			

			if (result.name != "")// if there was matching
			{
				final_results.push_back(result);
			}
		}
	}
	*/
	// merge the string first and then find keyword

	for (const PotionRecipe& recipe : _recipes)
	{
		combined_result.name = ConvertIntoOneString(recipe);

		for (const string& keyword : keywords)
		{
			result = StringChecker(keyword, combined_result.name);//gets matching result and store it into "result"
			combined_result.indicator.insert(combined_result.indicator.end(), result.indicator.begin(), result.indicator.end());
			
		}
		if (!combined_result.indicator.empty())// if there is matching keyword
		{
			final_results.push_back(combined_result);
		}
	}

	return final_results;
}

string RecipeManager::ConvertIntoOneString(PotionRecipe recipe)
{
	// ingredients into one string
	string ingredients_in_one;
	
	const map<string, int>& current_ingredietns = recipe._ingredients;
	// first ingredient
	
	string current_ingrerient_name;

	// make potion name, ingredient, effect, price in one string
	//ex. Redpotion / acid, 2*water, 2*copper / damage++ / 20

	for (map<string, int>::const_iterator it = current_ingredietns.begin(); it != current_ingredietns.end(); it++)
	{
		if (it != current_ingredietns.begin())
		{
			ingredients_in_one += " / ";// so that / can be placed between ingredients
		}

		int current_ingredient_count= it->second;
		if (current_ingredient_count == 1)// no need for 1*name, just name
		{
			ingredients_in_one += it->first;
		}
		else// n*ingredient
		{
			ingredients_in_one += to_string(current_ingredient_count) + "*" + it->first;
		}	
	}
	string Recipe_In_one = recipe._potionName + " / " + ingredients_in_one + " / Effect: " + recipe._effect + " / " + "price: " + to_string(recipe._price);
	// done
	return Recipe_In_one;
}

vector<string> RecipeManager::ConvertForStatus()// with no search result, just plain status
{
	vector<string> converted_strings;

	if (_recipes.empty()) return converted_strings;//return empty

	for (const PotionRecipe& current_recipe : _recipes)
	{
		converted_strings.push_back(ConvertIntoOneString(current_recipe));
	}

	return converted_strings;
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
