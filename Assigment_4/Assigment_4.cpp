#include "AlchemyWrokShop.h"
#include "IngredientDetector.h"
#include "Windows.h"
#include "ListPrinter.h"


using namespace std;

void PrintMap2(map< string, int>& map)
{
    if (map.empty())
    {
        cout << "Map is empty." << endl;
        return;
    }

    cout << "Map contents:" << endl;
   // for ( pair<string,int>& pair : map)
    for ( auto & pair : map)
    {
        cout << pair.second << "* " << pair.first << ", ";
    }
    printf("\n");
}

void PrintMap(map< string, int> Map)
{
    if (Map.empty())
    {
        cout << "Map is empty." << endl;
        return;
    }

    cout << "Map contents:" << endl;
   for(map<string,int>::iterator it= Map.begin(); it != Map.end(); it++)
        //for ( const auto & pair : map)
    {
        cout << it->second << "* " << it->first << ", ";
    }
    printf("\n");
}



int main(void)
{
    // string to map conversion test
    
    IngredientDetector typedetection;

    
    string list;
    //cin >> list;this stops reading string after ' '
    // to read all of the string with ' ', use std::getline(std::cin, list);

    //getline(cin, list);

    list = "salt, 2*red pepper, butter, 2*butter,            23* fucking purple    potato";

    typedetection.MakeIngredientList(list);// convert string to map list

    auto SortedIngredients = typedetection.GetSortedIngredients();

    PrintMap2(SortedIngredients);
    
    
    /*
    string shop_name;
    cout << "Type the name of the AlchemyWorkShop: ";
    getline(cin, shop_name);

    AlchemyWorkShop* WorkShop = new  AlchemyWorkShop(shop_name);

    cout << "Welcome to the " << WorkShop->GetWorkShopName() << "!" << endl;

    WorkShop->GetCommand();

    */

    return 0;
}
