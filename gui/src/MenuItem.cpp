/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** MenuItem implementation
*/

#include "MenuItem.hpp"

MenuItem::MenuItem(std::string text)
	: _stateTexture(false), _texture(std::string()), _text(text), _selected(false)
{
}

MenuItem::MenuItem(Entity type, int id, std::string text, ui x, ui y, ui lenght, ui height, bool isPasswordBox)
	: _stateTexture(false), _texture(std::string()), _type(type), _id(id), _text(text),_coord(x, y),
		_size(lenght, height), _isPasswordBox(isPasswordBox)
{

}

MenuItem::MenuItem(Entity type, int id, std::string texture)
	: _stateTexture(true), _texture(texture), _type(type), _id(id)
{
}

void MenuItem::setCoord(unsigned int x, unsigned int y)
{
	_coord = std::make_pair(x, y);
}

void MenuItem::setSize(unsigned int x, unsigned int y)
{
	_size = std::make_pair(x, y);
}

bool MenuItem::isPasswordBox() const
{
	return _isPasswordBox;
}