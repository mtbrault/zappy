/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** class Connection
*/

#include "Connection.hpp"

Connection::Connection()
{
	_socket = new Socket("TCP");
}

Connection::~Connection()
{
}

std::vector<std::unique_ptr<IEntity>> &Connection::createConnectionWindow()
{
	int x = 1920 / 2 - 200;
	_items.clear();
	_items.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 1, "IP Address", x, 120, 400, 70)));
	_items.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 2, "127.0.0.1" , x, 190, 400, 70)));
	_items.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 3, "Port", x, 320, 400, 70)));
	_items.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 4, "4242" , x, 390, 400, 70)));
	_items.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 5, "Connect", x, 500, 400, 70)));
	return _items;
}

void 	Connection::newSocket(std::string type)
{
	_socket = new Socket(type);
}

void 	Connection::closeSocket()
{
	close(_fd);
}

bool 	Connection::click(Actions &actions)
{
	if (actions.buttonPressed == 5)
		return (true);
	return (false);
}

std::vector<std::unique_ptr<IEntity>> &Connection::getBadConnectionWindow()
{
	_updateItems.push_back(std::make_unique<MenuItem>(Entity::BUTTON, 5, "./media/red.png"));
	return _updateItems;
}

int 	Connection::connect(std::string ip, std::string port)
{
	std::replace(ip.begin(), ip.end(), 'y', '7');
	std::replace(ip.begin(), ip.end(), 'Y', '7');
	try {
		_socket->connection(ip, port);
		_fd = _socket->getFd();
	} catch (const std::exception &e) {
		std::cout << "An error occured";
		std::cout << "You cannot connect with these informations" << std::endl;
		return false;
	}
	return true;
}