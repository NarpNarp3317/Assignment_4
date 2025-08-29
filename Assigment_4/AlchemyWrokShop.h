#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "RecipeManager.h"
#include "PotionRecipe.h"
#include "StockManager.h"
#include "IngredientDetector.h"
#include "PotionBottle.h"


using namespace std;

class AlchemyWorkShop
{
public:
	AlchemyWorkShop(string _name);

private:
	string _name;

	map<char, string> _input_keys;

	RecipeManager* _Recipe_M;
	StockManager* _Stock_M;
	IngredientDetector* _ListChecker;





public:


	string GetWorkShopName();

	void SetInputKeyMapping();


	void Get_Command(char input);
	void DoAsCommand(char input);// do functions as command input


	void PrintStatus();//PrintOut the Status;

	//====== Make Potion =======//
	void MakePotion();
	// make Potion and store the recipe on recipe manager, and store potion on stock manager

	//====== search ======//
	void DoSearch();

	void Search_by_Potion();

	void Search_by_Ingredients();// can search with multiple ingredients

	//====== Recipe =======//
	PotionRecipe RequestRecipe();// request recipe and return when writing it is done

	void StockRecipe(PotionRecipe recipe);// add the finished recipe to the RecipeManager
	void StockPotion(PotionBottle newPotion);//add Potion to the StockManager



};