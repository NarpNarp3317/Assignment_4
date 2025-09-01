#include <iostream>
#include "AlchemyWrokShop.h"
#include "Ask_and_Proceed.h"

using namespace std;

AlchemyWorkShop::AlchemyWorkShop(string name)
{
	this-> _name = name;
	this->_current_coins = 30;//shop with starting budged!

	//this->_comands_Map = {};//starts with empty
	SetInputKeyMapping();// set comands map;

	this->_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);// use this to change the text color

	RecipeManager* R_Manager = new RecipeManager;
	this->_Recipe_M = R_Manager;

	StockManager* S_Manager =new StockManager(3);// for asignment, max potion count is 3
	this->_Stock_M= S_Manager;

	IngredientDetector* ListChecker = new IngredientDetector;// this could have been simply just header, but for now, keep it this way
	this->_ListChecker= ListChecker;

	ListPrinter* Printer = new ListPrinter(32, _output_handle);//max width of list and put outputhandle inthere
	this->_ListPrinter = Printer;

}

string AlchemyWorkShop::GetWorkShopName()
{
	return this->_name;
}

void AlchemyWorkShop::SetCoinPurse(int current_coins)//cheat code!
{
	this->_current_coins = current_coins;
}

bool AlchemyWorkShop::PaywithCoin(int price)
{
	if (_current_coins < price)// if there is not enough coins to pay
	{
		return false;// can't pay
	}
	else
	{
		_current_coins -= price;
		return true;
	}
}

void AlchemyWorkShop::EarnCoins(int earning)
{
	_current_coins += earning;
}

void AlchemyWorkShop::SetInputKeyMapping()
{
	
	//using Str_key_functionPtr
	// put function name and funtion address for the function pointer)
	//_comands_Map['1'] = { "Make Potion", AlchemyWorkShop::MakePotion};
	//_comands_Map['s'] = _comands_Map['S'];//uppercase and lowecase shares same value// for now, use number for functions
	//Problem: function ptr only works with static and free functions but not member functions that requires (this).
	//--> for that reason, used <functional>
	
	_comands_Map['1'] = { "Make Potion",[this]() {this->MakePotion(); } };//use lambda function to store current class as object and use it to call function
	_comands_Map['2'] = { "Print Out Status",[this]() {this->PrintStatus(); } };
	_comands_Map['3'] = { "Search by keyword",[this]() {this->MakePotion(); } };
	_comands_Map['4'] = { "Use Potion",[this]() {this->MakePotion(); } };
	_comands_Map['5'] = { "Sell Potion",[this]() {this->MakePotion(); } };
	_comands_Map['6'] = { "Leave "+ this->_name,[this]() {this->MakePotion(); } };

}

void AlchemyWorkShop::GetCommand()
{
	printf("\n");//add vertical pad
	// print out the keys for the functions first

	cout << "//======= Command keys =======//" << endl;

	for (pair<const char, Str_Key_function>& pair : _comands_Map)
	{
		cout << "(" << pair.first << ") " << pair.second.function_name << endl;
	}
	//printing key map done, proceed
	printf("\n");//add vertical pad

	AskAndProceed("Type key to proceed: ", _comands_Map);// this will ask for char key and call function in commands_map
}

void AlchemyWorkShop::PrintStatus()
{
}

void AlchemyWorkShop::MakePotion()
{
	//how it goes
	/*
	 1. type in name of the potion
	 2. type in lists of ingredients;
	    --> check if the ingredients are avaliable(can only use available ingredients)
		 if no ingredient --> try again
		 if ingredient available, goes on
	 3. compare the ingredients and ingredients from stored recipe
		 if same ingredient is found, says "you created (the potion)!"
		 if there was no same ingredient, says"new potion created! would you save the potion?
			 if no-> dispose potion and end loop
			 if yes -> tell recipe manager to make new recipe and store it. and then store the potion on stock manager, end loop
	*/

	// befor writing down recipies, shows lists of available ingredients first.
	map<string,int> ingredients=_Stock_M->GetIngredientStorage();

	_ListPrinter->PrintOutList(ingredients);// give the list to printer and print out the list!

	printf("\n");// for vertical pad

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

 void AlchemyWorkShop::StartSearch()
{
	 // just print out everything
	 /*
	 char input='\0';
	 while (input == '\0')
	 {
		 cout << "(1). Search Potion. / (2). Search Ingredient" << endl;
		 cout << ">>";
		 cin >> input;
		 if (input == '1')
		 {

		 }
		 else if(input=='2')
		 {

		 }
		 else
		 {
			 cout << "Error, Invalid input detected. Plz try again." << endl;
		 }
	 }
	 */

	 
}

 void AlchemyWorkShop::Search_Potion()
 {
 }

 void AlchemyWorkShop::Search_Ingredients()
 {
 }


 void AlchemyWorkShop::StockRecipe(PotionRecipe recipe)
 {
	 _Recipe_M->AddPotionRecipe(recipe);
 }

 void AlchemyWorkShop::StockPotion(PotionBottle newPotion)
 {
	 if (_Stock_M->GetCurrentCapacity() < _Stock_M->GetMaxCapacity())//if there is enough room for more potion
	 {
		 _Stock_M->StorePotion(newPotion);
	 }
	 else
	 {
		 cout << "Not enough space for Potion. (1) Use it by your self. /(2) Sell it to the customer. / (3) Discard the potion. " << endl;

		 char input;// = '\0';
		 cin >> input;

		 bool isrunning = true;
		 {
			 while (isrunning)
			 {
				 if (input == '1')
				 {
					 cout << "Player used the potion." << endl;
					 cout << newPotion.GetEffect() << endl;//print out effect

				 }
				 else if (input == '2')
				 {
					 cout << "Potion is sold to the customer." << endl;

				 }
				 else if (input == '3')
				 {
					 cout << "Potion is disposed. What a waste." << endl;
					 isrunning = false;
				 }
				 else
				 {
					 cout << "Invalid input. Plz, try agin." << endl;
				 }
			 }
		 }
	 } 
 }


 PotionBottle AlchemyWorkShop::SelectPotion()
 {
	 if (_Stock_M->GetCurrentCapacity() == 0)
	 {
		 cout << "There is no potion left in storage." << endl;
		 return {};
	 }
	 cout << "Select Potion";
	 // print list of potions with number to choose;

	map<string,int> potions= _Stock_M->GetPotionStorage();

	map<int,string> selectionList;// for selection only

	int number = 1;
	for (pair<const string, int>& pair : potions)
	{
		if (pair.second != 0)// only if there is potion// map can include name of potion that storage doesnt have. the count can be checked by the value
		{
			selectionList[number] = pair.first;

			if (pair.second > 1)//if current potion count is more than one
			{
				cout << "*" << pair.second;// ex. 2*RedPotion
			}
			cout << "(" << number << ") " << pair.first;
			++number;// for next potion number
		}
		//if potion has no count(only name for key), do nothing
		// dont erase the key. there is difference between "no potion left" and "shop didn't have it in the first place"

	}// endl of loop
	printf("\n");

	bool isrunning = true;
	int input;
	while (isrunning)
	{
		cout << ">>";
		cin >> input;

		map<int, string>::iterator it = selectionList.find(input);
		if (it != selectionList.end())
		{
			vector<PotionBottle> real_potions = _Stock_M->GetActualPotionList();
			for (PotionBottle& potion : real_potions)
			{
				if (potion.GetName() == it->second)// if potion names are same
				{
					return potion;// just end function and leave!
				}
			}
		}
		else
		{
			cout << "Invalid input detected. Plz, try again." << endl;
		}
	}
 }



 bool AlchemyWorkShop::SellPotion(PotionBottle Potion)
 {
	 // different types of potions are stored. and each potions has different prices. for now, select potion and sell.
	 /*
	 cout << "Howmany? :";
	 cin >> sellcount;
	 printf("\n");

	 if (sellcount > currentC)//try to sell more than what shop has
	 {
		 cout << "Not enough Potion is in storage.";
		 SetConsoleTextAttribute(_output_handle, 12);// turn text to red
		 cout << currentC << "/" << maxC << ")" << endl;
		 SetConsoleTextAttribute(_output_handle, 7);//back to normal
	 }
	 else if (sellcount <= currentC)
	 {
		 cout << "Sold " << sellcount << " Potions. " << currentC- sellcount << "/" << maxC << ")" << endl;
		 _Stock_M->SetCurrentCapacity(currentC - sellcount);// update the current count

	 }
	 else
	 {
		 cout << "Invalid number detected." << endl;
	 }

	 */

	 if (_Stock_M->RemovePotion(Potion))//if potion was successfully removed
	 {
		 cout << "Potion is sold to the customer." << endl;
		 return true;
	 }
	 cout << "Couldn't sell the potion." << endl;
	 return false;// if it failed
 }

 bool AlchemyWorkShop::UsePotion(PotionBottle Potion)
 {
	 if (_Stock_M->RemovePotion(Potion))//if potion was successfully removed
	 {
		 cout << "Player used the potion." << endl;
		 cout << Potion.GetEffect() << endl;// print out the potion effect
		 return true;
	 }

	 cout << "Player couldn't use the potion." << endl;
	 return false;// if it failed
 }

 void AlchemyWorkShop::LeaveShop()
 {
	 bool isrunning = true;
	 char input;

	 while (isrunning)
	 {
		 cout << "Do you really want to leave? ( Y / N )";
		 cin >> input;

		 if (input == 'Y' || input == 'y')
		 {
			 cout << "Good bye, and come again to " << _name << "." << endl;
			 this->~AlchemyWorkShop();
			 isrunning = false;
		 }
		 else if (input == 'N' || input == 'n')
		 {
			 isrunning = false;
		 }
		 else
		 {
			 cout << "Invalid input detected. Plz try again." << endl;
		 }
	 }
 }

 AlchemyWorkShop::~AlchemyWorkShop()// clean up!
 {
	 _Recipe_M->~RecipeManager();
	 delete _Recipe_M;

	 _Stock_M->~StockManager();
	 delete _Stock_M;

	 _ListChecker->~IngredientDetector();
	 delete _ListChecker;

	 _ListPrinter->~ListPrinter();
	 delete _ListPrinter;
 }

 /*
 bool AlchemyWorkShop::UsePotion(PotionBottle Potion, const string& bywho)
 {
	 if (bywho.empty())// if no name was typed
	 {
		 cout << "Error, string by who is not typed" << endl;// only for debug
		 return false;
	 }

	 if (_Stock_M->RemovePotion(Potion))//if potion was successfully removed
	 {
		 string potion_name = Potion.GetName();
		 cout << bywho << " used" << potion_name << "." << endl;
		 cout << Potion.GetEffect() << endl;// print out the effect;
		 return true;
	 }
	 return false;// if it failed
 }
 */