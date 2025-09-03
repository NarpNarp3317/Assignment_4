#pragma once
#include <string>
using namespace std;

class PotionBottle// default will be the empty bottle of potion
{
public:
	PotionBottle(string name, string effect, int price);
	PotionBottle();//default bottle;

private:
	string _name;
	string _effect;// print out when it is used;
	int _price;

public:
	string GetName();
	void SetName(string name);
	string GetEffect();
	void SetEffect(string effect);

	int GetPrice();
	void SetPrice(int price);
	//void SetPrice(int newprice);// may be not needed? // maybe 

	void UsePotion();// use the potion and make it empty plask(default potion bottle)
};