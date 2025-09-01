#pragma once
// to print out the list of items and its value in order
#include "SearchResult.h"
#include <map>
#include <vector>
#include <string>
//#include <type_traits>// to use is_same, <type_traits>is included// is_same<A,B>::value --> returns the bool
//#include <typeinfo>// to use typeid// nope, worng usage// turns out, stl isnt a "real" data type, so this wont work with vector
#include <iostream>
#include <Windows.h>// for console output 

using namespace std;

class ListPrinter
{
public:
	ListPrinter(int maxLength, HANDLE output_handle);

private:
	int _max_length;// this is the max length of one line of string, if it excede, move on to next line
	string _icon;// indicator icon that tells the start of the list (ex. >>salt(20/30)   or  * salt(20/30)

	HANDLE _output_handle;// for color change;

public:
	//void ConvertMapToPrintable(map<string, list);// get list (vector or map) and convert it for printout;

	void PrintIcon();

	void PrintOutList(map<string,int> list);// just print out map....// this need to be a template ... fuck

	void PrintOutSearchResults(vector<SearchResult> results);// print out the list with color highlight

	/*
	template<typename T>
	void ConvertToPrintable(const T list);
	*/

	~ListPrinter();
};

// template definition should be in header. not so sure why so, ask this for tutor later// for now, no template

/*
template<typename T>// definition of T needs to be done in compiling, not during runtime

inline void ListPrinter::ConvertToPrintable(T list)// what is inline and why is it added?
{
	if (typeid(T) == typeid(vector<string>))
	{
		ConvertVector(list);
	}
	else if (typeid(T) == typeid(map<string, SearchResult>))
	{
		ConvertMap(list);
	}
	else
	{
		cout << "Error, Invalid list." << endl;
	}
*/
	/*
	if (is_same<T,vector<string>>::value)
	{

	}
	else if (is_same<T, map<string, SearchResult>>::value)
	{

	}
	else
	{
		cout << "Error, Invalid list." << endl;
	}
	*/
