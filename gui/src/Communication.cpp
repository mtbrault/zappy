/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Communication file
*/

#include "Communication.hpp"

Com::Com(int fd)
	:_fd(fd)
{
}

Com::Com()
{
}

Com::~Com()
{
}

void Com::setFd(int fd)
{
	_fd = fd;
}

std::string	Com::getMsg()
{
	char 	*buf;
	int 	r;

	r = get_next_line(_fd, &buf);
	if (r > 0) {
		return (std::string(buf));
	} else {
		throw (std::exception());
		std::cout << "The server has closed unexpectedly" << std::endl;
	}
}

bool Com::myRead(std::string &toRead)
{
	fd_set 	fd_read;
 	struct timeval tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0.1;
	FD_ZERO(&fd_read);
	FD_SET(_fd, &fd_read);
	select(_fd + 1, &fd_read, NULL, NULL, &tv);
	if (FD_ISSET(_fd, &fd_read)) {
		toRead = getMsg();
		return (true);
	}
	return (false);
}

void Com::myWrite(std::string toWrite)
{
	write(_fd, toWrite.c_str(), toWrite.size());
}