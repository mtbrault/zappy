/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Irrlib header
*/

#ifndef IRRLIB_HPP_
	#define IRRLIB_HPP_

# include <irrlicht.h>
#include <functional>
# include "MyEventReceiver.hpp"

# include "IEntity.hpp"
# include "MyEventReceiver.hpp"
# include "Actions.hpp"
# include "MenuItem.hpp"
# include "Player.hpp"
# include "ACube.hpp"
# include "ASphere.hpp"
# include "Music.hpp"
# include "Defines.hpp"

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class IrrLib {
	public:
		IrrLib(Actions &);
		~IrrLib();
		void addCube(std::unique_ptr<IEntity>&);
		void addPlayer(std::unique_ptr<IEntity> &);
		void addSphere(std::unique_ptr<IEntity> &entity);
		void updateSphere(std::unique_ptr<IEntity> &entity);
		
		Actions getActions();
		bool getRun();
		void createPlane(pairUC &size);
		void updateEntities(std::vector<std::unique_ptr<IEntity>>&);
		void removeEntities(std::vector<std::pair<int, Entity> > &vectorToRemove);
		void removeCube(int);
		// void affMenuItems(std::vector<MenuItem>&);
		void addButton(std::unique_ptr<IEntity>&);
		void updateButton(std::unique_ptr<IEntity> &entity);
		
		void addStaticText(std::unique_ptr<IEntity>&);
		void addEditBox(std::unique_ptr<IEntity>&);
		void addCheckBox(std::unique_ptr<IEntity>&);
		void addListBox(std::unique_ptr<IEntity>&);
		
		std::string getInputText(std::unique_ptr<IEntity> &item);
		bool getCheckboxState(std::unique_ptr<IEntity> &item);
		std::wstring getLabelText(std::unique_ptr<IEntity> &item);
		void initMenu(std::vector<std::unique_ptr<IEntity>> &);
		
		void drop();
		void draw();
		void drawMenu();
		int getIdButtonPressed() const;
		std::wstring getListBoxChoice(std::unique_ptr<IEntity>&);
		void displayBackground();
		void initGame(pairUC size, std::vector<std::unique_ptr<IEntity> >&);

		void drawGame();
		void cleanMenu();
		void removeItem(int);
		void removePlayer(int);

		void newMenuItems(std::vector<std::unique_ptr<IEntity>> &menuItems);
		void initMenu(std::vector<MenuItem> &);
		void updateLabel(std::unique_ptr<IEntity> &item);
		void updatePlayer(std::unique_ptr<IEntity> &entity);
		void updateCube(std::unique_ptr<IEntity> &entity);
		void deletePause();
		void setVisible(bool, int);
		void dropAll();
		void updateItem(std::unique_ptr<IEntity> &entity);
		void addItem(std::unique_ptr<IEntity> &entity);
		bool getSplitScreen() const {return _splitScreen; };
		void setSplitScreen(bool split);
		void removeSphere(int);
		
		int	handleClickColision();
		// void addStaticText(std::unique_ptr<IEntity> &item);
		// void AffEntities(std::vector<GameEntities>);

	private:
		irr::IrrlichtDevice		*_device;
		irr::video::IVideoDriver	*_driver;
		irr::scene::ISceneManager	*_smgr;
		irr::scene::ISceneCollisionManager	*_colsmgr;
		irr::gui::IGUIEnvironment	*_guienv;
		const irr::scene::IGeometryCreator *_geomentryCreator;
	
		Actions _actions;
		MyEventReceiver			_eventReceiver;
		irr::core::vector3df		_camTarget;

		std::vector<irr::scene::ISceneNode*> _cubes;
		std::vector<irr::gui::IGUIEditBox*> _inputs;
		std::vector<irr::gui::IGUICheckBox*> _checkboxes;
		std::vector<irr::gui::IGUIStaticText*> _labels;
		std::vector<irr::gui::IGUIButton*> _buttons;
		std::vector<irr::scene::IAnimatedMeshSceneNode*> _players;
		std::vector<irr::scene::ISceneNode*> _spheres;
		std::vector<irr::scene::IAnimatedMeshSceneNode*> _items;
		irr::gui::IGUIListBox *_listbox;
		irr::scene::ICameraSceneNode	*_camera;
		irr::scene::ISceneNode	*_skybox;
		irr::scene::ISceneNode* _ground;
		Music	_gamemusic;

		std::map<Entity, std::function<void(std::unique_ptr<IEntity>&)>> _factory;
		std::map<Entity, std::function<void(std::unique_ptr<IEntity>&)>> _factoryUpdate;
		std::map<Entity, std::function<void(int)>> _factoryDelete;

		irr::scene::ICameraSceneNode *_cameras[2];

		irr::core::vector3df	_camPos;
		int _screenSizeX;
		int _screenSizeY;
		bool _splitScreen;
		int _lastFps;
		int _altitude;
		int _x;
		int _y;
};

#endif