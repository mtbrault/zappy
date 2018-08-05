/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
# define INVENTORY_HPP_

struct Inventor {
	Inventor() :stones{0, 0, 0, 0, 0, 0}, food(0) {}
	int stones[6];
	int food;
};

// enum class Inventory
// {
// 	LINEMATE,
// 	DERAUMERE,
// 	SIBUR,
// 	MENDIANE,
// 	PHIRAS,
// 	THYSTAME,
// 	FOOD,
// 	NONE
// };

#endif /* !INVENTORY_HPP_ */
