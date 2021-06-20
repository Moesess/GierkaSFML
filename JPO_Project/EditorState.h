#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "DefaultEditorMode.h"
#include "EnemyEditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class Tile;
class TileMap;
class EditorMode;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;

enum EditorModes{DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};

class EditorState :
	public State{

private:
	// Variables
	EditorStateData editor_state_data;

	sf::View view;
	sf::Font font;
	PauseMenu* pmenu;
	float camera_speed;
	
	std::map<std::string, gui::Button*> buttons;

	TileMap* tile_map;

	std::vector<EditorMode*> modes;
	unsigned active_mode;

	// Methods
	void variables_init();
	void editor_state_data_init();
	void view_init();
	void key_binds_init();
	void fonts_init();
	void buttons_init();
	void pause_menu_init();
	void gui_init();
	void tile_map_init();

	void modes_init();

protected:
	float texture_res;

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Methods
	void update_input(const float& dt);
	void update_editor_input(const float& dt);
	void update_buttons();
	void update_pause_menu_buttons();
	void update_modes(const float& dt);
	void update_gui(const float& dt);
	void update(const float &dt);

	void render_buttons(sf::RenderTarget& target);
	void render_gui(sf::RenderTarget& target);
	void render_modes(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif