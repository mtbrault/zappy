/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** pathfinding header
*/

#ifndef PATHFINDING_HPP_
# define PATHFINDING_HPP_

# include <vector>
# include <iostream>
# include <algorithm>
# include <string>
# include <map>

# include "Inventory.hpp"
# include "Converter.hpp"

class PathFinding {
public:
	PathFinding();
	~PathFinding() {}
	std::vector<std::pair<int, int>> calcPath(std::vector<std::vector<std::string>> vision, Inventor);

private:
	void searchPosition(std::string toFind);
	void getTiles(Inventor);
	void getArray(std::vector<std::vector<std::string>> vision);
	std::vector<std::vector<std::vector<std::string>>>	_array;

	int _size;
	int _count;
	int _lenMax;
	std::vector<std::pair<int, int>> _dir;
	std::map<Inventory, std::string>	_dico;
};

#endif /* !PATHFINDING_HPP_ */