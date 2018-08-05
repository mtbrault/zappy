/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Rendering
*/

#ifndef RENDER_HPP_
	#define RENDER_HPP_

# include <utility>
# include <vector>
# include <array>
# include <utility>
# include <memory>
# include <cmath>
# include "ACube.hpp"
# include "Player.hpp"
# include "MenuItem.hpp"
# include "Defines.hpp"

# define NBMODELS 3
# define LABELSIZE 50

class Render {
	public:
		Render();
		~Render();
		
		void	addButton(int id, std::string text, std::pair<int, int> pos, std::pair<int, int> size);
		void	addPlayer(Player);
		void	addCube(std::pair<int, int>, std::array<int, 7>);
		void	addItem(std::pair<float, float>, int);

		void	updatePlayerLevel(int, int);
		void	updatePlayerInventory(int, std::array<int, 7>);
		void	updatePlayerPosition(int, std::pair<int, int>, int);
		void	updatePlayerOrientation(int id, std::pair<int, int>, int);
		void	updatePlayerInventory(int, int, bool = false);

		void	removeItem(std::pair<int, int>, int);
		void	removePlayer(int);

		void	clearUpdateEntities();
		void	clearRemoveEntities();

		std::vector<std::pair<int, Entity>> 	&getRemovedEntities();
		std::vector<std::unique_ptr<IEntity>>	&getRendering();

		void	updateLabelClick(std::pair<int, int>, int);

		void	clear();

		void	updatePlayerUseItem(int, int);

	private:
		int										_id;
		int										_idCube;
		int										_idTeam;
		std::pair<int, int>						_mapSize;
		std::map<int, std::unique_ptr<Player>>	_players;
		std::vector<Item>						_items;
		std::map<std::string, int>				_teams;
		std::map<int, std::unique_ptr<ACube>>	_cubes;
		std::map<int, std::unique_ptr<IEntity>>	_buttons;
		std::vector<std::unique_ptr<IEntity>>	_rendering;
		std::vector<std::pair<int, Entity> > 	_vectorToRemove;
		std::map<int, std::string>				_allModels;
		std::map<int, std::string>				_allTextures;
		std::map<int, float>					_allScales;
};

#endif /* !RENDER_HPP_ */
