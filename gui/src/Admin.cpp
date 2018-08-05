/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** admin file
*/

#include "Admin.hpp"
#include "Execute.hpp"

Admin::Admin(int fd)
	:AClient(fd)
{
}

Admin::~Admin()
{
	for (auto &i : _iasPids) {
//		int ret = kill(i, SIGINT);
	}
}

static const command_s commandadmin[] =
{
	{"msz", 3, &AClient::commandMsz},
	{"np", 2, &AClient::commandNp},
	{"mop", 3, &AClient::commandMop},
	{"pin", 3, &AClient::commandPin},
	{"plv", 3, &AClient::commandPlv},
	{"nt", 2, &AClient::commandNt},
	{"pto", 2, &AClient::commandPto},
	{"", -1, NULL}
};

void 	Admin::createButtons()
{
	_render.addButton(BUTTON_ID, "Menu", std::make_pair(SCREEN_WIDTH / 2 - 300 , 50), std::make_pair(100, 50));
	_render.addButton(BUTTON_ID + 1, "Exit", std::make_pair(SCREEN_WIDTH / 2 + 200, 50), std::make_pair(100, 50));
	_render.addButton(BUTTON_ID + 2, "Add IA", std::make_pair(SCREEN_WIDTH / 2 - 70, 50), std::make_pair(140, 50));
}

static char* get_str(std::string str)
{
	char *writable = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0';
	return writable;
}

void 	Admin::handleButtons(State &state, Actions actions, bool &init)
{
	int pid;

	if (actions.buttonPressed == BUTTON_ID) {
		state = State::INIT;
		init = true;
		_render.clear();
	} else if (actions.buttonPressed == BUTTON_ID + 1) {
		state = State::EXIT;
	} else if (actions.buttonPressed == BUTTON_ID + 2) {
		actions.buttonPressed = 0;
		if ((pid = fork()) == 0) {
			char *const args[] = {get_str("./../client/zappy_ai") , get_str("-n"), get_str("toto"), get_str("-p"), get_str(_port), get_str("-h"), get_str(_ip)};
			Execute newexecute("./../client/zappy_ai", args);
			std::cout << "IA created" << std::endl;
			while (true);
		} else
			_iasPids.push_back(pid);
	}
}

void 	Admin::calc(Actions actions, int click)
{
	std::string string;

	_com.myRead(string);
	if (string.size())
		for (int i = 0; commandadmin[i].cmd != ""; i++) {
			if (strncasecmp(commandadmin[i].cmd.c_str(), string.c_str(), commandadmin[i].len) == 0)
				((*this).*commandadmin[i].ptr)(string);
		}
	if (actions.click)
		_render.updateLabelClick(actions.lastMouseClick, click);
}