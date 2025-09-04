#include "search.h"

SearchResult StringChecker(const string& keyword, const string& compared_string)
{
	SearchResult result = { "",{} };

	if (keyword.length() == 0 || compared_string.length() == 0) return result;//if there are nothing, return nothing;
	if (keyword.length() > compared_string.length() == 0) return result;// if keyword is bigger than comparing word

	//for (int i = 0; i < compared_string.length() - keyword.length(); i++)//if lenght is not enough, why bother
	for (int i = 0; i <= compared_string.length() - keyword.length(); i++)//abcabc, key=abc--> i=0;i<3 (nope) i=0;i<=3 (yep)
	{
		bool nobreak = true;
		int loopcount = 0;// to allow overlapping highlight, no skipping

		for (int j = 0; j < keyword.length(); j++)
		{
			if (compared_string[i + j] != keyword[j])
			{
				nobreak = false;
				break;
			}
			++loopcount;//count the loop

		//	ana anana
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
// version 2 (2dvector approach?)// this one does not work with overlapping hihglight case











template<typename Key, typename Value>// template is required in cpp even though it was in header!
vector<SearchResult> SearchMap(string keyword, map<Key, Value> searchArea, Enum_Key_or_Value key_or_value)
//-> should it return map? printing out only one?
{
	vector<SearchResult> searchResults = {};//empty result

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

	}// the loop is done

	return searchResults;
}

vector<SearchResult> SearchVector(string keyword, vector<string> searchArea)
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
