/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** abstract class for client
*/

#include "AClient.hpp"

AClient::AClient(int fd)
	:_com(fd)
{
	std::srand(std::time(nullptr));
}

AClient::~AClient()
{
}

void 	AClient::setFd(int fd)
{
	_com.setFd(fd);
}

std::pair<int, int>	AClient::getMapSize()
{
	std::string tmp;
	int X;
	int Y;

	std::string size;
	while(_com.myRead(size) == false);
	std::istringstream iss(size);
	iss >> tmp >> X >> Y;
	return (std::make_pair(X, Y));
}

std::vector<std::unique_ptr<IEntity>> &AClient::getRendering()
{
	return (_render.getRendering());
}

void	AClient::clearUpdateEntities()
{
	_render.clearUpdateEntities();
}

void	AClient::clearRemoveEntities()
{
	_render.clearRemoveEntities();
}

std::vector<std::pair<int, Entity>> &AClient::getRemovedEntities()
{
	return (_render.getRemovedEntities());
}

void	AClient::commandNp(std::string message)
{
	std::istringstream	iss(message);
	std::array<int, 7>	rsscs;
	std::string tmp;
	std::string team;
	int id;
	int X;
	int Y;

	iss >> tmp >> id >> X >> Y >> rsscs[0] >> rsscs[1] >> rsscs[2] >> rsscs[3]
		>> rsscs[4] >> rsscs[5] >> rsscs[6] >> team;
	Player		player(X, Y, id, team);
	player.setInventory(rsscs);
	_render.addPlayer(player);
}

void	AClient::commandDp(std::string message)
{
	std::istringstream	iss(message);
	std::string tmp;
	int id;

	iss >> tmp >> id;
	_render.removePlayer(id);
}

void	AClient::commandNt(std::string message)
{
	std::istringstream iss(message);
	std::string tmp;
	std::array<int, 7> rs;
	int id;
	float X;
	float Y;

	iss >> tmp >> X >> Y;
	iss >> rs[0] >> rs[1] >> rs[2] >> rs[3] >> rs[4] >> rs[5] >> rs[6];
	_render.addCube(std::make_pair(static_cast<int>(X), static_cast<int>(Y)), rs);
	float xrand = 0.3;
	float yrand = 0.3;
	for (int i = 0; i < 7; i++)
		for (int it = 0; it < rs[i]; it++) {
			_render.addItem(std::make_pair(X -0.5 + xrand, Y -0.5 + yrand), i);
			if (xrand < 0.5)
				xrand = xrand + 0.2;
			else {
				yrand = yrand + 0.2;
				xrand = 0.2;
			}
		}
}

void	AClient::commandMop(std::string message)
{
	std::istringstream iss(message);
	std::string tmp;
	int id;
	int X;
	int Y;
	int O;

	iss >> tmp >> id >> X >> Y >> O;
	_render.updatePlayerPosition(id, std::make_pair(X, Y), O);
}

void 	AClient::commandPin(std::string inventory)
{
	std::string tmp;
	int id;
	std::array<int, 7> in;

	std::istringstream iss(inventory);
	iss >> tmp >> id >> tmp >> tmp >> in[0] >> in[1]
		>> in[2] >> in[3] >> in[4] >> in[5] >> in[6];
	_render.updatePlayerInventory(id, in);
}

void 	AClient::commandPlv(std::string level)
{
	std::string tmp;
	int 	id;
	int 	L;

	std::istringstream iss(level);
	iss >> tmp >> id >> L;
	_render.updatePlayerLevel(id, L);
}

void 	AClient::commandPno(std::string orientation)
{
	std::istringstream iss(orientation);
	std::string	tmp;
	int id;
	int X;
	int Y;
	int O;

	iss >> tmp >> id >> X >> Y >> O;
	_render.updatePlayerOrientation(id, std::make_pair(X, Y), O);
}

void 	AClient::commandPto(std::string object)
{
	std::istringstream iss(object);
	std::string	tmp;
	int id;
	int X;
	int Y;
	int type;

	iss >> tmp >> id >> X >> Y >> type;
	_render.updatePlayerInventory(id, type, false);
	_render.removeItem(std::make_pair(X, Y), type);
}

void 	AClient::commandPso(std::string object)
{
	std::istringstream iss(object);
	std::string	tmp;
	int id;
	int type;
	int X;
	int Y;

	iss >> tmp >> id >> X >> Y >> type;
	_render.updatePlayerInventory(id, type, true);
	_render.addItem(std::make_pair(X, Y), type);
}

void 	AClient::commandPui(std::string object)
{
	std::istringstream iss(object);
	std::string	tmp;
	int id;
	int type;

	iss >> tmp >> id >> type;
	_render.updatePlayerUseItem(id, type);
}

void 	AClient::commandAdi(std::string object)
{
	std::istringstream iss(object);
	std::string	tmp;
	int type;
	int X;
	int Y;

	iss >> tmp >> type >> X >> Y;
	_render.addItem(std::make_pair(X, Y), type);
}

void 	AClient::commandMsz(std::string mapsize)
{
	std::istringstream iss(mapsize);
	std::string tmp;
	int x;
	int y;

	iss >> tmp >> x >> y;
	_mapsize = std::make_pair(x, y);
}