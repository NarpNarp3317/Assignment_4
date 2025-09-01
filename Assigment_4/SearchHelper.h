#pragma once
#include <vector>
#include <map>
#include <string>
#include "SearchResult.h"
#include "Enum_Key_Value.h"

using namespace std;

class SearchHelper
{
public:
	SearchHelper();
	
private:
	bool _was_search_successful;// to indicate the search result outside of the class, without individually checking the result;

public:


	SearchResult StringChecker(string keyword, string compared_string);// check if the key word is included in a comparing word


	
	template<typename Key,typename Value>// use template to make it work in wide range of datatypes
	vector<SearchResult> SearchMap(string keyword, map<Key, Value> searchArea, Enum_Key_or_Value key_or_value);// search item through map// i mean, key or value can be done with bool but.. this seems nicer
	//returns the vector of search result of key or value
	
	vector<SearchResult> SearchVector(string keyword, vector<string> searchArea);// search item through vector
	
	// maybe later, but for now, only string searching is needed

};