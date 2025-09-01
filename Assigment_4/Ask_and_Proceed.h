#pragma once

#include <string>
#include <iostream>
#include "Key_function.h"
#include <map>
using namespace std;



void AskAndProceed(string command, map<const char, Str_Key_function > commandkeys)// use map with char as key and function pointer as values.
{
	bool isrunning = true;
	char typedkey;

	while (isrunning)
	{
		cout << command;

		cin >> typedkey;

		map<const char, Str_Key_function >::iterator it = commandkeys.find(typedkey);

		if (it == commandkeys.end())
		{
			cout<<"Error, Invalid input detected." << endl;
		}
		else
		{
			it->second.function();// now key_function is using <functional>
			isrunning = false;
			//it->second.functionPtr();// second(value)==keyfunction{name, functionptr}. get functionptr// get function ptrcall the current function by adding()
		}
	}
}