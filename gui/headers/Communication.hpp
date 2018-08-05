/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** communication's header
*/

#ifndef COMMUNICATION_HPP_
	#define COMMUNICATION_HPP_

# include <iostream>
# include <unistd.h>
# include "get_next_line.hpp"

class Com
{
public:
	Com(int fd);
	Com();
	~Com();
	std::string	getMsg();
	void		setFd(int);
	bool		myRead(std::string &toRead);
	void 		myWrite(std::string toWrite);
private:
	int 	_fd;
};



#endif /* !COMMUNICATION_HPP_ */
