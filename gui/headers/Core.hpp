/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** core's header
*/

#ifndef CORE_HPP_
	#define CORE_HPP_

# include <iostream>
# include "Socket.hpp"
# include "IrrLib.hpp"
# include "Login.hpp"
# include "Connection.hpp"
# include "IEntity.hpp"
# include "Communication.hpp"
# include "Guest.hpp"
# include "Admin.hpp"
# include "State.hpp"
# include "Defines.hpp"

class Core {
	public:
		Core();
		~Core() = default;
		void	coreInit();
		void	coreLogin();
		void	coreGuest();
		void	coreAdmin();
		void 	coreLoading();
		void	loop();

	private:
		bool 			_init;
		IrrLib 			_lib;
		Actions 		_act;
		State			_state;

		Login			_login;
		Connection 		_connection;
		std::string		_command;
		Guest 			_guest;
		Admin 			_admin;
};

#endif /* !CORE_HPP_ */
