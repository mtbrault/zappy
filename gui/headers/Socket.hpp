/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** socket's header
*/

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <cstring>
# include <iostream>
# include <string>

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>

class Socket {
	public:
		Socket(std::string type);
		~Socket();
		int		connection(std::string, std::string);
		int 	getFd() const noexcept { return _fd; }
	private:
		int		_fd;
};

#endif /* !SOCKET_HPP_ */
