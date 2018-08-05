/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** ZappyClient
*/

#include "ZappyClient.hpp"

ZappyClient::ZappyClient(int ac, const char **av)
	:_id(-1), _team(""), _port(4242), _host("127.0.0.1"), _sock(nullptr), _player(nullptr)
{
	for (auto i = 1 ; i < ac ; i += 2) {
		if (*av[i] == '-' && av[i + 1])
			getFlag(std::string(av[i]), std::string(av[i + 1]));
		else if (*av[i] == '-')
			throw std::invalid_argument(std::string(av[i]) + ": Missing data.");
		else
			throw std::invalid_argument(std::string(av[i]) + ": Not a flag.");
	}
	if (!_team.size())
		throw std::invalid_argument(std::string("Missing team name."));
	else if (_port <= 1000)
		throw std::invalid_argument(std::string("Invalid port."));
	std::cout << "===  Init ok  ===" << std::endl;
	std::cout << "Team name: " << _team << std::endl;
	std::cout << "Host: " << _host << std::endl;
	std::cout << "Port: " << _port << std::endl;
	_sock = std::unique_ptr<Socket>(new Socket(_port, _host));
	_player = std::unique_ptr<ZappyPlayer>(new ZappyPlayer(_team));
	_sock->init();
	_sock->connection();
	_sock->send(_team + "\n");
	int answers = 0;
	while (answers < 3) {
		auto msg = _sock->receive();
		if (msg.size() > 0) {
			std::cout << "reçu du serveur à l'initialisation : size " << msg.size() <<std::endl;
			for (auto &i : msg)
				std::cout << i << std::endl;
		}
		answers += msg.size();
	}
}

void	ZappyClient::getFlag(const std::string &flag, const std::string &str)
{
	if (!flag.compare("-p")) {
		std::istringstream tmp(str);
		tmp >> _port;
	} else if (!flag.compare("-n")) {
		_team = str;
	} else {
		if (!flag.compare("-h"))
			_host = str;
		else
			throw std::invalid_argument(std::string("Invalid flag: '") + flag + "'.");
	}
}

ZappyClient::~ZappyClient()
{
}

void	ZappyClient::play()
{
//	std::vector<std::string> &msgs;
//	std::vector<std::string> &receive;
	std::vector<std::string> receive;
	std::vector<std::string> allReceive;
	std::queue<std::string> send;

	_sock->send("Look\n");
	_sock->receive();
	while (!_sock->checkEnd()) {
		receive.clear();
		allReceive.clear();
		while (!send.empty()) {
			_sock->send(send.front());
			while ((receive = _sock->receive()).empty());
			if (receive.front() == "dead")
				return  ;
			allReceive.push_back(receive.front());
			receive.pop_back();
			send.pop();
		}
		auto tmp = _player->think(allReceive); // si l'IA ne doit pas bouger, est ce que renvoyer un vector nul pour msg marche
		for (auto &i : tmp)
			send.push(i);
	}
	std::cout << "End of game\n";
}
