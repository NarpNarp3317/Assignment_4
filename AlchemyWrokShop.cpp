#include "AlchemyWrokShop.h"
#include "Ask_and_Proceed.h"

//using namespace std;// using this and using windows.h cause problem.  i geuss it works when they are not in same cpp?

AlchemyWorkShop::AlchemyWorkShop(string name)
{
	this-> _name = name;
	this->_current_coins = 30;//shop with starting budged!

	this->_empty_bottle_count=0;// default count of 5
	this->_bottle_price = 2;// empty bottle price it aint cheep
	this->_ingredient_add_cost = 5;//per ingredient

	this->_is_staying = true;// to leave the shop and stop loop of choices in int main

	//this->_comands_Map = {};//starts with empty
	SetInputKeyMapping();// set comands map;

	this->_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);// use this to change the text color

	this->_Recipe_M = new RecipeManager;
	
	this->_Stock_M = new StockManager(3);// for asignment, max potion count is 3
	
	this->_ListChecker = new IngredientDetector;// this could have been simply just header, but for now, keep it this way
	
	this->_ListPrinter = new ListPrinter(32, _output_handle,2);//max width of list and put outputhandle inthere// green for highlight color (2)
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
		PrintCoinStatus();
		return true;
	}
}

void AlchemyWorkShop::EarnCoins(int earning)
{
	_current_coins += earning;
	PrintCoinStatus();
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
	_comands_Map['2'] = { "Print Out Status",[this]() {this->PrintAllStatus(); } };
	_comands_Map['3'] = { "Search by keyword",[this]() {this->StartSearch(); } };
	_comands_Map['4'] = { "Use Potion",[this]() {this->TrytoUsePotion(); } };
	_comands_Map['5'] = { "Sell Potion",[this]() {this->TrytoSellPotion(); } };
	_comands_Map['6'] = { "Add New Ingredient",[this]() {this->AddIngredients(); } };
	_comands_Map['7'] = { "Leave "+ this->_name,[this]() {this->LeaveShop(); } };
	_comands_Map['8'] = { "Cheat code", [this]() {this->KABOOM(); } };
	

}

//void AlchemyWorkShop::GetCommand()--> to return bool for int main for ending the loop of choices
bool AlchemyWorkShop::GetCommand()
{
	if (!this->_is_staying) return false;// for stop getting command and leave the shop
	else
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

		return true;
	}

}

void AlchemyWorkShop::PrintAllStatus()//print all status
{
	PrintCoinStatus();
	PrintoutBottleStatus();
	PrintIngredientStatus();
	PrintPotionStatus();	
	PrintRecipeStatus();

	EnterToContinue();// enter to continue
}

void AlchemyWorkShop::PrintPotionStatus()
{
	cout << "//===== Potion Status =====//" << endl;
	_ListPrinter->PrintOutMapList(_Stock_M->GetPotionStorage(), horizontal);
	cout  << endl;
}

void AlchemyWorkShop::PrintIngredientStatus()
{
	cout << "//===== Ingredient Status =====//" << endl;
	_ListPrinter->PrintOutMapList(_Stock_M->GetIngredientStorage(), horizontal);
	cout << endl;
}

void AlchemyWorkShop::PrintRecipeStatus()
{
	cout << "//===== Recipe Status =====//" << endl;
	_ListPrinter->PrintOutVectorList(_Recipe_M->ConvertForStatus(),vertical);
	cout << endl;
}

void AlchemyWorkShop::PrintCoinStatus()
{
	cout << "Current coins: ";
	//SetConsoleTextAttribute(_output_handle, 14);// yellow for coin
	PrintColorString(to_string(_current_coins), 14);
	//SetConsoleTextAttribute(_output_handle, 7);//default white
	printf("\n");
}

void AlchemyWorkShop::PrintoutBottleStatus()
{
	cout << "Current Bottle: " << _empty_bottle_count << endl;
}

void AlchemyWorkShop::PrintColorString(string string, int color)
{
	SetConsoleTextAttribute(_output_handle, color);
	cout << string;
	SetConsoleTextAttribute(_output_handle, 7);// default white color
}

void AlchemyWorkShop::MakePotion()//--------------------------------------------------------------- ** Make Potion **
{
	// check if there is empty bottle to hold potion;
	if (_empty_bottle_count < 1)
	{
		cout << "There is no bottle to make potion." << endl;

		if (AskYes_or_No("Do you wish to buy more bottle? (Y/N): ", { 'Y','y' }, { 'N','n' }))
		{
			if (PaywithCoin(_bottle_price))
			{// paid with coin
				cout << "Purchased 1*empty potion bottle. Curretnt coin:";
				PrintColorString(to_string(_current_coins), 14);// print coin with yellow	
				printf("\n");
				_empty_bottle_count += 1;// add bottle, continue
			}
			else
			{// could not purchase the bottle
				cout << "Not enough coints to purchase empty bottle." << endl;
				return;// end function
			}
		}
		else
		{
			return;// did not purchase the bottle, end function
		}
	}
	// if enough potions are in shop, skip if


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
	map<string, int> sorted_ingredients;

	//_ListPrinter->PrintOutMapList(ingredients,vertical);// give the list to printer and print out the list! // not done yet!
	PrintIngredientStatus();//changed it into function and now it can used in here. fuck yeah

	printf("\n");// for vertical pad

	bool isrunning = true;

	// type in ingredients
	while (isrunning)
	{
		string written_list;// = "";
		cout << "Type in Ingredients :";

		//cin >> written_list;// this cannot gets string with " "

		std::cin.ignore();
		getline(cin, written_list);// iostream holds the prior string/char. to 
		//cout << written_list;	
		printf("\n");

		if (!_ListChecker->MakeIngredientList(written_list))// generate the list and check if list making wasn't successful
		{// failed
			cout << "Invalid ingredients. Plz try again." << endl;
		}
		else
		{
			// successful
			sorted_ingredients = (_ListChecker->GetSortedIngredients());
			// now it's time for Recipe Manager's work;
			isrunning = false;
			break;
		}
	}
	// if new ingrdients were found, put it on the ingredient list // before that, 1. check if there is new ingredient, check if there is enough ingredients in storage.(new ingredient will be purchased get 10)

	vector<string> new_ingredients = _Stock_M->DetectNewIngredients(sorted_ingredients);
	short int lenght = new_ingredients.size();//more inexpensive?

	short int total_cost = 0;

	if (lenght > 0)
	{
		cout << "New Ingredient" << ((lenght > 1) ? "s are" : " is") << " detected." << endl;

		cout << new_ingredients[0];// print first 

		for (short int i{ 1 }; i < lenght; i++)// no more =, {} for safety and cost
		{
			cout << ", " << new_ingredients[i];
		}
		printf("\n");

		total_cost = lenght * _ingredient_add_cost;

		cout << "Ingredient Expansion cost: ( ";

		PrintColorString(to_string(total_cost), 14);

		cout << " )" << endl;

		if (AskYes_or_No("Do you wish to pay? ( Y / N ) :", { 'Y','y' }, { 'N','n' }))
		{//yes
			if (PaywithCoin(total_cost))
			{
				// make a map of new ingredients with default
				int defualt_count=_Stock_M->GetMax_ingredientCounts();
				map<string, int> converted_ingredients;

				for (const string& name : new_ingredients)
				{
					converted_ingredients[name] = defualt_count;
				}
				//conversion completed

				_Stock_M->AddIngredients(converted_ingredients);


				cout << "New ingredients are added." << endl;
				//PrintCoinStatus();// pay with coin will update the coin status automatically
				// print out the ingredient state;



				//check if the ingredients are enough
				if (_Stock_M->UseIngredients(sorted_ingredients))// put the first writen list of ingredients to use and deduct the used amount
				{// this function returns bool
					// if it used ingredients
					_empty_bottle_count -= 1;//decrement used empty potion bottle // this is where it finalized!
					//potion is created
				}
				else
				{
					cout << "Not enough ingredients are in the storage." << endl;

					EnterToContinue();// enter to continue
					return;// making potion failed. end function
				}
				
				

			}
			else
			{
				cout << "Not enough coins to purchase new ingredients." << endl;

				EnterToContinue();// enter to continue
				return;// end make potion function
			}
		}
		else
		{//no
			cout << "Potion making is cancled." << endl;

			EnterToContinue();// enter to continue
			return;// end make potion function
		}

	}
	
	// end of situation if new ingredients were/was found
	

	if (_Recipe_M->Find_Recipe_with_SameIngredients(sorted_ingredients)._potionName == "")// to return potion recipe as null, made new recipe named "".
		//  --> this is used as the indicator of "no same ingredient list found"
	{// if there was no recipe sharing same ingredient list

		cout << "You have found new Potion!" << endl;
		/*
		bool isselected = false;
		char selectioninput;
		bool isyes = true;//default will be yes
		while (!isselected)
		{
			cout << "Would you record the recipe for new potion ? (Y / N) : ";
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
		*/ // use ask yes or no

		bool isprocessing = false;
		string newPotionName;
		string newPotionEffect;
		int newPotionPrice;

		if (!AskYes_or_No("Would you record the recipe for new potion ? (Y / N) : ", { 'Y','y' }, { 'N','n' }))
		{//no(!)
			cout << "New recipe and potion are discarded." << endl;
		}
		else
		{//yes
		/*
		if (!isyes)// if selected no to record new recipe
		{
			cout << "New recipe discarded." << endl;
		}
		

		else// if selected yes!
		{
		*/ // no more using while
			
			while (!isprocessing)//-------------> type name
			{
				cout << "Type in name of new potion: ";
				cin.ignore();
				getline(cin, newPotionName);

				if (newPotionName.size() == 0)//if no name was typed in;
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

			//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//---------------------------------------------sdfasad sfewsf 

			
			getline(cin, newPotionEffect);
			cout << endl;

			cout << "Type in potion price : ";
			cin >> newPotionPrice;
			cout << endl;

			PotionRecipe newPotionRecipe(newPotionName, sorted_ingredients, newPotionEffect, newPotionPrice);// make new potion recipe
			if (_Recipe_M->AddPotionRecipe(newPotionRecipe))
			{
				cout << newPotionName << " is added as new recipe." << endl;
				_Stock_M->AddNewPotion(newPotionName);
				cout << newPotionName << " is kept in storage" << endl;
			}
			else
			{
				cout << newPotionName << " could not be added." << endl;// for now, there is no reason for this to be triggerd.
			};
			// now!!! make actual potion and store it on stock manager;
		}//----------------------------------------------------------------------------------->Potion recipe storing or discarding is done
		

		//StockPotion(newPotionName);//handle the potion//---> this only works if the potion name is not stored in stock yet....fuck
		/*
		if (_Stock_M->CheckStorage())// check potion storage can add more potion
		{// if there is enough space
			if (_Stock_M->StorePotion(newPotionName))
			{
				cout << "Potion is Stored in Storage." << endl;
			}
			else
			{
				cout << "There is no more space for new potion" << endl;
			}
		}
		*/ 
		//when player decides to discard the recipe, the "new" potion didnt get its name, effect, or price. all of these wont work. just throw it away as well.
		
	}
	EnterToContinue();// enter to continue
}

 void AlchemyWorkShop::StartSearch()
{
	 cout << "* Only Alphabet can be used as Search key word." << endl;
	 cout << "Type in keyword: ";
	 string written_string;

	 cin.ignore();
	 getline(cin, written_string);

	 if (written_string.empty())
	 {
		 cout << "No keyword detected." << endl;

		 EnterToContinue();// enter to continue
		 return;// end function
	 }
	 // convert string of keywords to seperate chunks of keyword
	 if (!_ListChecker->MakeIngredientList(written_string))
	 {
		 cout << "Invalid Keyword Detected." << endl;
	 }
	 //after conversion is done;
	 //------------check search result of ingredients, potion recipes
	 map<string,int> temp_chunks_of_keyword= _ListChecker->GetSortedIngredients();// well.... it was supposed to be used for ingredient detection, but in here, it is reused for detecting seperate keyword
	 // this would be nice if  it was a vector, but for now, work with what i got
	 // fuck it, conversion
	 vector<string> chunks_of_keyword = {};
	 for (const pair<string, int>& keyword : temp_chunks_of_keyword)
	 {
		 chunks_of_keyword.push_back(keyword.first);
	 }
	 // vector ready to be used

	 // start search using keyword chunks
	 // 
	 //---------------------------------------------------------------------------------------------------------- ** Search Potions ** (by name and by its recipe)
	 _ListPrinter->PrintOutSearchResults((_Recipe_M->SearchPotionRecipes(chunks_of_keyword)), vertical);

	 //---------------------------------------------------------------------------------------------------------- ** Search Ingredients **
	 //_ListPrinter->PrintOutSearchResults((_Stock_M->(chunks_of_keyword)), vertical);


	 EnterToContinue();// enter to continue


	 

	



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

 void AlchemyWorkShop::AddIngredients()// as command, make new ingredient for a price, if the ingredient with same name already exist, dont charge and store new ingredient
 {

 }

 void AlchemyWorkShop::StockRecipe(PotionRecipe recipe)
 {
	 _Recipe_M->AddPotionRecipe(recipe);
 }

 void AlchemyWorkShop::StockPotion(string newPotion)
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

					 PotionRecipe Potion = _Recipe_M->GetRecipeUsingName(newPotion);

					 cout << Potion._effect << endl;//print out effect

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


 string AlchemyWorkShop::SelectPotion()
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
	for (const pair<string, int>& pair : potions)
	{
		if (pair.second != 0)// only if there is potion// map can include name of potion that storage doesnt have. the count can be checked by the value
		{
			selectionList[number] = pair.first;// put on a selection map

			//----- for print out-----//

			cout << "(" << number << ") " << pair.first;//(1) Red_Potion

			if (pair.second > 1)//if current potion count is more than one
			{
				cout << " x" << pair.second << " / ";// ex. (1) RedPotion x2 / (2) BluePotion / (3) YellowPotion x3....
			}
			
			++number;// for next potion number
		}
		//if potion has no count(only name for key), do nothing
		// dont erase the key. there is difference between "no potion left" and "shop didn't have it in the first place"

	}// endl of loop// printing is done
	printf("\n");

	bool isrunning = true;
	int input;
	while (isrunning)//
	{
		cout << ">>";

		cin.ignore(99999, '\n');
		cin >> input;

		map<int, string>::iterator it = selectionList.find(input);
		if (it != selectionList.end())//input number is same as the key of selection map
		{
			/*
			for (const string & name : real_potions)
			{
				if (potion.GetName() == it->second)// if potion names are same
				{
					return potion;// just end function and leave!
				}
			}
			*/
			// just return the name from the selection map
			return selectionList[input];
		}
		else
		{
			cout << "Invalid input detected. Plz, try again." << endl;
		}
	}
 }

 bool AlchemyWorkShop::TrytoSellPotion()// select+sell
 {
	 return SellPotion(SelectPotion());
 }

 bool AlchemyWorkShop::TrytoUsePotion()//select+use
 {	
	 return  UsePotion(SelectPotion());
 }

 bool AlchemyWorkShop::SellPotion(string Potion_name)
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

	 if (_Stock_M->RemovePotion(Potion_name))//if potion was successfully removed
	 {
		 PotionRecipe Potion = _Recipe_M->GetRecipeUsingName(Potion_name);

		 int potion_price = Potion._price;

		 int discount_price = ((potion_price - _bottle_price > 0) ? potion_price - _bottle_price : 0);
		 //if(potion_price- _bottle_price<min_margin)

		 string question = "Customer ask for discount for returning empty bottle. Discount-price(" + to_string(discount_price) + ")\n Do you accept? ( Y /N ) >> ";

		 if (AskYes_or_No(question, {'Y', 'y'}, {'X','x'}))// ask question
		 {// if Y
			 cout << "Potion is sold to the customer." << endl;
			 _empty_bottle_count += 1;// return the empty bottle
			 EarnCoins(discount_price);

			 EnterToContinue();// enter to continue
			 return true;
		 }
		 else
		 {// if N
			 cout << "Potion is sold to the customer." << endl;// no discount!
			 EarnCoins(potion_price);

			 EnterToContinue();// enter to continue
			 return true;
		 }
	 }
	 cout << "Couldn't sell the potion." << endl;
	 return false;// if it failed
 }

 bool AlchemyWorkShop::UsePotion(string Potion_name)
 {
	 if (_Stock_M->RemovePotion(Potion_name))//if potion was successfully removed
	 {
		 PotionRecipe Potion = _Recipe_M->GetRecipeUsingName(Potion_name);

		 cout << "Player used the potion." << endl;
		 cout << Potion._effect << endl;// print out the potion effect
		 return true;
	 }

	 cout << "Player couldn't use the potion." << endl;
	 return false;// if it failed
 }

 void AlchemyWorkShop::EnterToContinue()
 {
	 PrintColorString(">> Enter to continue.", 8);
	 cin.get();
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
			 cout << "\nGood bye, and come again to " << _name << "." << endl;

			 Sleep(2000);// for giving time for saying good bye!
			 this->_is_staying=false;// to leave the store
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

 void AlchemyWorkShop::KABOOM()
 {
	 cout << "!!!!! BOOOOM !!!!!" << "\a";

	this-> ~AlchemyWorkShop();
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