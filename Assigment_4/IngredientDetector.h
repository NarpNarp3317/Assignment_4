#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class IngredientDetector
{
public:
	IngredientDetector();

private:
	
//===== data members =====//
	string _writen_Lists;// recieved string of ingredients
	map<string, int> _sorted_ingredients;// key == ingredient name, value ==ingredient count// return this as result
	char _endl_signal;//
	char _count_signal;

//=== member functions ====//
public:

	bool MakeIngredientList(string writen_ingredients);// return bool, if making was unsuccessful, return false, if it works, return true;

	bool CompareIngredientLists(map<string, int> A, map<string, int> B);// compare list A and B to check if they are same;

	map<string,int> GetSortedIngredients();

	int ConvertStringToInt(string int_string);
	string NameTrimmer(string name);// this will trim out the unnecessary " "s and return trimed name

	bool DetectText(char current_char);

	bool DetectNumber(char current_char) ;

	bool DetectSignal(char current_char);

	~IngredientDetector();

};