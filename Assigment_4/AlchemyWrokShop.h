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
#include "Key_function.h"// to hold string of what function does and function pointer to be called
#include "ListPrinter.h"
#include "Windows.h"// for text color change

using namespace std;

class AlchemyWorkShop
{
public:
	AlchemyWorkShop(string _name);

private:
	string _name;
	int _current_coins;//if potion was sold, where would money goes?

	//map<char, string> _input_keys;
	map<const char, Str_Key_function> _comands_Map;// change it into map of keys for functionPtrs

	RecipeManager* _Recipe_M;
	StockManager* _Stock_M;

	IngredientDetector* _ListChecker;
	ListPrinter* _ListPrinter;

	HANDLE _output_handle;
	//HANDLE _input_handle;// maybe too far



public:


	string GetWorkShopName();

	void SetCoinPurse(int current_coins);//only for cheat code

	bool PaywithCoin(int price);// if there is no more money to spend, return false
	void EarnCoins(int earning);




	void SetInputKeyMapping();


	void GetCommand();// do functions as command input


	void PrintStatus();//PrintOut the Status;

	//====== Make Potion =======//
	void MakePotion();
	// make Potion and store the recipe on recipe manager, and store potion on stock manager

	//====== search ======//
	void StartSearch() ;

	void Search_Potion();

	void Search_Ingredients();// can search with multiple ingredients

	//====== Recipe =======//
	//PotionRecipe RequestRecipe();// request recipe and return when writing it is done

	void StockRecipe(PotionRecipe recipe);// add the finished recipe to the RecipeManager
	void StockPotion(PotionBottle newPotion);//add Potion to the StockManager



	PotionBottle SelectPotion();// for sell and use potion// returns selected potion
	bool SellPotion(PotionBottle Potion);//sell potion// return if it sold the potion or not
	bool UsePotion(PotionBottle Potion);// use by your self// return if player used potion or not
	//bool UsePotion(PotionBottle Potion, const string& bywho);// it turns out copying every string would be a wasteful. use reference to get the string
														// --> and add const to prevent unwanted modification
	//--> i get it but turns outm name for user is not needed for now.




	void LeaveShop();
	~AlchemyWorkShop();
};