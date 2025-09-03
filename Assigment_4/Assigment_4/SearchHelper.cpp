#include "SearchHelper.h"
#include <typeinfo>// to check the if selected template type name is string or not(cuz, it only works with string)


SearchHelper::SearchHelper()
{
	this->_was_search_successful = false;// if no search was done, false... i guess// only to check if the result was successful or not
}



/*
SearchResult SearchHelper::StringChecker(string keyword, string compared_string)
{
	SearchResult result = { "",{}};//make empty result

	int start_index;// to store the starting index of keyword in compared string
	bool buildingStarted = false;
	int key_i = 0;
	char endof_key = keyword[keyword.length() - 1];
	bool is_keyword_in = false;//bool if the keyword is in compared string

	for (int i = 0; i < compared_string.length(); i++)
	{
		if (compared_string.length() - i < keyword.length())// if lenght is not enough
		{
			break;
		}
		char c = compared_string[i];

		if (c != keyword[key_i])
		{
			if(buildingStarted)
			{
				buildingStarted = false;
				key_i = 0;
			}
		}
		else
		{
			if (c == keyword[0])
			{
				buildingStarted = true;
				start_index = i;//only record the start of key char
			}

			if (c == endof_key)
			{
				is_keyword_in = true;
				result.indicator.push_back(start_index);//put start indicator fisrt!
				result.indicator.push_back(i);// put end indicator later
				// if the keyword is single char like "a", there would be 2 indexes with same value. this will be considered in printout function
																									// if next index shares same indicator int, only change the color
				key_i = 0;
			}
			else// if the job is not done yet
			{
				++key_i;//for next char of keyword
			}
		}
	}
	// end of the loop

	return  result;
}
*/
// version 1.2
// Problems
//1. when keyword start and end shared same char and repeats while overlapping --->"anana" if the key is "ana" full textcolor needs to be changed but nope.
//   ---> make exception for first and last? but what if (word==aannaannaannaann, key= aannaa

SearchResult SearchHelper::StringChecker(string keyword, string compared_string)
{
	SearchResult result = { "",{} };

	if (keyword.length() == 0 || compared_string.length() == 0) return result;//if there are nothing, return nothing;

	//for (int i = 0; i < compared_string.length() - keyword.length(); i++)//if lenght is not enough, why bother
	for (int i = 0; i <= compared_string.length() - keyword.length(); i++)//abcabc, key=abc--> i=0;i<3 (nope) i=0;i<=3 (yep)
	{
		bool nobreak = true;
		int loopcount = 0;

		for (int j = 0; j < keyword.length(); j++)
		{
			if (compared_string[i+j] != keyword[j])
			{
				nobreak = false;
				break;
			}
			++loopcount;//count the loop

		}// end of the loop // checking is done;

		if (nobreak)
		{
			result.name = compared_string;
			result.indicator.push_back(i);// start index
			result.indicator.push_back(i + keyword.length() - 1);//end index
		}

		i += loopcount;// to skip the checked chars of compared_string 
		// this is preventing overlapping case. if it doesnt increment, then it will do unnecessary loop
		// could detect the overlapping pattern and subtract the loopcount with size of pattern size
		// or start keyword checking at the end of the pattern
		// fuck
	}
	// end of full check

	return result;
}
// version 2 (2dvector approach?)

/*
SearchResult SearchHelper::StringChecker(string keyword, string compared_string)
{
	SearchResult result = { "",{} };

	if (keyword.length() == 0 || compared_string.length() == 0) return result;//if there are nothing, return nothing;

	bool isoverlappable=false;
	int overlapsize=0;
	//check if keyword is overlappable ("aabcaa" "abca", "aaa")
	if (keyword[0] == keyword[keyword.length() - 1])// when first and last char is same, it could be overlaped//--> not really. (key==aabaab,word aabaabaab)// if chunk of text repeats in the end, it 
	{
		isoverlappable = true;
		//check how many chars can be overlapped(ex. aaabaaa--> 3 , abaaa-->1, aabaaaa->2) or (ababaCababa ---> 5 ababa)
		// it can overlap if 1. sequence of same chars (aaaaaa), 2, 



	}
	// if it doesnt, just move on.




	//for (int i = 0; i < compared_string.length() - keyword.length(); i++)//if lenght is not enough, why bother
	for (int i = 0; i <= compared_string.length() - keyword.length(); i++)//abcabc, key=abc--> i=0;i<3 (nope) i=0;i<=3 (yep)
	{
		bool nobreak = true;
		int loopcount = 0;

		for (int j = 0; j < keyword.length(); j++)
		{
			if (compared_string[i + j] != keyword[j])
			{
				nobreak = false;
				break;
			}
			++loopcount;//count the loop

		}// end of the loop // checking is done;

		if (nobreak)
		{
			result.name = compared_string;
			result.indicator.push_back(i);// start index
			result.indicator.push_back(i + keyword.length() - 1);//end index
		}

		i += (loopcount-overlapsize);// to skip the checked chars of compared_string
	}
	// end of full check

	return result;
}
*/
// version 2.2 (+ overlapping condition)

/*
SearchResult SearchHelper::StringChecker(string keyword, string compared_string)
{
	SearchResult result = { "",{}};
	size_t pos = compared_string.find(keyword);// turns out, string has find function.... fuck
	while (pos != std::string::npos)
	{
		result.indicator.push_back(pos);
		result.indicator.push_back(pos + keyword.length() - 1);
		pos = compared_string.find(keyword, pos + 1);
	}

	return result;
}
*/
//chat gpt version .... fuck

/*
bool SearchHelper::StringChecker(string keyword, string compared_string)
{
	//if the key word is abc, the searchable words are abc, xabc, xabcxx, xabcabc, xabcxabc, xabcababx, 
	// what cannot be searched --> xx, ab, xab, xabxc,

	// the rule-->1. a,b,c needs to be neighbors, 2. all a,b,c need to be included, 3. 

	// build a word if starting char a is detected
	// if the keyword building is succesfully done in loop, the compared string is searchable!
	// this wont detect more than one abc cause if the word is detected, it will return true immediately, it wont work in case like chaning the color of shared text
																										// --> but this is only for checking true or false, this is enough i guess?
	
	
	if (keyword.length() > compared_string.length())// if the keyword is bigger than the compared stirng, dont even start the loop cause it would be the waste of the loop
	{
		return false;// dont bother looping, this cant be true;
	}
	// if the compared word is capable of containing the keyword


	//bool isfirst = false;//did keyword[0] 'a' detected? // if it get detected, next should be keyword[1] 'b'.....it goes on 
		// checking is it first wont be needed

	bool buildingStarted = false;
	int index_key = 0;
	//char key_c = keyword[index_key];
	char endof_key = keyword[keyword.length() - 1];// the last char of the compared string

	//bool iskeyword_built=false;//was building successfully done? // checking if the key word building is done or not would be done by checking if c==endof_key
	
	for (int i = 0; i < compared_string.length(); i++)
	{
		char c = compared_string[i];// current char of compared word

		if (c == keyword[index_key])// if keyword char is detected
		{
			if (c == keyword[0])// if first keyword char is detected, 
			{
				buildingStarted = true;
			}

			if (c == endof_key)// if the current c is the end of the keyword(if keyword is successfully built)
			{
				//check is it possible to build a keword from current coord of string
				return true;// the building is done!, the compared string is containing the keyword
			}
			else // if the keyword is not fully built yet
			{
				++index_key;// increment the index, so that next key_c can be set
				//key_c = keyword[index_key];// set the next key_c to be the rightside neighbor
			}
		}
		else// if the current c is not keyword c
		{
			if (buildingStarted)// turn off if it was on
			{
				buildingStarted = false;
			}


		}
	}// the end of the loop
	// if the loop finied and couln't finish building keyword, this means the compared string does not have keyword
	return false;
}
*/
// version 1


template<typename Key, typename Value>// template is required in cpp even though it was in header!
vector<SearchResult> SearchHelper::SearchMap(string keyword, map<Key, Value> searchArea, Enum_Key_or_Value key_or_value)
//-> should it return map? printing out only one?
{	
	vector<SearchResult> searchResults = {};//empty result
	/*
	if (keyorvalue == key)
	{
		if (typeid(Key) != typeid(string))
		{
			cout << "Error, this only works with string." << endl;
			return searchResults;
		}
	}
	else
	{
		if (typeid(Value) != typeid(string))
		{
			cout << "Error, this only works with string." << endl;
			return searchResults;
		}
	}
	*/ // maybe stop the search if the type is not string?

	for (pair<const Key, Value>& pair : searchArea)// fuck yeah, now i get it
	{
		// string checker only works if key or value is string// well...fix it later

		SearchResult result;// make storage

		if (key_or_value == key) result = StringChecker(keyword, pair.first);
		else result = StringChecker(keyword, pair.second);

		if (result.name != "")//if the name of the result is not empty("")//--> this means search was successful
		{
			searchResults.push_back(result);
		}
		//else, do nothing
		/*
		if (keyorvalue == key)// if searching for key(serching for key with same string)
		{
			SearchResult result = StringChecker(keyword, pair.first);// store it on result

			if (result.name != "")//if the name of the result is not empty("")//--> this means search was successful
			{
				searchResults.push_back(result);
			}
			//else, do nothing
		}
		else// if searching for value// searching for value
		{
			SearchResult result = StringChecker(keyword, pair.second);//same here

			if (result.name != "")
			{
				searchResults.push_back(result);
			}
			//else, do nothing
		}
		*/
	}// the loop is done

	return searchResults;
}

vector<SearchResult> SearchHelper::SearchVector(string keyword,vector<string> searchArea)
{
	vector<SearchResult> searchResults = {};

	for (string compared_string : searchArea)
	{
		SearchResult result = StringChecker(keyword, compared_string);
		if (!result.name.empty())//if name is searched// empty() can be used!!!! fuck yeah
		{
			searchResults.push_back(result);
		}
	}//end of the loop
	return searchResults;
}
