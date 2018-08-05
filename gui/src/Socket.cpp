/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** socket file
*/

#include "Socket.hpp"

Socket::Socket(std::string type)
{
	struct protoent *proto;

	proto = getprotobyname(type.c_str());
	if (!proto)
		throw(std::exception());
	_fd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (_fd == -1) {
		std::cerr << "socket has failed" << std::endl;
		throw(std::exception());
	}
}

Socket::~Socket()
{
	close(_fd);
}

int	Socket::connection(std::string ip, std::string port)
{
	struct sockaddr_in	s_in;

	std::memset(&s_in, '0', sizeof(s_in));
	if (inet_pton(AF_INET, ip.c_str(), &s_in.sin_addr) <= 0)
		throw (std::exception());
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(std::stoi(port));
	if (connect(_fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
		throw (std::exception());
	return _fd;
}