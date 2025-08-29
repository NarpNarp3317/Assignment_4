#include <iostream>
#include "AlchemyWrokShop.h"

using namespace std;


AlchemyWorkShop::AlchemyWorkShop(string name)
{
	this-> _name = name;;

	RecipeManager* R_Manager = new RecipeManager;
	this->_Recipe_M = R_Manager;

	StockManager* S_Manager =new StockManager;
	this->_Stock_M= S_Manager;

	IngredientDetector* ListChecker = new IngredientDetector;
	this->_ListChecker= ListChecker;

}

string AlchemyWorkShop::GetWorkShopName()
{
	return this->_name;
}

void AlchemyWorkShop::MakePotion()
{
	// 1. type in name of the potion
	// 2. type in lists of ingredients;
	//    --> check if the ingredients are avaliable(can only use available ingredients)
		// if no ingredient --> try again
		// if ingredient available, goes on
	// 3. compare the ingredients and ingredients from stored recipe
		// if same ingredient is found, says "you created (the potion)!"
		// if there was no same ingredient, says"new potion created! would you save the potion?
			// if no-> dispose potion and end loop
			// if yes -> tell recipe manager to make new recipe and store it. and then store the potion on stock manager, end loop


	bool isrunning = true;

	while (isrunning)
	{
		string written_list="";
		cout << "Type in Ingredients :";
		cin >> written_list;
		printf("\n");

		if (!_ListChecker->MakeIngredientList(written_list))// generate the list and check if list making wasn't successful
		{// failed
			isrunning = false;
			break;
		}
		// successful
		map<string, int> ingredients = (_ListChecker->GetSortedIngredients());
		// now it's time for Recipe Manager's work;

		if (_Recipe_M->Find_Recipe_with_SameIngredients(ingredients)._potionName == "")// to return potion recipe as null, made new recipe named "".
																					//  --> this is used as the indicator of "no same ingredient list found"
		{// if there was no recipe sharing same ingredient list


			cout << "You have found new Potion!" << endl;

			bool isselected = false;
			char selectioninput;
			bool isyes =true;//default will be yes
			while (!isselected)
			{
				cout <<"Would you record the recipe for new potion ? (Y / N) : ";
				cin >> selectioninput;

				if (selectioninput == 'Y' || selectioninput == 'y')
				{
					isyes = true;
					isselected = true;
				}
				else if (selectioninput == 'N' || selectioninput == 'n')
				{
					isyes = false;
					isselected = true;
				}
				else
				{
					cout << "Invalid input, Plz try again." << endl;
				}
			}

			if (!isyes)// if selected no to record new recipe
			{
				cout << "New recipe discarded." << endl;
			}
			else// if selected yes!
			{
				bool isprocessing = false;
				string newRecipeName;
				string newPotionEffect;
				int newPotionPrice;


				while (!isprocessing)//-------------> type name
				{
					cout << "Typein name of new potion: ";
					cin >> newRecipeName;

					if (newRecipeName.size() == 0)//if no name was typed in;
					{
						cout << "No name was detected. Plz try again." << endl;
					}
					else isprocessing = true;
				}
				isprocessing = false;
				/*
				while (!isprocessing)//-------------> type effect
				{
					cout << "Typein name of new potion: ";
					cin >> newRecipeName;

					if (newRecipeName.size() == 0)//if no name was typed in;
					{
						cout << "No effect was written. Plz try again." << endl;
					}
					else isprocessing = true;

				}

				*/
				// effect can be a blank

				cout << "Type in potion effect : ";
				cin>> newPotionEffect;
				printf("\n");

				cout << "Type in potion price : ";
				cin >> newPotionPrice;
				printf("\n");

				PotionRecipe newPotionRecipe(newRecipeName, ingredients, newPotionEffect, newPotionPrice);// make new potion recipe
				_Recipe_M->AddPotionRecipe(newPotionRecipe);

				// now!!! make actual potion and store it on stock manager;
				
			}
			
		}






	}



}
