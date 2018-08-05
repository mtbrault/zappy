/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** socket's header
*/

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

// to remove
# include "get_next_line.h"

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>

# include <vector>
# include <string>
# include <exception>
# include <cstring>
# include <iostream>
# include <string>

class Socket {
public:
	Socket(int port = 4242, const std::string &machine = "127.0.0.1", const std::string &type = "TCP");
	~Socket();

	void connection();
	int init();
	std::vector<std::string> receive();
	void send(std::string );
	bool	checkEnd() const;

private:
	void	parseMessage(std::string &, std::vector<std::string> &) noexcept;
	void	getEntireMessage(int fdServ, fd_set fdRead, std::string &) noexcept;

	std::vector<std::string> _messages;
	std::string _machineName;
	std::string _type;
	int _port;
	int _servFd;
	bool _end;
};

#endif /* !SOCKET_HPP_ */
