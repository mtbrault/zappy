/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** ZappyClient header
*/

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

# include <fstream>
# include <exception>
# include <memory>
# include <iostream>
# include <sstream>
# include <ZappyPlayer.hpp>
# include "Socket.hpp"

class	ZappyClient {
public:
	ZappyClient(int ac, const char **av);
	~ZappyClient();
	void	play();

private:
	void	getFlag(const std::string &, const std::string &);

	int			_id;
	std::string		_team;
	int			_port;
	std::string		_host;
	std::unique_ptr<Socket>	_sock;
	std::unique_ptr<ZappyPlayer> _player;
};

#endif /* !CLIENT_HPP_ */
