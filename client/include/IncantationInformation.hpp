/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** IncantationInformation
*/

#ifndef INCANTATIONINFORMATION_HPP_
# define INCANTATIONINFORMATION_HPP_

# include "Inventory.hpp"
# include "Converter.hpp"

class IncantationInformation {
public:
	IncantationInformation() { setLevel(1); }
	~IncantationInformation() {}
	void setLevel(int level);
	Inventor getInventor() const { return _inventorRequired; }
	int getNbPlayer() const { return _nbPlayerRequired; }
	int	getLevel() const { return _level; }
	bool	checkReady(const Inventor &) const;
	int	getPlayerNumber() const;

private:
	int _level;
	int _nbPlayerRequired;
	Inventor _inventorRequired;
};

#endif /* !INCANTATIONINFORMATION_HPP_ */
