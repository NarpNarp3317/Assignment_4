#include "ListPrinter.h"


ListPrinter::ListPrinter(int maxLength, HANDLE output_handle, int highlight_color)
{
	this->_max_length = maxLength;
	this->_icon = ">>";
	this->_output_handle = output_handle;
	this->_highlight_color = highlight_color;
	this->_icon_color = 8;//dark grey
}


void ListPrinter::PrintIcon()
{
	SetConsoleTextAttribute(_output_handle, _icon_color);//set color to red;
	cout << _icon;
	SetConsoleTextAttribute(_output_handle, 7);// return to default color
}

void ListPrinter::PrintOutMapList(const map<string, int>& list, Enum_PrintoutDirection direction)// just print out the list
{
	int total_lenght_of_current_line = 0;


	if (list.empty())
	{
		SetConsoleTextAttribute(_output_handle, 12);// red for error?
		cout << "No result has been found" << endl;
		SetConsoleTextAttribute(_output_handle, 7);// default 7
		return;
	}


	for (const pair<string, int>& pair : list)
	{
		/*
		if (total_lenght_of_current_line > _max_length)
		{
			cout << endl;//double check// this is for after first loop is done
			total_lenght_of_current_line = 0;
		}
		*/
		PrintIcon();//>>
		cout << " " << pair.first << " x";

		if (pair.second == 0)
		{
			SetConsoleTextAttribute(_output_handle, 12);// if ingredient count is 0, alert by printing out red
			cout << pair.second;
			SetConsoleTextAttribute(_output_handle, 7);// defualt white
		}
		else
		{
			cout << pair.second;
		}
		// end of printing out one pair of list

		total_lenght_of_current_line += (4 + pair.first.length() + to_string(pair.second).length());// get the length of used line spaces


		if (direction == vertical)
		{
			cout << endl;// change line
		}
		else if (direction == horizontal)
		{
			if (total_lenght_of_current_line > _max_length)
			{
				cout << endl;// change line
				total_lenght_of_current_line = 0;// reset for next
			}

			else cout << "   ";// add spacing
		}
		else
		{
			cout << "Error, invalid enum detected in PrintOutSearchResults" << endl;
		}
	
	}
}

void ListPrinter::PrintOutVectorList(const vector<string> list, Enum_PrintoutDirection direction)// do the same but for vector
{
	int total_lenght_of_current_line = 0;


	if (list.empty())
	{
		SetConsoleTextAttribute(_output_handle, 12);// red for error?
		cout << "No result has been found" << endl;
		SetConsoleTextAttribute(_output_handle, 7);// default 7
		return;
	}


	for (const string& converted_string : list)
	{

		PrintIcon();//>>

		cout << converted_string;

		total_lenght_of_current_line += converted_string.length();//increment the vector


		if (direction == vertical)
		{
			cout << endl;// change line
		}
		else if (direction == horizontal)
		{
			if (total_lenght_of_current_line > _max_length)
			{
				cout << endl;// change line
				total_lenght_of_current_line = 0;// reset for next
			}

			else cout << "   ";// add spacing
		}
		else
		{
			cout << "Error, invalid enum detected in PrintOutSearchResults" << endl;
		}

	}
}

void ListPrinter::PrintOutSearchResults(const vector<SearchResult>& results, Enum_PrintoutDirection direction)// if horizontal-> as usual // vertical-> print 1->endl->2->enld...
{
	int total_lenght_of_current_line=0;// fuck, this is long// if this exceed the max length of horizontal layout, change the line
	int result_length;// total legnth of result string
	int last_char_index;//to print the rest of the string after highlight
	int start;//indicator start
	int end;// indicator end

	//bool searched = false;// to check if search was successful or not// or just check the result first
	// like this! how easy it is! fuck

	if (results.empty())
	{
		SetConsoleTextAttribute(_output_handle, 12);// red for error?
		cout << "No matching result." << endl;
		SetConsoleTextAttribute(_output_handle, 7);// default 7
		return;// sayonara--> leave function
	}

	for (const SearchResult& result : results)
	{
		last_char_index = 0;// starts from 0
		result_length = (result.name).length();
		total_lenght_of_current_line += result_length;
		if (total_lenght_of_current_line > _max_length)
		{
			cout << endl;//double check// this is for after first loop is done
			total_lenght_of_current_line = 0;
		}

		PrintIcon();// >>
		//for(int i=0; i< result.indicator.size();i++)
		for (int i = 0; i +1< result.indicator.size(); i += 2)// start and end-> increment by 2
		{
			start = result.indicator[i];
			end = result.indicator[i + 1];
			//print out normal un_highlighted string first

			//if (start == end)// the case when highlighted area is only one char ex. keyword a, "a"bc // turns out, it wont make exception cause the resetting wold happen before printint next string
		
			if (start > last_char_index)// if keyword is not infront of the result string
			{
				for (int j = last_char_index; j < start; j++)
				{
					cout << result.name[j];
				}
			}
			// after printing out the un_highlighted string

			SetConsoleTextAttribute(_output_handle, _highlight_color);
			//for (int k = start; k <= end; k++)// j needs to be reused// i for result loop, j for printing chars
			for (int j = start; j <= end; j++)
			{
				cout << result.name[j];
			}
			SetConsoleTextAttribute(_output_handle, 7);// default 7

			last_char_index = end + 1;// not last_char_index =end, it should be start of the next string, so, last_char_index =end+1
		}// end of indicator
		//print rest of the string
		if (last_char_index < result_length)//if there is chars not printed out yet
		{
			for (int j = last_char_index; j < result_length; j++)
			{
				cout << result.name[j];
			}
		}

		// end of printing out the results with highlights

		if (direction == vertical)
		{
			cout << endl;// change line
		}
		else if (direction == horizontal)
		{
			if (total_lenght_of_current_line > _max_length)
			{
				cout << endl;// change line
				total_lenght_of_current_line = 0;// reset for next
			}

			else cout << "   ";// add spacing
		}
		else
		{
			cout << "Error, invalid enum detected in PrintOutSearchResults" << endl;// for debug
		}
	}// end of printing all of the result, the real end!!! fuck yeah
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