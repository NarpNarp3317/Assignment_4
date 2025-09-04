#pragma once

#include <string>
//#include <iostream>
#include "Key_function.h"
#include <map>
#include <vector>
using namespace std;



void AskAndProceed(string command, map<const char, Str_Key_function > commandkeys);// use map with char as key and function pointer as values.

bool AskYes_or_No(string question, vector<char> chars_for_Yes, vector<char> chars_for_No);


//void Get_Full_line(istream& input, string& output);