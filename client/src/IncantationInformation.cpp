/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** IncantationInformation
*/

#include "IncantationInformation.hpp"

void IncantationInformation::setLevel(int level)
{
	_level = level;
	switch (level) {
		case 1:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 0;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_inventorRequired.food = 0;
			_nbPlayerRequired = 1;
			break;
		case 2:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 1;
	
			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_nbPlayerRequired = 2;
			break;
		case 3:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 1;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_nbPlayerRequired = 2;
			break;
		case 4:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 2;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_nbPlayerRequired = 4;
			break;
		case 5:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 1;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 3;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_nbPlayerRequired = 4;
			break;
		case 6:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 3;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 0;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 1;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 0;
			_nbPlayerRequired = 6;
			break;
		case 7:
			_inventorRequired.stones[static_cast<int>(Inventory::LINEMATE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::DERAUMERE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::SIBUR)] = 2;

			_inventorRequired.stones[static_cast<int>(Inventory::MENDIANE)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::PHIRAS)] = 2;
			_inventorRequired.stones[static_cast<int>(Inventory::THYSTAME)] = 1;
			_nbPlayerRequired = 6;
			break;
	}
}

bool	IncantationInformation::checkReady(const Inventor &tmp) const
{
	for (auto i = 0 ; i < 6 ; i += 1) {
		if (tmp.stones[i] < _inventorRequired.stones[i] && _inventorRequired.stones[i])
			return (false);
	}
	return (true);
}

int	IncantationInformation::getPlayerNumber() const
{
	return (_nbPlayerRequired);
}