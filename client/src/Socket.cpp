/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** socket file
*/

#include "Socket.hpp"

Socket::Socket(int port, const std::string &machineName, const std::string &type)
	:  _machineName(machineName), _type(type), _port(port), _end(false)
{
}

int	Socket::init()
{
	struct protoent *proto;

	proto = getprotobyname(_type.c_str());
	if (!proto)
		return -1;
	_servFd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (_servFd == -1) {
		std::cerr << "socket has failed" << std::endl;
		return -1;
	}
	return 0;
}

Socket::~Socket() noexcept
{
	close(_servFd);
}

void	Socket::connection()
{
	struct sockaddr_in	s_in;

	std::memset(&s_in, '0', sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(_port);
	if (inet_pton(AF_INET, _machineName.c_str(), &s_in.sin_addr) <= 0)
		throw std::runtime_error("Inet_pton could not resolve hostname.");
	if (connect(_servFd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
		throw std::runtime_error("Could not connect.");
}

void	Socket::getEntireMessage(int fdServ, fd_set fdRead, std::string &entireMessage) noexcept
{
	char *buff;
//	int r;

	if (FD_ISSET(fdServ, &fdRead)) {
		//std::cout << "IFSET\n";
		// while (get_next_line(fdServ, &buff)) {
		// 	entireMessage += std::string(buff);
		// }
		if (get_next_line(fdServ, &buff) < 0)
			_end = true;
		entireMessage += buff;
		// while ((r = read(fdServ, buff, 1023)) == 1023) {
		// 	buff[r - 1] = '\0';
		// 	entireMessage = entireMessage + std::string(buff);
		// }
		// if (r <= 0) {
		// 	std::cout << "Connection closed." << std::endl;
		// 	_end = true;
		// 	return ;
		// }
		// std::cout << "Aucun pb dans la reception de msg" << std::endl;
		// buff[r - 1] = '\0';
		// entireMessage = entireMessage + std::string(buff);
	}
}

void	Socket::parseMessage(std::string &entireMessage, std::vector<std::string> &messages) noexcept
{
	std::string delimiter = "\n";
	std::size_t pos = 0;
	std::string token;

	while ((pos = entireMessage.find(delimiter)) != std::string::npos) {
		token = entireMessage.substr(0, pos);
		messages.push_back(token);
		entireMessage.erase(0, pos + delimiter.length());
	}
	if (messages.empty() && entireMessage != "") {
		messages.push_back(entireMessage);
	}
}

std::vector<std::string> Socket::receive()
{
	fd_set fdRead;
	std::string entireMessage("");
//	struct timeval timer;
	char *buff = NULL;

	FD_ZERO(&fdRead);
	FD_SET(_servFd, &fdRead);
	// timer.tv_sec = 0;
	// timer.tv_usec = 1;
	std::cout << "before\n";
	select(_servFd + 1, &fdRead, NULL, NULL, NULL);//&timer);
	std::cout << "after\n";
	_messages.clear();
	if (FD_ISSET(_servFd, &fdRead)) {
		if (get_next_line(_servFd, &buff) < 0)
			_end = true;
		std::cout << "Receive : " << buff  << std::endl;
		_messages.push_back(buff);
	}
//	getEntireMessage(_servFd, fdRead, entireMessage);
//	parseMessage(entireMessage, _messages);
	return _messages;
}

//void	Socket::send(const std::vector<std::string> &vec)
void	Socket::send(std::string str)
{
//	for (auto &it : vec) {
	std::cout << "Send " << str.c_str();
	write(_servFd, str.c_str(), str.size());//+ 1);
//	}
}

bool	Socket::checkEnd() const
{
	return (_end);
}