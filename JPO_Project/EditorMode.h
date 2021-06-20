#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class Tile;
class TileMap;

class EditorStateData {
public:
	EditorStateData() {}

	// Vars
	sf::View* view;
	sf::Font* font;

	float* keytime;
	float* keytime_max;

	std::map< std::string, int>* key_binds;

	// Mouse Vars
	sf::Vector2i* mouse_pos_screen;
	sf::Vector2i* mouse_pos_window;
	sf::Vector2f* mouse_pos_view;
	sf::Vector2i* mouse_pos_grid;
};

class EditorMode{
protected:
	StateData* state_data;
	EditorStateData* editor_state_data;
	TileMap* tile_map;
	float texture_res;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

	// Getters
	const bool get_keytime();

	// Methods
	virtual void update_input(const float& dt) = 0;
	virtual void update_gui(const float& dt) = 0;
	virtual void update(const float &dt) = 0;

	virtual void render_gui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget&) = 0;
};

#endif // !EDITORMODE_H