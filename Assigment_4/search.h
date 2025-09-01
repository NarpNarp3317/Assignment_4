#pragma once
#include <vector>
#include <map>
#include <string>
#include "SearchResult.h"
#include "Enum_Key_Value.h"
#include <typeinfo>// to check the if selected template type name is string or not(cuz, it only works with string)
using namespace std;

// by not making a class, make a header and use the function. now i get how this works

SearchResult StringChecker(string keyword, string compared_string);

template<typename Key, typename Value>// template is required in cpp even though it was in header!
vector<SearchResult> SearchMap(string keyword, map<Key, Value> searchArea, Enum_Key_or_Value key_or_value);

vector<SearchResult> SearchVector(string keyword, vector<string> searchArea);