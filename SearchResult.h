#pragma once
#include <vector>
#include <string>

struct SearchResult
{
	std::string name;// name
	std::vector<int> indicator;// record of start and end of the text change color index
};