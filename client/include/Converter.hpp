/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Converter
*/

#ifndef CONVERTER_HPP_
# define CONVERTER_HPP_

# include <string>

//# include "ZappyPlayer.hpp"

enum class AIGoal {
	JOIN_PLAYER,
	WAIT,
	INCANTATION_READY,
	INCANTATION_WAITING,
	INCANTATION,
	EXPLORE,
	NONE
	// GIVE_RESSOURCE,
	// PUSH
};

enum class subTakeObject {
	LOOK,
	WAIT_LOOK,
	GET_INVENTORY,
	WAIT_INVENTORY,
	WAIT_HARVEST,
	HARVEST, // harvest = recolte while _dir is not empty
	END // mettre AIGoal à NONE
};

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum class HarvestStrat {
	A, // aller en haut
	B, // faire la moitié de la ligne jusqu'au point
	C, // faire la ligne entière
	END,
	NONE
};

enum class HarvestSubStratB {
	GO_UP,
	TURN,
	FORWARD,
	END
};

enum class HarvestSubStratC {
	TURN,
	CROSS_LINE,
	END
};

enum class Inventory
{
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD,
	NONE
};

class Converter {
public:
	Converter() {}
	~Converter() {}
	std::string convert(subTakeObject &) const;
	std::string convert(HarvestStrat &toConvert) const;
	std::string convert(Inventory toConvert) const;
	std::string convert(AIGoal toConvert) const;
};

#endif /* !CONVERTER_HPP_ */
