/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Login
*/

#ifndef LOGIN_HPP_
	#define LOGIN_HPP_

# include "IEntity.hpp"
# include "MenuItem.hpp"
# include "Communication.hpp"
# include "Actions.hpp"
# include <memory>

class Login {
	public:
		Login();
		Login(int);
		~Login();
		void setFd(int);
		std::vector<std::unique_ptr<IEntity>> &createLoginWindow();
		std::vector<std::unique_ptr<IEntity>> &getUpdateEntities() {return _updateItems;};
		bool connect(std::string, std::string);
		void pokeServer();
		bool clickAdmin(Actions &actions);
		bool clickGuest(Actions &actions);
		std::unique_ptr<IEntity> &getLoginId() { return _items[3]; };
		std::unique_ptr<IEntity> &getPassId() { return _items[5]; };

		void 			setIp(std::string ip) { _ip = ip; }
		void 			setPort(std::string port) { _port = port; }
		std::string 	getIp() const { return  _ip; }
		std::string 	getPort() const { return _port; }

	private:
		std::vector<std::unique_ptr<IEntity>>	_items;
		std::vector<std::unique_ptr<IEntity>>	_updateItems;
		std::string _ip;
		std::string _port;
		Com										_com;
};

#endif /* !LOGIN_HPP_ */
