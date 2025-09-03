#include "PotionBottle.h"


PotionBottle::PotionBottle(string name, string effect, int price)
{
	_name = name;
	_effect = effect;
	_price = price;
}

PotionBottle::PotionBottle()
{
	_name = "Empty Bottle";
	_effect = "It did nothing";
	_price = 0;
}

string PotionBottle::GetName()
{
	return _name;
}

void PotionBottle::SetName(string name)
{
	_name = name;
}

string PotionBottle::GetEffect()
{
	return _effect;
}

void PotionBottle::SetEffect(string effect)
{
	_effect = effect;
}

int PotionBottle::GetPrice()
{
	return _price;
}

void PotionBottle::SetPrice(int price)
{
	_price = price;
}

void PotionBottle::UsePotion()// basically making it into default empty bottle
{
	_name = "Empty Bottle";
	_effect = "It did nothing";
	_price = 0;
}

/*
void PotionBottle::SetPrice(int newprice)
{
	_price = newprice;
}
*/
