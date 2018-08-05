/*
** EPITECH PROJECT, 2018
** Player
** File description:
** player
*/

#include "Player.hpp"

Player::Player(int x, int y, int id, std::string team)
	: _level(1), _team(team)
{
	_x = x;
	_y = y;
	_id = id;
	_alive = true;
	_ressources.fill(0);
	_ressources[0] = 10;
	_type = Entity::PLAYER;
}

Player::Player(const Player &player)
{
	_x = player.getPos().first;
	_y = player.getPos().second;
	_id = player.getId();
	_alive = true;
	_ressources = player.getInventory();
	_level = player.getLevel();
	_team = player.getTeam();
	_scale = player.getScale();
	_model = player.getModel();
	_texture = player.getTexture();
	_type = Entity::PLAYER;
}
void 	Player::poke()
{
}

bool 	Player::isAlive() const
{
	return (_alive);
}

void 	Player::setAlive(bool alive)
{
	_alive = alive;
}

pairUC	Player::getPos() const
{
	return std::make_pair(_x, _y);
}

void	Player::setPos(float x, float y)
{
	_x = x;
	_y = y;
}

void	Player::setPos(int x, int y)
{
	_x = x;
	_y = y;
}

void Player::setRotation(int rotation)
{
	_rotation = rotation;
}

float	Player::getRotation() const
{
	return _rotation;
}

void	Player::setLevel(int level)
{
	_level = level;
}


int		Player::getLevel() const
{
	return _level;
}

void	Player::setInventory(std::array<int, 7> inventory)
{
	_ressources = inventory;
}

std::array<int, 7>	Player::getInventory() const
{
	return _ressources;
}

void		Player::addInInventory(int type)
{
	_ressources[type]++;
}

void		Player::removeInInventory(int type)
{
	_ressources[type]--;
}

std::string		Player::getTeam() const
{
	return _team;
}


std::string		Player::getModel() const
{
	return _model;
}

std::string		Player::getTexture() const
{
	return _texture;
}

float	Player::getScale() const
{
	return _scale;
}

void		Player::setModel(std::string model)
{
	_model = model;
}

void		Player::setTexture(std::string texture)
{
	_texture = texture;
}

void	Player::setScale(float scale)
{
	_scale = scale;
}