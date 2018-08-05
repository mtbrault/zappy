/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
**ZappyPlayer implementation
*/

#include <random>
#include "ZappyPlayer.hpp"
#include <unistd.h>


ZappyPlayer::ZappyPlayer(const std::string &team)
	: _team(team), _goal(AIGoal::NONE), _last(AIGoal::NONE), _dirTaken(false)
{
	_dico[Inventory::LINEMATE] = "linemate";
	_dico[Inventory::DERAUMERE] = "deraumere";
	_dico[Inventory::SIBUR] = "sibur";
	_dico[Inventory::MENDIANE] = "mendiane";
	_dico[Inventory::PHIRAS] = "phiras";
	_dico[Inventory::THYSTAME] = "thystame";
	_dico[Inventory::FOOD] = "food";
	_dico[Inventory::NONE] = "";
	//_choice.insert(std:make_pair(AIGoal::TAKE_OBJECT, &ZappyPlayer::calcTakeObject));
	_level.setLevel(1);
	_inventory.food = -1;
}

ZappyPlayer::~ZappyPlayer()
{
	for (auto &tile : _vision)
		tile.clear();
	//_dir.clear();
	_historicCommand.clear();
	std::queue<std::string> empty;
	std::swap(_historicAnswerCommand, empty);
	_orders.clear();
}

void ZappyPlayer::setInventory(std::string &inventory)
{
	std::istringstream values;
	std::string nb;

//	std::cout << "inventor : " << inventory << std::endl;
	inventory = inventory.substr(std::string("[food ").length(), inventory.length());
	values.str(inventory);
	values >> _inventory.food;

	nb = std::to_string(_inventory.food);
	inventory = inventory.substr(nb.size() + std::string(", linemate ").length(), inventory.length());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::LINEMATE)];

	nb = std::to_string(_inventory.stones[0]);
	inventory = inventory.substr(nb.size() + std::string(", deraumere ").size(), inventory.length());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::DERAUMERE)];

	nb = std::to_string(_inventory.stones[1]);
	inventory = inventory.substr(nb.size() + std::string(", SIBUR ").size(), inventory.size());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::SIBUR)];

	nb = std::to_string(_inventory.stones[2]);
	inventory = inventory.substr(nb.size() + std::string(", mendiane ").size(), inventory.size());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::MENDIANE)];

	nb = std::to_string(_inventory.stones[3]);
	inventory = inventory.substr(nb.size() + std::string(", PHIRAS ").size(), inventory.size());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::PHIRAS)];

	nb = std::to_string(_inventory.stones[4]);
	inventory = inventory.substr(nb.size() + std::string(", thystame ").size(), inventory.size());
//	std::cout << "inventor : " << inventory << std::endl;
	values.str(inventory);
	values >> _inventory.stones[static_cast<int>(Inventory::THYSTAME)];
	// std::cout << "food " << _inventory.food << std::endl;
	// for (int i = 0; i < 6; i++) {	
	// 	std::cout << _inventory.stones[i] << std::endl;
	// }
}

Inventory ZappyPlayer::takeStone(std::vector<std::string> &tile) const
{
	Inventor required = _level.getInventor();
	for (auto &item : tile) {
		if (required.stones[static_cast<int>(Inventory::LINEMATE)] > 0 && item.compare("linemate") == 0) {
			std::cout << "require linemate" << std::endl;
			return Inventory::LINEMATE;
		} if (required.stones[static_cast<int>(Inventory::DERAUMERE)] > 0 && item.compare("deraumere") == 0) {
			std::cout << "require DERAUMERE" << std::endl;
			return Inventory::DERAUMERE ;
		}
		if (required.stones[static_cast<int>(Inventory::SIBUR)] > 0 && item.compare("sibur") == 0) {
			std::cout << "require SIBUR" << std::endl;
			return Inventory::SIBUR;
		}
		if (required.stones[static_cast<int>(Inventory::MENDIANE)] > 0 && item.compare("mendiane") == 0) {
			std::cout << "require MENDIANE" << std::endl;
			return Inventory::MENDIANE;
		}
		if (required.stones[static_cast<int>(Inventory::PHIRAS)] > 0 && item.compare("phiras") == 0) {
			std::cout << "require PHIRAS" << std::endl;
			return Inventory::PHIRAS;
		}
		if (required.stones[static_cast<int>(Inventory::THYSTAME)] > 0 && item.compare("thystame") == 0) {
			std::cout << "require THYSTAME" << std::endl;
			return Inventory::THYSTAME;
		}
	}
	std::cout << "Aucune pierre sur la case, qu'est ce que tu fous encore ici" << std::endl;
	return Inventory::FOOD;
}

Inventory ZappyPlayer::chooseItemToTake(std::vector<std::string> &tile) const
{
	std::random_device re;
	std::uniform_int_distribution<int> distrib{1,10};
	char nb = distrib(re);
	// char nb = (std::rand() % 10) + 1;

	if (_inventory.food > 120) {
		return takeStone(tile);
	} if ((nb - ((_inventory.food - 20) / 10)) > 0)
		for (auto &item : tile) {
			if (item == "food")
				return Inventory::FOOD;
		}
	return takeStone(tile);
}

void ZappyPlayer::takeItem(std::vector<std::string> &tile)
{
	std::string item = _converter.convert(chooseItemToTake(tile));
	std::cout << "PLAYER TAKE " << item << std::endl;
	if (_historicCommand.size() >= 10)
		return;
	_orders.push_back("Take " + item + "\n");
	_historicCommand.push_back(_orders.back());
	unsigned int i = 0;
	std::cout << "Take an item : " <<  item << ", before size of tile = " << tile.size() << std::endl;
	for (auto &i : _array[_posPlayer.second][_posPlayer.first])
		std::cout << i << std::endl;
	std::cout << "And after : " << std::endl;
	for (i = 0; _array[_posPlayer.second][_posPlayer.first].size(); ++i) {
		//std::cout << "On tile : " << *(_array[_posPlayer.second][_posPlayer.first].begin() + i) << std::endl;
		if (!(*(_array[_posPlayer.second][_posPlayer.first].begin() + i)).compare(item)) {
			std::cout << "Remove " << item << " from array" << std::endl;
			break;
		}
	}
	if (_array[_posPlayer.second][_posPlayer.first].begin() + i != _array[_posPlayer.second][_posPlayer.first].end()) {
		std::cout << "Remove the item" << std::endl;
		_array[_posPlayer.second][_posPlayer.first].erase(_array[_posPlayer.second][_posPlayer.first].begin() + i);
	}
	for (auto &i : _array[_posPlayer.second][_posPlayer.first])
		std::cout << i << std::endl;
	for (i = 0; tile.size(); ++i) {
		if (!(*(tile.begin() + i)).compare(item)) {
			break;
		}
	}
	tile.erase(tile.begin() + i);
	std::cout << "size of tile = " << tile.size() << std::endl;
	std::cout << "End of remove " << std::endl;
}

int ZappyPlayer::countTiles()
{
	int h = _posPlayer.second;
	int count = 0;

	while (count == 0 && h >= 0) {
		for (auto &dir : _dir) {
			if (dir.second == h)
				count++;
		}
		h--;
	}
	return count;
}

std::vector<std::pair<int, int>> ZappyPlayer::getNextDirs()
{
	int h = _posPlayer.second;
	std::vector<std::pair<int, int>> line;
	int count = 0;

	std::cout << "getNextDirs" << std::endl;
	for (auto &i: _dir)
		std::cout << i.first << ", " << i.second << std::endl;
	std::cout << "H of player = " << h << std::endl;
	while (count == 0 && h >= 0) {
		std::cout << "LOOP : h = " << h << std::endl;
		for (auto &dir : _dir) {
			if (dir.second == h) {
				std::cout << "A dir is selected" << std::endl;
				count++;
				line.push_back(dir);
			}
		}
		h--;
	}
	std::cout << "End of getNextDirs" << std::endl;
	return line;
}

HarvestStrat ZappyPlayer::chooseStrat()
{
	std::vector<std::pair<int, int>> dirs;
	bool side = false;

	if (countTiles() == 1) {
		if (_posPlayer.first == getNextDirs().front().first)
			return HarvestStrat::A;
		else
			return HarvestStrat::B;
	}
	dirs = getNextDirs();
	if (dirs.empty())
		return HarvestStrat::NONE;
	for (auto dir : dirs) {
		if (dir.first < _posPlayer.first)
			side = true;
	}
	for (auto dir : dirs) {
		if (dir.first > _posPlayer.first && side == true)
			return HarvestStrat::C;
	}
	return HarvestStrat::B;
}

bool ZappyPlayer::checkTileEmpty(std::vector<std::string> &tile) const
{
	Inventor required = _level.getInventor();

	if (tile.empty())
		return true;
	for (auto &item : tile) {
		if (required.stones[static_cast<int>(Inventory::LINEMATE)] > 0 && item.compare("linemate") == 0) {
			std::cout << "il y a encore du linemate" << std::endl;
			return false;
		} if (required.stones[static_cast<int>(Inventory::DERAUMERE)] > 0 && item.compare("deraumere") == 0) {
			std::cout << "il y a encore du deraumere" << std::endl;
			return false;
		} if (required.stones[static_cast<int>(Inventory::SIBUR)] > 0 && item.compare("sibur") == 0) {
			std::cout << "il y a encore du sibur" << std::endl;
			return false;
		} if (required.stones[static_cast<int>(Inventory::MENDIANE)] > 0 && item.compare("mendiane") == 0) {
			std::cout << "il y a encore du mendiane" << std::endl;
			return false;
		} if (required.stones[static_cast<int>(Inventory::PHIRAS)] > 0 && item.compare("phiras") == 0) {
			std::cout << "il y a encore du phiras" << std::endl;
			return false;
		} if (required.stones[static_cast<int>(Inventory::THYSTAME)] > 0 && item.compare("thystame") == 0) {
			std::cout << "il y a encore du thystame" << std::endl;
			return false;
		}
	}
	return true;
}

bool ZappyPlayer::explore(HarvestStrat &strat, std::vector<std::pair<int, int>> &nextTiles)
{
	std::random_device re;
	std::uniform_int_distribution<int> distrib{0, 100};
	int tmp = distrib(re);
	// int tmp = std::rand() % 100;
	if (_inventory.food < 20) {
		std::cout << "Need some food" << std::endl;
		for (unsigned int y = 0; y < _array.size(); y++) {
			for (unsigned int x = 0; x < _array[y].size(); x++) {
				if (std::find(_array[y][x].begin(), _array[y][x].end(), "food") != _array[y][x].end()) {
					_dir.push_back(std::make_pair(x, y));
				}
			}
		}
		if (!_dir.empty()) {
			strat = chooseStrat();
			nextTiles = getNextDirs();
			return false;
		}
	}
	if (tmp < 20 && _historicCommand.size() < 10) {
		_orders.push_back("Left\n");
		_historicCommand.push_back("Left");
	} else if (tmp > 80 && _historicCommand.size() < 10) {
		_orders.push_back("Right\n");
		_historicCommand.push_back("Right");
	}
	if (_historicCommand.size() < 10) {
		_orders.push_back("Forward\n");
		_historicCommand.push_back("Forward");
	}
	return true;
}

bool ZappyPlayer::playerIsOnTile(std::vector<std::pair<int, int>> nextTiles)
{
	std::cout << "On player Is On Tile" << std::endl;
	for (auto &tile : nextTiles) {
		std::cout << "Tile : [" << tile.first << "," << tile.second << "] and Player : ["<< _posPlayer.first << "," << _posPlayer.second << "]" << std::endl;
		if (tile.first == _posPlayer.first && tile.second == _posPlayer.second) {
			std::cout << "Return true\n";
			return true;
		}
	}
	return false;
}

std::vector<std::string> &ZappyPlayer::getTile()
{
	return _array[_posPlayer.second][_posPlayer.first];
}


void ZappyPlayer::turnToUp(std::vector<std::pair<int, int>> nextTiles)
{
	if (_direction == Direction::LEFT && nextTiles.front().second != _posPlayer.second && _historicCommand.size() < 10) {
		_orders.push_back("Right\n");
		_historicCommand.push_back("Right");
		_direction = Direction::UP;
	} else if (_direction == Direction::RIGHT && nextTiles.front().second != _posPlayer.second && _historicCommand.size() < 10) {
		_historicCommand.push_back("Left");
		_orders.push_back("Left\n");
		_direction = Direction::UP;
	}
}

void ZappyPlayer::removeOneDir(std::pair<int, int> toRemove, std::vector<std::pair<int, int>> &nextTiles)
{
	unsigned int i = 0;
	std::cout << "Remove one dir" << std::endl;
	for (i = 0; i < _dir.size(); ++i)
		if ((_dir.begin() + i)->first == toRemove.first && (_dir.begin() + i)->second == toRemove.second) {
			std::cout << "Erase _dir tile " << std::endl;
			break;
		}
	_dir.erase(_dir.begin() + i);
	for (i = 0; i < nextTiles.size(); ++i)
		if ((nextTiles.begin() + i)->first == toRemove.first && (nextTiles.begin() + i)->second == toRemove.second) {
			std::cout << "Erase nextTile tile" << std::endl;
			break;
		}
	nextTiles.erase(nextTiles.begin() + i);
	std::cout << "END of REMOVE ONE DIR" << std::endl << std::endl;
}

void ZappyPlayer::turnOnLine(std::vector<std::pair<int, int>> nextTiles)
{
	if (_historicCommand.size() >= 10) {
		return;
	} for (auto &tile : nextTiles) {
		if (tile.first < _posPlayer.first) {
			_orders.push_back("Left\n");
			_direction = Direction::LEFT;
			_historicCommand.push_back("Left");
			return ;
		} else if (tile.first > _posPlayer.first) {
			_orders.push_back("Right\n");
			_direction = Direction::RIGHT;
			_historicCommand.push_back("Right");
			return ;
		}
	}
}

std::pair<int, int> ZappyPlayer::getFirstTile()
{
	auto nextDir = getNextDirs();
	std::pair<int, int> toReturn = nextDir.front();

	if (_direction == Direction::RIGHT) {
		std::cout << "Right\n";
		for (auto i: nextDir) {
			if (i.first > toReturn.first)
				toReturn = std::make_pair(i.first, i.second);
		}
	} else {
		std::cout << "Left\n";
		for (auto i: nextDir) {
			if (i.first < toReturn.first)
				toReturn = std::make_pair(i.first, i.second);
		}
	}
	return toReturn;
}

void	ZappyPlayer::turnOtherSide(Direction dir, int farthestLeft, int farthestRight)
{
	if (_direction == Direction::RIGHT && dir == Direction::LEFT
	&& _historicCommand.size() < 10) {
		_dirTaken = true;
		std::cout << "Turn left from RIGHT" << std::endl;
		_historicCommand.push_back("Left");
		_orders.push_back("Left\n");
		_direction = Direction::UP;
	}
	if (_direction == Direction::LEFT && dir == Direction::RIGHT
	&& _historicCommand.size() < 10) {
		_dirTaken = true;
		std::cout << "Turn Right from LEFT" << std::endl;
		_historicCommand.push_back("Right");
		_orders.push_back("Right\n");
		_direction = Direction::UP;
	}
	if (_direction == Direction::UP && _historicCommand.size() < 10) {
		_dirTaken = true;
		if (farthestLeft < farthestRight) {
			std::cout << "Turn left from up" << std::endl;
			_historicCommand.push_back("Left");
			_orders.push_back("Left\n");
			_direction = Direction::LEFT;
		} else {
			std::cout << "Turn right from up" << std::endl;
			_historicCommand.push_back("Right");
			_orders.push_back("Right\n");
			_direction = Direction::RIGHT;
		}
	}
}

int	ZappyPlayer::getFarthestLeft(std::vector<std::pair<int, int>> &nextTiles) const
{
	int min = nextTiles.front().first;

	for (auto &tile : nextTiles) {
		if (min > tile.first)
			min = tile.first;
	}
	return (min > _posPlayer.first ? min - _posPlayer.first : _posPlayer.first - min);
}

int	ZappyPlayer::getFarthestRight(std::vector<std::pair<int, int>> &nextTiles) const
{
	int max = nextTiles.front().first;

	for (auto &tile : nextTiles) {
		if (max < tile.first)
			max = tile.first;
	}
	return (max > _posPlayer.first ? max - _posPlayer.first : _posPlayer.first - max);
}

void ZappyPlayer::harvest()
{
	static HarvestStrat strat = HarvestStrat::NONE;
	static std::vector<std::pair<int, int>> nextTiles;
	static bool searchOnlyFood = false;

	std::cout << "____ HARVEST _____" << std::endl;
	if (strat == HarvestStrat::NONE) {
		_dirTaken = false;
		std::cout << " Choose strat" << std::endl;
		if (_dir.empty())
			_dir = _pahtFinder.calcPath(_vision, _level.getInventor());
		strat = chooseStrat();
		std::cout << "Strat choosed : " << _converter.convert(strat) << std::endl;
		nextTiles.clear();
		nextTiles = getNextDirs();
		if (nextTiles.empty()) {
			std::cout << "	Pas de case où aller." << std::endl;
			strat = HarvestStrat::NONE;
			if (explore(strat, nextTiles) == true) {
				std::cout << "	Just explore" << std::endl;
				changeGoal(AIGoal::NONE);
				std::cout << "____ End Harvest ____" << std::endl;
				return;
			}
			if (_dir.empty()) {
				changeGoal(AIGoal::NONE);
				std::cout << "____ End Harvest ____" << std::endl;
				return;
			}
			std::cout << "Explore to search food" << std::endl;
			searchOnlyFood = true;
		}
		if (_last == AIGoal::EXPLORE)
			_last = AIGoal::NONE;
		std::cout << "Les cases où aller sont du nombre de " << nextTiles.size() << " cases" << std::endl;
		for (auto &tile : nextTiles) {
			std::cout << "Tile [" << tile.first << "," << tile.second << "]" << std::endl;
		}
		std::cout << "Le player est sur la case [" << _posPlayer.first << "," << _posPlayer.second << "]" << std::endl;
	}
	if (strat == HarvestStrat::A) {
		std::cout << " == Strat A == " << std::endl;
		if (_historicCommand.size() >= 10) {
			std::cout << "Besoin d'attendre pour la réponse des commandes." << std::endl;
			changeGoal(AIGoal::WAIT);
			return ;
		}
		else if (_direction == Direction::LEFT) {
			std::cout << "	Player turn right" << std::endl;
			_orders.push_back("Right\n");
			_historicCommand.push_back("Right");
			_direction = Direction::UP;
		} else if (_direction == Direction::RIGHT) {
			std::cout << "	Player turn left" << std::endl;
			_historicCommand.push_back("Left");
			_orders.push_back("Left\n");
			_direction = Direction::UP;
		}
		if (_direction == Direction::UP) {
			while (_historicCommand.size() < 10 &&
			nextTiles.front().second < _posPlayer.second) {
				std::cout << "	Player move forward" << std::endl;
				_orders.push_back("Forward\n");
				_historicCommand.push_back("Forward");
				_posPlayer.second--;
			}
			if (_historicCommand.size() >= 10) {
				std::cout << "Besoin d'attendre pour la réponse des commandes." << std::endl;
				changeGoal(AIGoal::WAIT);
				return ;
			}
			else if (playerIsOnTile(nextTiles) == true) {
				std::cout << "Player on tile " << std::endl;
				auto tile = getTile();
				takeItem(tile);
				if (checkTileEmpty(tile) == true) {
					std::cout << "EMpty tile" << std::endl;
					if (searchOnlyFood == true && _inventory.food > 50) {
						_dir.clear();
						strat = HarvestStrat::NONE;
						changeGoal(AIGoal::NONE);
						searchOnlyFood = false;
					}
					removeOneDir(std::make_pair(_posPlayer.first, _posPlayer.second), nextTiles);
					if (_dir.empty()) {
						_dir.clear();
						changeGoal(AIGoal::NONE);
						strat = HarvestStrat::NONE;
					} else if (nextTiles.empty())
						strat = HarvestStrat::NONE;
					return;
				}
				std::cout << "checkTileEmpty has returned false" << std::endl;
			} else {
				std::cout << "Player not on tile alors qu'il est arrivé : " << std::endl;
				std::cout << "Pos player [" << _posPlayer.first << "," << _posPlayer.second << "]" << std::endl;
			}
		}
	} else if (strat == HarvestStrat::B) {
		std::cout << "\nIn strat B" << std::endl;
		if (_historicCommand.size() >= 10) {
			changeGoal(AIGoal::WAIT);
			return;
		} else
			turnToUp(nextTiles);
		if (_direction == Direction::UP) {
			while (_historicCommand.size() < 10 &&
			nextTiles.front().second < _posPlayer.second) {
				std::cout << "boucle\n";
				_orders.push_back("Forward\n");
				_historicCommand.push_back("Forward");
				_posPlayer.second--;
			}
		}
		if (_historicCommand.size() >= 10) {
			changeGoal(AIGoal::WAIT);
			return;
		} else if (nextTiles.front().second == _posPlayer.second) {
			if (playerIsOnTile(nextTiles)) {
//				std::cout << "============Player on tile==========" << std::endl;
				auto tile = getTile();
				takeItem(tile);
				if (checkTileEmpty(tile)) {
//					std::cout << "EMpty tile" << std::endl;
					if (searchOnlyFood == true && _inventory.food > 50) {
						_dir.clear();
						strat = HarvestStrat::NONE;
						changeGoal(AIGoal::NONE);
						searchOnlyFood = false;
					}
					removeOneDir(std::make_pair(_posPlayer.first, _posPlayer.second), nextTiles);
					if (_dir.empty()) {
						_dir.clear();
						strat = HarvestStrat::NONE;
						changeGoal(AIGoal::NONE);
					} else if (nextTiles.empty())
						strat = HarvestStrat::NONE;
					return;
				}
				// std::cout << "checkTileEmpty has returned false" << std::endl;	
			} else if (_direction == Direction::UP) {
//				std::cout << "Direction == UP" << std::endl;
				turnOnLine(nextTiles);
			} else {
//				std::cout << "Have to move forward\n";
				while (_historicCommand.size() < 10 &&
				playerIsOnTile(nextTiles) == false) {
//					std::cout << "One forward\n";
					_orders.push_back("Forward\n");
					_historicCommand.push_back("Forward");
					if (_direction == Direction::LEFT)
						_posPlayer.first--;
					else if (_direction == Direction::RIGHT)
						_posPlayer.first++;
					else
						std::cout << "n'a pas tourné, PROBLEM STRAT B HARVEST" << std::endl;
				}
				if (_historicCommand.size() >= 10)
//					changeGoal(AIGoal::WAIT);
					_goal = AIGoal::WAIT;
			}
		}
//			} else if ()
 	} else if (strat == HarvestStrat::C) {
		if (_historicCommand.size() >= 10) {
			std::cout << "WAIT FOR REMOVING OF COMMAND" << std::endl;
			changeGoal(AIGoal::WAIT);
			return;
		}
		std::vector<std::pair<int, int>> nextTiles = getNextDirs();
		int farthestLeft = getFarthestLeft(nextTiles), farthestRight = getFarthestRight(nextTiles);
		if (nextTiles.front().second != _posPlayer.second) {
			std::cout << "Sur la ligne en dessous\n";
			if (_dirTaken == false) {
				std::cout << "Pas encore tourné" << std::endl;
				if (_direction == Direction::RIGHT && (farthestRight - farthestLeft) > 2) {
					std::cout << "decide to turn on left\n";
					turnOtherSide(Direction::LEFT, farthestLeft, farthestRight);
				} else if (_direction == Direction::LEFT && (farthestRight - farthestLeft) >= 2) {
					std::cout << "decide to turn on right\n";
					turnOtherSide(Direction::RIGHT, farthestLeft, farthestRight);
				} else if (_direction == Direction::UP) {
					std::cout << "Direction is UP, decide to turn\n";
					turnOtherSide((farthestLeft > farthestRight ? Direction::RIGHT : Direction::LEFT), farthestLeft, farthestRight);
				} else if (_historicCommand.size() >= 10) {
					changeGoal(AIGoal::WAIT);
					return;
				}
			} else {
				std::cout << "A tourner normalement" << std::endl;
				std::pair<int, int> firstTile = getFirstTile();
				std::cout << "FirsTile : " << firstTile.first << "," << firstTile.second << std::endl;
				while (firstTile.first != _posPlayer.first && _historicCommand.size() < 10
				&& (_direction == Direction::LEFT || _direction == Direction::RIGHT)) {
					if (_direction == Direction::LEFT)
						_posPlayer.first--;
					else
						_posPlayer.first++;
					_historicCommand.push_back("Forward");
					_orders.push_back("Forward\n");
				}
				if (_historicCommand.size() >= 10) {
					std::cout << "WAIT FOR REMOVING OF COMMAND" << std::endl;
					changeGoal(AIGoal::WAIT);
					return;
				}
				if (_historicCommand.size() < 10 && _direction == Direction::UP && firstTile.second != _posPlayer.second) {
					_historicCommand.push_back("Forward");
					_orders.push_back("Forward\n");
					_posPlayer.second--;
				} else if (_historicCommand.size() && _direction != Direction::UP) {
					if (_direction == Direction::LEFT) {
						std::cout << "Tourne a droite pour aller en haut\n";
						_historicCommand.push_back("Right");
						_orders.push_back("Right\n");
					} else {
						std::cout << "Tourne a gauche pour aller en haut\n";
						_historicCommand.push_back("Left");
						_orders.push_back("Left\n");
					}
					_direction = Direction::UP;
				}
				if (_historicCommand.size() >= 10) {
					changeGoal(AIGoal::WAIT);
					return;
				}
			}
		} else {

			std::cout << "Have to change dir maybe - Strat C" << std::endl;
			if (playerIsOnTile(nextTiles) == true) {
				std::cout << "============Player on tile==========" << std::endl;
				auto tile = getTile();
				takeItem(tile);
				if (checkTileEmpty(tile)) {
					std::cout << "EMpty tile" << std::endl;
					if (searchOnlyFood == true && _inventory.food > 50) {
						_dir.clear();
						strat = HarvestStrat::NONE;
						changeGoal(AIGoal::NONE);
						searchOnlyFood = false;
					}
					removeOneDir(std::make_pair(_posPlayer.first, _posPlayer.second), nextTiles);
					if (_dir.empty()) {
						_dirTaken = true;
						_dir.clear();
						strat = HarvestStrat::NONE;
						changeGoal(AIGoal::NONE);
						std::cout << "END OF STRAT C\n";
					} else if (nextTiles.empty())
						strat = HarvestStrat::NONE;
					return;
				}
				std::cout << "checkTileEmpty has returned false" << std::endl;	
			} else if (_direction == Direction::UP) {
				std::cout << "Direction == UP" << std::endl;
				turnOnLine(nextTiles);
			} else {
				std::cout << "Have to move forward\n";
				while (_historicCommand.size() < 10 &&
				playerIsOnTile(nextTiles) == false) {
					std::cout << "One forward\n";
					_orders.push_back("Forward\n");
					_historicCommand.push_back("Forward");
					if (_direction == Direction::LEFT)
						_posPlayer.first--;
					else if (_direction == Direction::RIGHT)
						_posPlayer.first++;
					else
						std::cout << "n'a pas tourné, PROBLEM STRAT C HARVEST" << std::endl;
				}
				std::cout << "Out of while " << std::endl;
				if (_historicCommand.size() >= 10) {
					std::cout << "WAIT FOR REMOVING OF COMMAND" << std::endl;
					changeGoal(AIGoal::WAIT);
				}
			}
		}
	}
}

void ZappyPlayer::getArray()
{
	_array.clear();
	int lenMax = 2;
	int tmp = static_cast<int>(_vision.size());
	while (tmp > lenMax) {
		tmp = tmp - (lenMax - 1);
		lenMax += 2;
	}
	lenMax = lenMax - 1;
	int count = lenMax;
	for (auto it = _vision.rbegin(); it != _vision.rend();) {
		std::vector<std::vector<std::string>> line;
		for (int i = count; i < lenMax; i += 2) {
			line.push_back({});
		}
		for (int tmp = 0; tmp < count; tmp++) {
			line.push_back(*it);
			++it;
		}
		for (int i = count; i < lenMax; i += 2) {
			line.push_back({});
		}
		std::reverse(line.begin(), line.end());
		_array.push_back(line);
		count -= 2;
	}
}

void	ZappyPlayer::decipherLook(const std::string &str)
{
	_vision.clear();
	auto	j = 0;
	for (auto i = 1 ; str[i] && str[i] != ']' ; i += 1) {
		std::vector<std::string>	add;
		for (j = i; str[j] && str[j] != ']' && str[j] != ',' ; j += 1);
		std::istringstream	ss(str.substr(i, j - i));
		for (std::string item ; str[j] && ss >> item;)
			add.push_back(item);
		i = (str[j] ? j : j - 1);
		if (str[j])
			_vision.push_back(add);
	}
}

bool	ZappyPlayer::readyToIncantate()
{
	std::cout << "geree" << std::endl;
	auto &tile = getTile();
	int nbPlayers = std::count_if(tile.begin(), tile.end(),
		[](const std::string &str) {
			return (!str.compare("player"));
	});
	
	if (nbPlayers >= _level.getPlayerNumber()) {
		std::cout << "Enough Players (" << nbPlayers << "/" << _level.getPlayerNumber() << ")\n";
		//Check if enough stones
		/*for (auto i = 0 ; i < 6 ; i += 1) {
			for (auto nb = ; nb ; nb -= 1) {

			}
		}*/
		_orders.push_back("set linemate\n");
		return (true);
	} else {
		std::cout << "Not Enough Players (" << nbPlayers << "/" << _level.getPlayerNumber() << ")\n";
	}
	return (false);
}

void	ZappyPlayer::joinPlayer()
{
	if (!_callDir)
		return ;
	if (_callDir == 1 || _callDir == 2 || _callDir == 8) {
		_orders.push_back("Forward\n");
		_historicCommand.push_back("Forward");
	} else if (_callDir == 3 || _callDir == 4) {
		_historicCommand.push_back("Left");
		_orders.push_back("Left\n");
	} else if (_callDir == 6 || _callDir == 7) {
		_historicCommand.push_back("Right");
		_orders.push_back("Right\n");
	} else if (_callDir == 5) {
		_orders.push_back("Right\nRight\nForward\n");
		_historicCommand.push_back("Right");
		_historicCommand.push_back("Right");
		_historicCommand.push_back("Forward");
	}
}

void	ZappyPlayer::incantationManager()
{
	if (_goal == AIGoal::INCANTATION_READY) {
		if (_level.getLevel() == 1) {
			_goal = AIGoal::INCANTATION_WAITING;
			return ;
		}
		_orders.push_back(std::string("Broadcast ") + _team + std::string(" NeedHelp ") + std::to_string(_level.getLevel()) + "\n");
		_historicCommand.push_back("Broadcast");
	} else if (_goal == AIGoal::INCANTATION_WAITING) {
		if (readyToIncantate()) {
			_orders.push_back(std::string("Broadcast ") + _team + " StartingIncantation\n");
			_historicCommand.push_back("Broadcast");
			_orders.push_back("Start incantation\n");
			_historicCommand.push_back("Start incantation");
			changeGoal(AIGoal::INCANTATION);
		} else {
			_historicCommand.push_back("Broadcast\n");
			_orders.push_back(std::string("Broadcast ") + _team + std::string(" NeedHelp ") + std::to_string(_level.getLevel()) + "\n");
		}
	}
}

void	ZappyPlayer::changeGoal(const AIGoal &g)
{
	_last = _goal;
	_goal = g;
}

void	ZappyPlayer::addItemToInventory(std::string item)
{
	std::cout << "Item to add : -" << item << "-" << std::endl;

	if (item == "food\n") {
		std::cout << "add one " << "food" << std::endl;
		_inventory.food ++;
	} if (item == "linemate\n") {
		std::cout << "add one " << "linemate" << std::endl;
		_inventory.stones[0]++;
	} if (item == "deraumere\n") {
		std::cout << "add one " << "deraumere" << std::endl;
		_inventory.stones[1]++;
	} if (item == "sibur\n") {
		std::cout << "add one " << "sibur" << std::endl;
		_inventory.stones[2]++;
	} if (item == "mendiane\n") {
		std::cout << "add one " << "mendiane" << std::endl;
		_inventory.stones[3]++;
	} if (item == "phiras\n") {
		std::cout << "add one " << "phiras" << std::endl;
		_inventory.stones[4]++;
	} if (item == "thystame\n") {
		std::cout << "add one " << "thystame" << std::endl;
		_inventory.stones[5]++;
	}
	// if (!item.compare("food"))
	// 	_inventory.food ++;
	// if (!item.compare("linemate"))
	// 	_inventory.stones[0]++;
	// if (!item.compare("deraumere"))
	// 	_inventory.stones[1]++;
	// if (!item.compare("sibur"))
	// 	_inventory.stones[2]++;
	// if (!item.compare("mendiane"))
	// 	_inventory.stones[3]++;
	// if (!item.compare("phiras"))
	// 	_inventory.stones[4]++;
	// if (!item.compare("thystame"))
	// 	_inventory.stones[5]++;
}

void	ZappyPlayer::findGoal()
{
	std::cout << "Goal : " << _converter.convert(_goal) << std::endl;
	if (_goal == AIGoal::NONE) {
		std::cout << "-- No actual goal" << std::endl;
		_orders.push_back("Look\n");
		_historicCommand.push_back("Look");
		if (_inventory.food == -1) {
			_orders.push_back("Inventory\n");
			_historicCommand.push_back("Inventory");
		}
		_goal = AIGoal::WAIT;
	} else if (_goal == AIGoal::WAIT && _receiveHist.size()) {
		std::cout << "food : " << _inventory.food<< ", ";
		for (int i = 0; i < 6; i++) {
			std::cout << "stone[" << i + 1 << "] = " << _inventory.stones[i] << ", ";
		}
		std::cout << std::endl;
		std::cout << "-- Goal is Waiting ->" << _receiveHist.front() << std::endl;
		int size = _receiveHist.size();
		for (int i = 0; i < size && _historicCommand.front().compare("Look")
		&& _historicCommand.front().compare("Inventory"); ++i) {
			if (!_historicCommand.front().compare(0, std::string("Take").size(), "Take") && !_receiveHist.front().compare("ok")) {
				std::cout << "Cmd with item to take " << _historicCommand.front() <<  "add item : " << _historicCommand.front().substr(std::string("Take ").size()) << std::endl;//, _historicCommand.size()) << std::endl;
				addItemToInventory(_historicCommand.front().substr(std::string("Take ").size()));//, _historicCommand.size()));
			}
			_receiveHist.pop();
			_historicCommand.pop_front();
			// sleep(1);
		}
		if (_historicCommand.size() > 0 && !_historicCommand.front().compare("Look") && _receiveHist.size()) {
			decipherLook(_receiveHist.front());
			_historicCommand.pop_front();
			_receiveHist.pop();
			_direction = Direction::UP;
			getArray();
			_posPlayer = std::make_pair(_array.front().size() / 2, _array.size() - 1);
		}
		if (_historicCommand.size() > 0 && !_historicCommand.front().compare("Inventory")
		&& _receiveHist.size()) {
			std::cout << "set inventory" << std::endl;
			_historicCommand.pop_front();
			setInventory(_receiveHist.front());
			_receiveHist.pop();
		}
		std::cout << "historic cmd size : " << _historicCommand.size() << ", last goal = " << _converter.convert(_last);
		std::cout << ", _dir size : " << _dir.size() << ", dir empty ? << " << std::boolalpha << _dir.empty();
		if (_historicCommand.size() > 0)
			std::cout << ", first historic cmd : " <<  _historicCommand.front() << std::endl;
		else
			std::cout << std::endl;
		if (_historicCommand.size() > 0 && _last == AIGoal::EXPLORE &&
		_dir.empty()) {
			_goal = AIGoal::WAIT;
			std::cout << "Wait for remove old command and get the look" << std::endl;
		} else if (!_level.checkReady(_inventory) && _inventory.food != -1) {
			_goal = AIGoal::EXPLORE;
			std::cout << "NOT READY TO INCANTATE" << std::endl;
		}
		if (_level.checkReady(_inventory) && _inventory.food != -1){
			std::cout<< "READY TO INCANTATE" << std::endl;
			_goal = AIGoal::INCANTATION_READY;
		}
	} else if (_goal == AIGoal::WAIT) {
		std::cout << "C(est WAIT" << std::endl;
	}
	else if (_goal == AIGoal::EXPLORE) {
		std::cout << "-- Exploring" << std::endl;
		harvest();
	} else if (_goal == AIGoal::JOIN_PLAYER) {
		std::cout << "-- Joining PLAYER" << std::endl;
		joinPlayer();
	} else if (_goal == AIGoal::INCANTATION_READY || _goal == AIGoal::INCANTATION_WAITING) {
		std::cout << "-- Incantation READY" << std::endl;
		incantationManager();
	}
}

void	ZappyPlayer::analyseComs(const std::vector<std::string> &messages)
{
	for (auto &it : messages) {
		std::istringstream	ss(it);
		std::string		object;
		int			dir;
		int			level;
		ss >> object;
		ss >> dir;
		ss >> object;
		if (object.compare(_team))
			continue;
		ss >> object;
		ss >> level;
		if (!object.compare("NeedHelp") && level == _level.getLevel() && _historicCommand.size() < 10) {
			_callDir = dir;
			_historicCommand.push_back("Broadcast");
			_orders.push_back(std::string("Broadcast ") + _team + " IHelp " + std::to_string(_level.getLevel()));
			_goal = AIGoal::JOIN_PLAYER;
		} else if (!object.compare("IHelp") && level == _level.getLevel() && _goal == AIGoal::INCANTATION_READY) {
			_goal = AIGoal::INCANTATION_WAITING;
		}
	}
}

void	ZappyPlayer::parseMessage(const std::vector<std::string> &vec)
{
	std::vector<std::string>	com;
	std::srand(std::time(nullptr)); // a enlever
	for (auto &msg : vec) {
		if (msg.compare(0, std::string("message").size(), "message") == 0) {
			_messageHist.push(msg);
			com.push_back(msg);
		} else
			_receiveHist.push(msg);
	}
	analyseComs(com);
}

std::vector<std::string> &ZappyPlayer::think(const std::vector<std::string> &vec)
{
	std::cout << "--- Thinking ---" << std::endl;
	for (auto &it : vec)
		std::cout << "<= " << it << std::endl;
	_orders.clear();
	parseMessage(vec);
	findGoal();
	for (auto &it : _orders) {
		std::cout << "=> " << it;
	}
	return (_orders);
}