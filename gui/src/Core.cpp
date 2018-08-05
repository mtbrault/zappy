/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** core cpp
*/

#include "Core.hpp"
#include <string>
#include <fstream>

Core::Core()
	:_lib(_act), _state(State::INIT), _guest(-1), _admin(-1), _init(true)
{
	std::cout << "Core Initialized" << std::endl;
}

void Core::coreInit()
{
	if (_init == true) {
		_lib.cleanMenu();
		_lib.initMenu(_connection.createConnectionWindow());
		_connection.closeSocket();
		_connection.newSocket("TCP");
		_init = false;
	}
	if (_connection.click(_act)) {
		if (_connection.connect(_lib.getInputText(_connection.getIpId()), _lib.getInputText(_connection.getPortId()))) {
			_login.setFd(_connection.getFd());
			_login.setIp(_lib.getInputText(_connection.getIpId()));
			_login.setPort(_lib.getInputText(_connection.getPortId()));
			_lib.cleanMenu();
			_lib.initMenu(_login.createLoginWindow());
			_login.pokeServer();
			_state = State::LOGIN;
		} else {
			_lib.updateEntities(_connection.getBadConnectionWindow());
		}
	}
}

void 	Core::coreLogin()
{
	if (_login.clickAdmin(_act)) {
		if (_login.connect(_lib.getInputText(_login.getLoginId()), _lib.getInputText(_login.getPassId()))) {
			_admin.setFd(_connection.getFd());
			_admin.setIp(_login.getIp());
			_admin.setPort(_login.getPort());
			_lib.cleanMenu();
			_admin.createButtons();
			_lib.updateEntities(_admin.getRendering());
			_state = State::ADMIN;
		} else
			_lib.updateEntities(_login.getUpdateEntities());
	} else if (_login.clickGuest(_act)) {
		if (_login.connect("guest", "guest")) {
			_guest.setFd(_connection.getFd());
			_lib.cleanMenu();
			_guest.createButtons();
			_lib.updateEntities(_guest.getRendering());
			_state = State::GUEST;
		}
	}
}

void 	Core::coreGuest()
{
	_guest.clearUpdateEntities();
	_guest.clearRemoveEntities();
	_guest.calc(_act);
	_guest.handleButtons(_state, _act, _init);
	if (_state == State::EXIT)
		_connection.closeSocket();
	_lib.updateEntities(_guest.getRendering());
	_lib.removeEntities(_guest.getRemovedEntities());
}

void 	Core::coreAdmin()
{
	int idNodeClicked = -1;

	_admin.clearUpdateEntities();
	_admin.clearRemoveEntities();
	if (_act.click)
		idNodeClicked = _lib.handleClickColision();
	_admin.calc(_act, idNodeClicked);
	_admin.handleButtons(_state, _act, _init);
	if (_state == State::EXIT)
		_connection.closeSocket();
	_lib.updateEntities(_admin.getRendering());
	_lib.removeEntities(_admin.getRemovedEntities());
}

void	Core::loop()
{
	while (_lib.getRun() && _state != State::EXIT) {
		_act = _lib.getActions();
		if (_state == State::INIT)
			coreInit();
		else if (_state == State::LOGIN)
			coreLogin();
		else if (_state == State::GUEST)
			coreGuest();
		else if (_state == State::ADMIN)
			coreAdmin();
		_lib.draw();
	}
}