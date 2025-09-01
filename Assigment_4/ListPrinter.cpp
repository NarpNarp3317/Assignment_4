#include "ListPrinter.h"


ListPrinter::ListPrinter(int maxLength, HANDLE output_handle)
{
	this->_max_length = maxLength;
	this->_icon = ">>";
	this->_output_handle = output_handle;
}


void ListPrinter::PrintIcon()
{
	SetConsoleTextAttribute(_output_handle, 12);//set color to red;
	cout << _icon;
	SetConsoleTextAttribute(_output_handle, 7);// return to default color
}

void ListPrinter::PrintOutList(map<string, int> list)
{
}

void ListPrinter::PrintOutSearchResults(vector<SearchResult> results)
{
}

ListPrinter::~ListPrinter()// good bye
{
}


/*
void ListPrinter::ConvertMap(map<string, SearchResult>)
{
}

void ListPrinter::ConvertVector(vector<string>)
{
}
*/