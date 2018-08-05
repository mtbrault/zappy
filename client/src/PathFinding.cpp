/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** pathfinding
*/

#include "PathFinding.hpp"

PathFinding::PathFinding()
{
	_dico[Inventory::LINEMATE] = "linemate";
	_dico[Inventory::DERAUMERE] = "deraumere";
	_dico[Inventory::SIBUR] = "sibur";
	_dico[Inventory::MENDIANE] = "mendiane";
	_dico[Inventory::PHIRAS] = "phiras";
	_dico[Inventory::THYSTAME] = "thystame";
	_dico[Inventory::FOOD] = "food";
	_dico[Inventory::NONE] = "";
}

std::vector<std::pair<int, int>> PathFinding::calcPath(std::vector<std::vector<std::string>> vision, Inventor toGet)
{
	std::cout << "calc Path" << std::endl;
	_dir.clear();
	for (auto &it : vision)
		for (auto &it2 : it) {
			std::cout << "loop : [" << it2 << "]"<< std::endl;
	}
	getArray(vision);
	std::cout << "Array getted" << std::endl;
	getTiles(toGet);
	std::cout << "Tiles getted" << std::endl;
	return _dir;
}

void PathFinding::searchPosition(std::string toFind)
{
	int y = 0;
	int x = 0;
	int count = 0;
	int countTmp = 0;
	bool find = false;
	std::pair<int, int> coord;

	for (auto &line : _array) {
		x = 0;
		for (auto &tile : line) {
			countTmp = 0;
			for (auto &item : tile) {
				if (item == toFind)
					countTmp++;
			}
			if (countTmp > count) {
				find = true;
				count = countTmp;
				coord = std::make_pair(x, y);
			}
			x++;
		}
		y++;
	}
	if (find == true)
		_dir.push_back(coord);
}

void PathFinding::getTiles(Inventor toGet)
{
	if (toGet.stones[static_cast<int>(Inventory::LINEMATE)] > 0)
		searchPosition(_dico.find(Inventory::LINEMATE)->second);
	if (toGet.stones[static_cast<int>(Inventory::DERAUMERE)] > 0)
		searchPosition(_dico.find(Inventory::DERAUMERE)->second);
	if (toGet.stones[static_cast<int>(Inventory::SIBUR)] > 0)
		searchPosition(_dico.find(Inventory::SIBUR)->second);
	if (toGet.stones[static_cast<int>(Inventory::MENDIANE)] > 0)
		searchPosition(_dico.find(Inventory::MENDIANE)->second);
	if (toGet.stones[static_cast<int>(Inventory::PHIRAS)] > 0)
		searchPosition(_dico.find(Inventory::PHIRAS)->second);
	if (toGet.stones[static_cast<int>(Inventory::THYSTAME)] > 0)
		searchPosition(_dico.find(Inventory::THYSTAME)->second);
	_dir.erase(std::unique(_dir.begin(), _dir.end()), _dir.end());
}

void PathFinding::getArray(std::vector<std::vector<std::string>> vision)
{
	_array.clear();
	_lenMax = 2;
	int tmp = static_cast<int>(vision.size());
	while (tmp > _lenMax) {
		tmp = tmp - (_lenMax - 1);
		_lenMax += 2;
	}
	_lenMax = _lenMax - 1;
	int count = _lenMax;
	for (auto it = vision.rbegin(); it != vision.rend();) {
		std::vector<std::vector<std::string>> line;
		for (int i = count; i < _lenMax; i += 2) {
			line.push_back({});
		}
		for (int tmp = 0; tmp < count; tmp++) {
			line.push_back(*it);
			++it;
		}
		for (int i = count; i < _lenMax; i += 2) {
			line.push_back({});
		}
		std::reverse(line.begin(), line.end());
		_array.push_back(line);
		count -= 2;
	}
}