#pragma once
#include <string>
#include <functional>// to handle function like varialbe

struct Str_Key_function
{
	std::string function_name;

	std::function<void()> function;
	// make a function which returns (void) and gets () as argument
};

/*
struct Str_Key_function
{
	std::string function_name;
	//void(*)() functionPtr;
	void(*functionPtr)();// for the syntax of function pointer, the carrier must be insied of the (*) not like the other data types
};
*/