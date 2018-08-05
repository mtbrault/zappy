/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** ZappyPlayer implementation
*/

#ifndef ZAPPYPLAYER_HPP_
# define ZAPPYPLAYER_HPP_

/*
# include <string>
# include <vector>
# include <random>
# include <chrono>
# include <iostream>
# include <sstream>
# include <map>
# include <queue>
# include <stack>
# include <algorithm>
# include <unordered_map>
# include <utility>

# include "Converter.hpp"
# include "IncantationInformation.hpp"
# include "PathFinding.hpp"

# include <unistd.h> // to remove
*/


# include <string>
# include <vector>
# include <random>
# include <chrono>
# include <iostream>
# include <sstream>
# include <map>
# include <list>
# include <queue>
# include <stack>
# include <algorithm>
# include <unordered_map>
# include <utility>

# include "Converter.hpp"
# include "IncantationInformation.hpp"
# include "PathFinding.hpp"

typedef std::vector<std::vector<std::string>> mapper;

class	ZappyPlayer {
public:
	ZappyPlayer(const std::string &);
	~ZappyPlayer();

	std::vector<std::string>	&think(const std::vector<std::string> &);
private:
	void	parseMessage(const std::vector<std::string> &);
	void	changeGoal(const AIGoal &);
	void	decipherLook(const std::string &);
	void	findGoal();
	void	setInventory(std::string &inventory);
	Inventory	takeStone(std::vector<std::string> &tile) const;
	Inventory	chooseItemToTake(std::vector<std::string> &tile) const;
	void		takeItem(std::vector<std::string> &);
	int		countTiles();
	HarvestStrat	chooseStrat();
	void		joinPlayer();
	void	harvest();
	bool	explore(HarvestStrat &strat, std::vector<std::pair<int, int>> &nextTiles);
	void	getArray();
	bool	checkTileEmpty(std::vector<std::string> &tile) const;
	std::vector<std::pair<int, int>>	getNextDirs();
	void	incantationManager();
	bool	checkAnswer();
	void	addItemToInventory(std::string item);
	bool	readyToIncantate();
	void	analyseComs(const std::vector<std::string> &messages);
	bool	playerIsOnTile(std::vector<std::pair<int, int>> nextTiles);
	void	turnToUp(std::vector<std::pair<int, int>> nextTiles);
	std::vector<std::string>	&getTile();
	void	removeOneDir(std::pair<int, int>, std::vector<std::pair<int, int>> &);
	void	turnOnLine(std::vector<std::pair<int, int>> nextTiles);
	int	getFarthestRight(std::vector<std::pair<int, int>> &nextTiles) const;
	int	getFarthestLeft(std::vector<std::pair<int, int>> &nextTiles) const;
	void	turnOtherSide(Direction dir, int farthestLeft, int farthestRight);
	std::pair<int, int> getFirstTile();

	std::vector<mapper>	_array;
	std::string		_team;
	PathFinding		_pahtFinder;
	AIGoal			_goal;
	AIGoal			_last;
	std::vector<std::string>	_orders;
	std::queue<std::string>	_messageHist;
	std::stack<std::string>	_sendHist;
	std::queue<std::string>	_receiveHist;
	std::list<std::string>	_historicCommand;
	std::queue<std::string>	_historicAnswerCommand;
	mapper			_vision;
	Inventor		_inventory;
	std::map<Inventory, std::string>	_dico;
	IncantationInformation	_level;
	std::pair<int, int>	_posPlayer;
	int	_callDir;
	std::vector<std::pair<int, int>>	_dir;
	Direction _direction;
	bool _dirTaken;
	Converter _converter;
};

#endif /* !ZAPPYPLAYER_HPP_ */