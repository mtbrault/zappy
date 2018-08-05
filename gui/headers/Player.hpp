/*
** EPITECH PROJECT, 2018
** player
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

#include <memory>
#include <array>
#include <iostream>
#include "Item.hpp"
#include "AEntity.hpp"
#include "Player.hpp"

class Player : public AEntity {
public:
	Player(int, int, int, std::string);
	Player(const Player&);
	~Player() {};
	void		poke();
	bool		isAlive() const;
	void		setAlive(bool);
	pairUC		getPos() const;
	int			getPower() const;
	void		setPos(float x, float y);
	void		setPos(int x, int y);
	int			getLevel() const;
	void		setLevel(int);
	void		setInventory(std::array<int, 7>);
	float		getRotation() const;
	void		setRotation(int);
	std::string	getModel() const;
	std::string	getTexture() const;
	std::string	getTeam() const;
	float		getScale() const;
	void		setModel(std::string);
	void		setTexture(std::string);
	void		setScale(float);
	void		removeInInventory(int);
	void		addInInventory(int);
	std::array<int, 7>		getInventory() const;

private:

	int 							_number;
	int 							_rotation;
	int								_level;
	int								_indexTeam;
	float							_speed;
	float							_scale;
	std::string						_team;
	std::string						_model;
	std::string						_texture;
	std::array<int, 7>				_ressources;
};

#endif /* !PLAYER_HPP_ */
