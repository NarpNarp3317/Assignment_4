#include "IngredientDetector.h"
#include <iostream>

using namespace std;

IngredientDetector::IngredientDetector()
{
	_writen_Lists = "";// default
	_endl_signal=',';
	_count_signal='*';
}

bool IngredientDetector::MakeIngredientList(string writen_ingredients)
{
	//storage for name and count
	string rebuilt_count="";
	string rebuilt_name="";
	
	bool isCounterFounded=false;// for the case of (salt==1*salt)
	bool isDetectingName=false;// for loop; when the loop is for count, if text is detected, then it would be considerd invalid //expects number for the first contact
	int i = 0;//loop starting
	// invalid checker //(ex. 1 2*pebbles (x) 12*pebbles (o), 12312*Pebbles(x)//exceding limit)
	bool isvalid = true;
	
	//for (char c : writen_ingredients)
	//for(i; i< writen_ingredients.length(); i++)// this is used so that looping can be paused and restarted
	/*
	while(i<writen_ingredients.length())
	{
		//char c = writen_ingredients[i];//char of current index of string// it does not work on individual while loop fuck;

		if (!(DetectText(c) || DetectNumber(c) || DetectSignal(c)))// if the conditons are false(!)
		{
			isvalid = false;// invalid char detected break the loop
			break;
		}
		else// when it is valid
		{
			while (i < writen_ingredients.length() == true)// the while loop only compare when the order reahces the end and turn back.
				// --> even inside the while loop, the conditon must be checked
			{
				if (DetectNumber(c) == true)
				{
					rebuilt_count += c;
					i++;
				}
				else break;// number detection over
			}
			// detected other than number

			if (i < writen_ingredients.length() && c == _count_signal)
			{
				i++;
			}// number is made and 
			else if (rebuilt_count != "")// if number is valid but * was found
			{
				isvalid = false;
				break;
			}

			//------- build name ------//
			while (i < writen_ingredients.length())
			{
				if (DetectText(c) == true)
				{

				}
			}
			if()




			
			







			//before anything, convert uppercase to lowercase for future sorting
			if (c >= 'A' && c <= 'Z')
			{
				c = c - ('A' - 'a');//subtract the gap amount of uppercase and lowercase  to convert uppercase to lowercase;
			}

			if (DetectNumber(c) && !isName)//if it is detected number while detecting number(not name)
			{
				rebuilt_count += c;
			}

			else if ((c == _count_signal) && !isName)// if current char is count signal while it is detecting name
			{
				isName = true;//switch to the name detecting mode
			}
		
			else if (DetectText(c) && isName)// if current char is text while it was chekcing name;
			{
				rebuilt_name += c;//build name with c
			}
			else if (c == _endl_signal)
			{
				
			}


		}


	}
	// loop is done or paused

	if (!isvalid)//if it is not valid!// doesnt really require != true or something
	{
		cout << "Error, Invalid input, Plz try agin." << endl;
		_sorted_ingredients.clear();// invalid detected, cleanup the prior update;
		return;
	}
	else
	{
		int ingredient_count;

	}
	
	*/

	vector<int> ingredient_Counts;
	vector<string> ingredient_Names;

	for (i; i < writen_ingredients.length(); i++)
	{
		char c = writen_ingredients[i];//current char

		if (!(DetectNumber(c) || DetectSignal(c) || DetectText(c)))// if all conditions are false (!)
		{
			isvalid=false;
			break;
		}

		if (c >= 'A' && c <= 'Z')// convert upper case to lowercase for future sort
		{
			c = c - ('A' - 'a');
		}

		if (DetectNumber(c) && !isDetectingName)// if current c is number and wasnt detecting name(== was detecting number)
		{
			rebuilt_count += c;
		}
		else if (c == _count_signal && !isDetectingName)// if c is '*' and was counting for number;
		{
			isCounterFounded = true;//set it to true cause... it is true
			isDetectingName = true;// switch to name detection mode
		}
		else if (DetectText(c))// if c is text
		{
			if (!isCounterFounded && rebuilt_count == "")//if the counter was no counter signal and no number was inputed
			{
				rebuilt_name += c;// continue on the making names!!! the number will be default 1;
			}
			else if (isCounterFounded && rebuilt_count != "")// if the counter and number is valid! all good!
			{
				rebuilt_name += c;
			}
			else//this conditons will be considerd as error
			{
				isvalid = false;
				break;
			}

			
		}
		else if (c == _endl_signal)// the end signal is detected. put it on a temp vectors
		{
			if (rebuilt_name != "")// if name building was successful
			{
				int count = ConvertStringToInt(rebuilt_count);

				/*

				if (rebuilt_count == "")// if there were no number detected
				{
					count = 1;// ex. 1*Salt == Salt
				}
				else
				{
					for (char digit : rebuilt_count)// convert string to number using for each loop!!!
					{

					}
				}
				*/
				// building count and name finished. now put it one a temp vectors
				
				if (count == -100)// the error number
				{
					isvalid = false;
					break;
				}

				ingredient_Counts.push_back(count);
				// before putting name on vector, trim the possible " " on front and back of the string (ex."   pepper "-->"pepper"

				ingredient_Names.push_back(NameTrimmer(rebuilt_name));//pushback trimed name

			}
			// putting on temp vetor done, now reset for next text

			rebuilt_count = "";
			rebuilt_name = "";
			isDetectingName = false;// dont forget this!!!!! fuck
			isCounterFounded = false;// and this too
		}
	}
	// the loop ended. if it was optimal, the last name and number would have been created but couldnt put it on vectors
	// therefore, put them in vectors!!!!!


	if (rebuilt_name != "")// if name building was successful in the end
	{
		int count = ConvertStringToInt(rebuilt_count);
		if (count == -100)// the error number
		{
			isvalid = false;// do the same thing
		}
		else
		{
			ingredient_Counts.push_back(count);
			ingredient_Names.push_back(NameTrimmer(rebuilt_name));//pushback trimed name
		}
	}

	if (!isvalid)// if hole conditions were ignored and was invalid
	{
		return false;
	}

	_sorted_ingredients.clear();// clean for the guest!
	for (int i = 0; i < ingredient_Names.size(); i++)
	{
		_sorted_ingredients[ingredient_Names[i]] += ingredient_Counts[i];// use ingredient name as key to calculate the value.
		//WARNING : however, using value to get key is not possible with map(well, could do it manually using iterator but, not in a same way as using key to get value)
	}
}

bool IngredientDetector::CompareIngredientLists(map<string, int> A, map<string, int> B)
{
	/*
	if (A.size() != B.size())// check if the size is different
	{
		return false;
	}
	//well.... map is not same as vector. this wont work
	// if the size is same, do the loop. item count is same so using lenght of A wont be a problem
	for(int i=0;i<A.size();i++)
	{
		if (A.begin() + i != B.begin() + i) return false;
	}
	return true;
	*/
	// turns out, map can be simply comparable like this
	return A == B;
}


int IngredientDetector::ConvertStringToInt(string int_string)
{
	int number=0;
	if (int_string.length() == 0) return 1;// if there is no string detected, return 1// when no number was detected, it is considered as default 1
																							// -> ex. 1*salt==salt
	for (int i = 0; i < int_string.length(); i++)
	{
		if (!DetectNumber(int_string[i]))// check if the char is number or not!!!! fuck
		{
			cout<<"Error, Non Numeric Text Detected in String to Int Converter!"<<endl;
			return -100;// error, return -100 bring chaos to the world
		}
		number = number*10+ (int_string[i]-'0');
	}
	return number;
}

string IngredientDetector::NameTrimmer(string name)// trim out front and back ' '
{
	bool islasttext = false;// save the bool and use it for cheking if the last c was text or ' '
	string newName="";
	vector<string> chunks;// temp storage of chunk of text for later

	for (int i = 0; i < name.length();i++)//loop till the char is not ' '
	{
		char c = name[i];
		if (c != ' ')
		{
			newName += c;
			islasttext = true;
		}
		else
		{
			if (islasttext)// if current c is ' ' and last c wast text --> end of the chunk
							// this causes the Error!!! --> if there is no ' ' inthe end of the name like"  salt", this wont be added into vector
			{
				chunks.push_back(newName);
				newName = "";//reset the namestorage;
				islasttext = false;
			}
		}
	}// the loop ends
	// for the case of there were no ' ' for last c;
	if (islasttext)
	{
		chunks.push_back(newName);
		newName = "";//reset the namestorage;
		islasttext = false;
	}

	cout << "the size of chunks vector is = " << chunks.size() << endl;

	newName = chunks[0];
	
	for (int i = 1; i < chunks.size(); i++)
	{
		newName = newName +(" " + chunks[i]);
	}
	// all is done!!! fuck yeah
	return newName;
	
}



map<string, int> IngredientDetector::GetSortedIngredients()
{
	return _sorted_ingredients;
}

bool IngredientDetector::DetectText(char current_char)
{
	if (current_char >= 'A' && current_char <= 'Z' || current_char >= 'a' && current_char <= 'z' || current_char == ' ' || current_char == '_') return true;
	else return false;
}

bool IngredientDetector::DetectNumber(char current_char)
{
	if ((current_char >= '0' && current_char <= '9')) return true;
	else return false;
}

bool IngredientDetector::DetectSignal(char current_char)
{
	if (current_char == _endl_signal || current_char == _count_signal) return true;
	else return false;
}
