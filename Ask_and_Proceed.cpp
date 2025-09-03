#include "Ask_and_Proceed.h"
#include <iostream>


void AskAndProceed(string command, map<const char, Str_Key_function > commandkeys)// use map with char as key and function pointer as values.
{
	char typedkey;

	while (true)
	{
		cout << command;
		//cin.ignore(99999, '\n');
		cin >> typedkey;

		map<const char, Str_Key_function >::iterator it = commandkeys.find(typedkey);

		if (it == commandkeys.end())
		{
			cout << "Error, Invalid input detected." << endl;
		}
		else
		{
			it->second.function();// now key_function is using <functional>
			return;
			//it->second.functionPtr();// second(value)==keyfunction{name, functionptr}. get functionptr// get function ptrcall the current function by adding()
		}
	}
}

bool AskYes_or_No(string question, vector<char> chars_for_Yes, vector<char> chars_for_No)
{
	char typedkey;

	while (true)
	{
		cout << question;
		//cin.ignore(99999, '\n');
		cin >> typedkey;

		if (find(chars_for_Yes.begin(), chars_for_Yes.end(), typedkey) != chars_for_Yes.end())// if typedkey is found in yes vector
		{
			return true;
		}
		else if (find(chars_for_No.begin(), chars_for_No.end(), typedkey) != chars_for_No.end())// if typedkey is found in yes vector
		{
			return false;
		}
		else
		{
			cout << "Invalid input detected. Plz try again." << endl;
		}
	}
}