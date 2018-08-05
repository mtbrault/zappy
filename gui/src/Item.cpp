/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item class 
*/

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "Item.hpp"

Item::Item(float x, float y, int id, int type)
	:_x(x), _y(y), _id(id), _alive(false)
{
	_getModel[FOOD] = "./media/French Fries/TopL.obj";
	_getTexture[FOOD] = "./media/French Fries/GrPotato.png";
	_getScale[FOOD] = 0.2f;
	_getModel[LINEMATE] = "./media/Hamburger/TopL.obj";
	_getTexture[LINEMATE] = "./media/Hamburger/ItFoodHamburger_tex03.png";
	_getScale[LINEMATE] = 0.2f;
	_getModel[DERAUMERE] = "./media/Cupcake/TopL.obj";
	_getTexture[DERAUMERE] = "./media/Cupcake/FoodCake.png";
	_getScale[DERAUMERE] = 0.2f;
	_getModel[SIBUR] = "./media/Juice/TopL.obj";
	_getTexture[SIBUR] = "./media/Juice/ItFoodJuice.png";
	_getScale[SIBUR] = 0.2f;
	_getModel[MENDIANE] = "./media/Ice Cream/TopL.obj";
	_getTexture[MENDIANE] = "./media/Ice Cream/ItFoodIce02.png";
	_getScale[MENDIANE] = 0.2f;
	_getModel[PHIRAS] = "./media/Hotdog/TopL.obj";
	_getTexture[PHIRAS] = "./media/Hotdog/FoodHotDogLight.png";
	_getScale[PHIRAS] = 0.2f;
	_getModel[THYSTAME] = "./media/Pizza/TopL.obj";
	_getTexture[THYSTAME] = "./media/Pizza/ItFoodPizzatex13.png";
	_getScale[THYSTAME] = 0.2f;
	_bonusType = static_cast<eItem>(type);
	_id = id;
}

Item::~Item()
{
}

eItem Item::getItemType() const
{
	return (_bonusType);
}

std::string		Item::getModel()
{
	return _getModel[_bonusType];
}

std::string		Item::getTexture()
{
	return _getTexture[_bonusType];
}

float	Item::getScale()
{
	return _getScale[_bonusType];
}
