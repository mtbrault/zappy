/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** converter
*/

#include "Converter.hpp"

std::string Converter::convert(subTakeObject &toConvert) const
{
	switch (toConvert) {
	case subTakeObject::LOOK :
		return "LOOK";
	case subTakeObject::WAIT_LOOK :
		return "WAIT_LOOK";
	case subTakeObject::GET_INVENTORY :
		return "GET_INVENTORY";
	case subTakeObject::WAIT_INVENTORY :
		return "WAIT_INVENTORY";
	case subTakeObject::WAIT_HARVEST :
		return "WAIT_HARVEST";
	case subTakeObject::HARVEST :
		return "HARVEST";
	case subTakeObject::END:
		return "END";
	}
	return "NONE";
}

std::string Converter::convert(AIGoal toConvert) const
{
	switch (toConvert) {
	case AIGoal::JOIN_PLAYER :
		return "JOIN_PLAYER";
	case AIGoal::WAIT :
		return "WAIT";
	case AIGoal::INCANTATION_READY :
		return "INCANTATION_READY";
	case AIGoal::INCANTATION_WAITING :
		return "INCANTATION_WAITING";
	case AIGoal::INCANTATION :
		return "INCANTATION";
	case AIGoal::EXPLORE :
		return "EXPLORE";
	case AIGoal::NONE :
		return "NONE";
	}
	return "NONE";
}

std::string Converter::convert(HarvestStrat &toConvert) const
{
	switch (toConvert) {
	case HarvestStrat::A:
		return "A";
	case HarvestStrat::B:
		return "B";
	case HarvestStrat::C:
		return "C";
	case HarvestStrat::END:
		return "END";
	case HarvestStrat::NONE:
		return "NONE";
	}
	return "NONE";
}

std::string Converter::convert(Inventory toConvert) const
{
	switch (toConvert) {
	case Inventory::LINEMATE :
		return "linemate";
	case Inventory::DERAUMERE :
		return "deraumere";
	case Inventory::SIBUR :
		return "sibur";
	case Inventory::MENDIANE :
		return "mendiane";
	case Inventory::PHIRAS :
		return "phiras";
	case Inventory::THYSTAME :
		return "thystame";
	case Inventory::FOOD :
		return "food";
	case Inventory::NONE :
		return "None";
	}
	return "NONE";
}