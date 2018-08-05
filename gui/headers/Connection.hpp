/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
	#define CONNECTION_HPP_

# include "IEntity.hpp"
# include "MenuItem.hpp"
# include "Socket.hpp"
# include "Actions.hpp"
# include <memory>
# include <algorithm>

class Connection {
	public:
		Connection();
		~Connection();
		void 	newSocket(std::string type);
		void 	closeSocket();
		bool 	click(Actions &actions);
		int 	connect(std::string, std::string);
		int 	getFd() const { return _fd; }
		std::vector<std::unique_ptr<IEntity>> &createConnectionWindow();
		std::unique_ptr<IEntity> &getIpId() { return _items[1]; };
		std::unique_ptr<IEntity> &getPortId() { return _items[3]; };
		std::vector<std::unique_ptr<IEntity>> &getBadConnectionWindow();
	private:
		std::vector<std::unique_ptr<IEntity>> 	_items;
		std::vector<std::unique_ptr<IEntity>> 	_updateItems;
		std::string 							_ipAddress;
		std::string 							_port;
		Socket									*_socket;
		int 									_fd;
};

#endif /* !CONNECTION_HPP_ */
