/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** guest file
*/

#include "Guest.hpp"

Guest::Guest(int fd)
	:AClient(fd)
{
}

Guest::~Guest()
{
}

static const command_s commandguest[] =
{
	{"msz", 3, &AClient::commandMsz},
	{"np", 2, &AClient::commandNp},
	{"mop", 3, &AClient::commandMop},
	{"pin", 3, &AClient::commandPin},
	{"plv", 3, &AClient::commandPlv},
	{"nt", 2, &AClient::commandNt},
	{"pto", 2, &AClient::commandPto},
	{"pso", 3, &AClient::commandPso},
	{"dp", 2, &AClient::commandDp},
	{"pui", 3, &AClient::commandPui},
	{"adi", 3, &AClient::commandAdi},
	{"", -1, NULL}
};

void 	Guest::createButtons()
{
	_render.addButton(BUTTON_ID, "Menu", std::make_pair(SCREEN_WIDTH / 2 - 150 , 50), std::make_pair(100, 50));
	_render.addButton(BUTTON_ID + 1, "Exit", std::make_pair(SCREEN_WIDTH / 2 + 50, 50), std::make_pair(100, 50));
}

void 	Guest::handleButtons(State &state, Actions actions, bool &init)
{
	if (actions.buttonPressed == BUTTON_ID) {
		state = State::INIT;
		init = true;
		_render.clear();
	}
	if (actions.buttonPressed == BUTTON_ID + 1)
		state = State::EXIT;
}

void 	Guest::calc(Actions actions)
{
	std::string string;

	_com.myRead(string);
	if (string.size())
		for (int i = 0; commandguest[i].cmd != ""; i++) {
			if (strncasecmp(commandguest[i].cmd.c_str(), string.c_str(), commandguest[i].len) == 0)
				((*this).*commandguest[i].ptr)(string);
		}
}