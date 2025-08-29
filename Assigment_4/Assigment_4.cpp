#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AlchemyWrokShop.h"
#include "IngredientDetector.h"

using namespace std;

void PrintMap(const map<string, int>& m)
{
    if (m.empty()) {
        cout << "Map is empty." << endl;
        return;
    }

    cout << "Map contents:" << endl;
    for (const auto& pair : m)
    {
        cout << pair.first << " : " << pair.second << endl;
    }
}


int main(void)
{
    // string to map conversion test
    /*
    IngredientDetector typedetection;
    string list = "1*salt, 2*red pepper, butter, 2*butter,            23* fucking purple    potato";

    typedetection.MakeIngredientList(list);

    PrintMap(typedetection.GetSortedIngredients());
    */
    

    return 0;
}
