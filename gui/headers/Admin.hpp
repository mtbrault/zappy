/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** admin's header
*/

#ifndef ADMIN_HPP_
	#define ADMIN_HPP_

# include "AClient.hpp"
# include "Actions.hpp"
# include "signal.h"

class Admin : public AClient {
	public:
		Admin(int);
		~Admin();
		void 	calc(Actions actions, int click);
		void 	createButtons() final;
		void 	handleButtons(State &, Actions, bool &) final;
	private:
		std::vector<pid_t>	_iasPids;
};

#endif /* !ADMIN_HPP_ */
