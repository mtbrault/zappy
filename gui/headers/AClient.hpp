/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** abstract class for client
*/

#ifndef ACLIENT_HPP_
	#define ACLIENT_HPP_

# include <sstream>
# include <utility>
# include <sstream>
# include <cstdlib>
# include <ctime>
# include <strings.h>
# include <functional>
# include "Render.hpp"
# include "Actions.hpp"
# include "Communication.hpp"
# include "State.hpp"
# include "Defines.hpp"

class AClient {
	public:
		AClient(int);
		~AClient();
		void 	init();
		void	calc();
		virtual void 	createButtons() = 0;
		virtual void 	handleButtons(State &, Actions, bool &) = 0;
		void 	setFd(int fd);
		std::pair<int, int>	getMapSize();
		void 	setPlayersID();
		void 	clearUpdateEntities();
		void 	clearRemoveEntities();
		std::vector<std::unique_ptr<IEntity>>	&getRendering();
		std::vector<std::pair<int, Entity>> 	&getRemovedEntities();

		void 	setIp(std::string ip) { _ip = ip; }
		void 	setPort(std::string port) { _port = port; }

		void 	commandNp(std::string);
		void 	commandDp(std::string);
		void 	commandMop(std::string);
		void 	commandPin(std::string);
		void 	commandPlv(std::string);
		void	commandPno(std::string);
		void	commandNt(std::string);
		void	commandPto(std::string);
		void	commandMsz(std::string);
		void	commandPso(std::string);
		void	commandPui(std::string);
		void	commandAdi(std::string);

	protected:
		std::vector<int> 	_ids;
		std::string			_port;
		std::string 		_ip;
		Render 				_render;
		Com 				_com;
		std::pair<int, int>	_mapsize;
};

struct command_s
{
	std::string cmd;
	int 		len;
	void		(AClient::*ptr)(std::string);
};

#endif /* !ACLIENT_HPP_ */
