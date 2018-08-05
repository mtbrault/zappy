/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** class Login
*/

#include "Login.hpp"

Login::Login(int fd)
	: _com(fd)
{
}

Login::Login()
{
}

Login::~Login()
{
}

#define SCREEN_WIDTH 1920

std::vector<std::unique_ptr<IEntity>> &Login::createLoginWindow()
{
	int x = SCREEN_WIDTH / 2 - 50;
	_items.push_back(std::make_unique<MenuItem>(Entity::BUTTON, 1, "Guest", 250, 500, 400, 70));
	_items.push_back(std::make_unique<MenuItem>(Entity::LABEL, 2, "or", 750, 500, 70, 70));
	_items.push_back(std::make_unique<MenuItem>(Entity::LABEL, 3, "Login", x, 120, 400, 70));
	_items.push_back(std::make_unique<MenuItem>(Entity::INPUT, 4, "" , x, 190, 400, 70));
	_items.push_back(std::make_unique<MenuItem>(Entity::LABEL, 5, "Password", x, 320, 400, 70));
	_items.push_back(std::make_unique<MenuItem>(Entity::INPUT, 6, "" , x, 390, 400, 70, true));
	_items.push_back(std::make_unique<MenuItem>(Entity::BUTTON, 7, "Connect", x, 500, 400, 70));
	return _items;
}

bool Login::connect(std::string userName, std::string passWord)
{
	std::string response;

	_com.myWrite("login " + userName + "\n");
	_com.myWrite("pass " + passWord + "\n");
	while (_com.myRead(response) == false);
	if (std::stoi(response) == 200)
		return (true);
	_updateItems.push_back(std::make_unique<MenuItem>(Entity::BUTTON, 7, "./media/red.png"));
	return (false);
}

void Login::pokeServer()
{
	std::string	response;

	while (_com.myRead(response) == false);
	_com.myWrite("GUI\n");
}

void Login::setFd(int fd)
{
	_com.setFd(fd);
}

bool 	Login::clickAdmin(Actions &actions)
{
	if 	(actions.buttonPressed == 7)
		return (true);
	return (false);
}

bool	Login::clickGuest(Actions &actions)
{
	if 	(actions.buttonPressed == 1)
		return (true);
	return (false);
}