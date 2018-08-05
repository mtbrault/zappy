/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** guest's header
*/

#ifndef GUEST_HPP_
	#define GUEST_HPP_

# include "Actions.hpp"
# include "AClient.hpp"

class Guest : public AClient {
	public:
		Guest(int);
		~Guest();
		void 	calc(Actions);
		void 	createButtons() final;
		void 	handleButtons(State &, Actions, bool &) final;

};

#endif /* !GUEST_HPP_ */
