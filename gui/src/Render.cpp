/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Rendering
*/

#include "Render.hpp"

static const float tab[4] = {
	0.0f,
	90.0f,
	180.0f,
	-90.0f
};

typedef struct	model_s {
	std::string model;
	std::string texture;
	float		scale;
}				model_t;

static const model_t models[NBMODELS] = {
	{"./media/ironman.MD3", "./media/ironman.png", 1.0f},
	{"./media/oakt.MD3", "./media/oakt.png", 1.0f},
	{"./media/venom.MD3", "./media/venom.png", 1.0f}
};

Render::Render()
	: _id(0), _idCube(0), _idTeam(0)
{
	for (int i = 0; i < NBMODELS; ++i) {
		_allModels.insert(std::make_pair(i, models[i].model));
		_allTextures.insert(std::make_pair(i, models[i].texture));
		_allScales.insert(std::make_pair(i, models[i].scale));
	}
}

Render::~Render()
{
}

void	Render::addButton(int id, std::string text, std::pair<int, int> pos, std::pair<int, int> size)
{
	_buttons.insert(std::make_pair(id, std::make_unique<MenuItem>(Entity::BUTTON, id, text, pos.first, pos.second, size.first, size.second)));
	_rendering.push_back(std::make_unique<MenuItem>(Entity::BUTTON, id, text, pos.first, pos.second, size.first, size.second));
}

void	Render::addCube(std::pair<int, int> pos, std::array<int, 7> _rs)
{
	_cubes.insert(std::make_pair(_idCube, std::make_unique<ACube>(pos.first, pos.second, "", _idCube)));
	_cubes[_idCube]->setRessources(_rs);
	_rendering.push_back(std::make_unique<ACube>(pos.first, pos.second, "./media/cube.jpg", _idCube));
	_idCube++;
}

void	Render::addItem(std::pair<float, float> pos, int type)
{
	_items.push_back(Item(pos.first, pos.second, _id, type));
	_rendering.push_back(std::make_unique<Item>(pos.first, pos.second, _id++, type));
}

void	Render::removeItem(std::pair<int, int> pos, int type)
{
	int i = 0;

	for (auto &it : _items) {
		if (std::round(it.getPos().first) == pos.first && std::round(it.getPos().second) == pos.second
			&& it.getItemType() == type) {
				_vectorToRemove.push_back(std::make_pair(it.getId(),
					it.getType()));
				_items.erase(_items.begin() + i);
				return;
		}
		i++;
	}
}

void	Render::addPlayer(Player player)
{
	int id = player.getId();
	std::string team = player.getTeam();

	if (id == 0)
		_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, 2332,
			"ID team level F  L  D  S  M P  T"
			, 0, id * LABELSIZE, 500, 50));
	if (_teams.find(team) == _teams.end())
		_teams.insert(std::make_pair(team, _idTeam++));
	std::cout << _allModels[_teams[team]] << std::endl;
	player.setModel(_allModels[_teams[team]]);
	player.setTexture(_allTextures[_teams[team]]);
	player.setScale(_allScales[_teams[team]]);
	_players.insert(std::make_pair(id, std::make_unique<Player>(player)));
	_rendering.push_back(std::make_unique<Player>(player));
	_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, id,
		std::to_string(id) + " " + team + " " + std::to_string(player.getLevel()) +
		std::to_string(player.getInventory()[0]) + " " +
		std::to_string(player.getInventory()[1]) + " " +
		std::to_string(player.getInventory()[2]) + " " +
		std::to_string(player.getInventory()[3]) + " " +
		std::to_string(player.getInventory()[4]) + " " +
		std::to_string(player.getInventory()[5]) + " " +
		std::to_string(player.getInventory()[6]),
		0, (id + 1) * LABELSIZE, 500, 50));
}

void	Render::updatePlayerPosition(int id, std::pair<int, int> coord, int orientation)
{
	// if (_players.find(id) == _players.end()) {
	// 	// _players.insert(std::make_pair(id, std::make_unique<Player>(coord.first, coord.second, id,)));
	// 		std::cout << "tototo" << std::endl;
	// }
	_players[id]->setPos(coord.first, coord.second);
	_players[id]->setRotation(tab[orientation - 1]);
	_rendering.push_back(std::unique_ptr<Player>(_players[id].get()));
}

void 	Render::updatePlayerOrientation(int id, std::pair<int, int> coord, int orientation)
{
	// if (_players.find(id) == _players.end()) {
	// 	_players.insert(std::make_pair(id, std::make_unique<Player>(coord.first, coord.second, id, "team")));
	// }
	_players[id]->setRotation(tab[orientation - 1]);
	_rendering.push_back(std::unique_ptr<Player>(_players[id].get()));
}

void 	Render::removePlayer(int id)
{
	_vectorToRemove.push_back(std::make_pair(id, Entity::PLAYER));
}

void	Render::updatePlayerLevel(int id, int level)
{
	
	_players[id]->setLevel(level);
	_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, id,
		std::to_string(id) + "\t" + _players[id]->getTeam() + "\t" +
		std::to_string(level) + " " + std::to_string(_players[id]->getInventory()[0]),
		0, (id + 1) * LABELSIZE, 500, 50));
}

void	Render::updatePlayerInventory(int id, std::array<int, 7> inventory)
{
	_players[id]->setInventory(inventory);
	_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, id,
		std::to_string(id) + "  " + _players[id]->getTeam() + " " + std::to_string(_players[id]->getLevel()) +
		" " + std::to_string(_players[id]->getInventory()[0]) + " " +
		std::to_string(_players[id]->getInventory()[1]) + " " +
		std::to_string(_players[id]->getInventory()[2]) + " " +
		std::to_string(_players[id]->getInventory()[3]) + " " +
		std::to_string(_players[id]->getInventory()[4]) + " " +
		std::to_string(_players[id]->getInventory()[5]) + " " +
		std::to_string(_players[id]->getInventory()[6]),
		0, (id + 1) * LABELSIZE, 500, 50));
}

void	Render::updatePlayerUseItem(int id, int type)
{
	_players[id]->removeInInventory(type);
	_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, id,
		std::to_string(id) + " " + _players[id]->getTeam() + " " + std::to_string(_players[id]->getLevel()) +
		" " + std::to_string(_players[id]->getInventory()[0]) + " " +
		std::to_string(_players[id]->getInventory()[1]) + " " +
		std::to_string(_players[id]->getInventory()[2]) + " " +
		std::to_string(_players[id]->getInventory()[3]) + " " +
		std::to_string(_players[id]->getInventory()[4]) + " " +
		std::to_string(_players[id]->getInventory()[5]) + " " +
		std::to_string(_players[id]->getInventory()[6]),
		0, (id + 1) * LABELSIZE, 500, 50));
}

void	Render::updatePlayerInventory(int id, int type, bool isRemove)
{
	if (isRemove == false)
		_players[id]->addInInventory(type);
	else
		_players[id]->removeInInventory(type);
	_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, id,
		std::to_string(id) + " " + _players[id]->getTeam() + " " + std::to_string(_players[id]->getLevel()) +
		" " + std::to_string(_players[id]->getInventory()[0]) + " " +
		std::to_string(_players[id]->getInventory()[1]) + " " +
		std::to_string(_players[id]->getInventory()[2]) + " " +
		std::to_string(_players[id]->getInventory()[3]) + " " +
		std::to_string(_players[id]->getInventory()[4]) + " " +
		std::to_string(_players[id]->getInventory()[5]) + " " +
		std::to_string(_players[id]->getInventory()[6]),
		0, (id + 1) * LABELSIZE, 500, 50));
}

std::vector<std::unique_ptr<IEntity>>	&Render::getRendering()
{
	return _rendering;
}

void	Render::clearUpdateEntities()
{
	for (auto &it : _rendering) {
		it.release();
	}
	_rendering.clear();
}

void	Render::clearRemoveEntities()
{
	_vectorToRemove.clear();
}

std::vector<std::pair<int, Entity>> &Render::getRemovedEntities()
{
	return (_vectorToRemove);
}

void	Render::updateLabelClick(std::pair<int, int> posMouseClick, int id)
{
	if (id >= 0 && _cubes.find(id) != _cubes.end()) {
		std::array<int, 7>	rs = _cubes[id]->getRessources();
		_rendering.push_back(std::make_unique<MenuItem>(Entity::LABEL, 34543,
		"id:" + std::to_string(id) +
		" food:" + std::to_string(rs[0]) +
		" linemate:" + std::to_string(rs[1]) +
		" deraumere:" + std::to_string(rs[2]) +
		" sibur:" + std::to_string(rs[3]) +
		" mendiane:" + std::to_string(rs[4]) +
		" phiras:" + std::to_string(rs[5]) +
		" thystame:" + std::to_string(rs[6])
		, 0, 950, 1920, 50));
	}
}

void	Render::clear()
{
	for (auto &it : _cubes) {
		_vectorToRemove.push_back(std::make_pair(it.second->getId(),
					it.second->getType()));
		it.second.release();
	}
	_cubes.clear();
	for (auto &it : _items) {
		_vectorToRemove.push_back(std::make_pair(it.getId(),
					it.getType()));
	}
	_items.clear();
	for (auto &it : _players) {
		_vectorToRemove.push_back(std::make_pair(it.second->getId(),
					it.second->getType()));
		it.second.release();
	}
	_players.clear();
}
