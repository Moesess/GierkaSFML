#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;

class DefaultEditorMode :
	public EditorMode{
private:
	// Vars
	sf::Text cursor_text;
	sf::RectangleShape sidebar;
	gui::TextureSelector* texture_selector;
	sf::RectangleShape selector_shape; // kwadrat zaznaczajacy tile
	sf::IntRect texture_rect;
	bool colliding;
	short type;
	int layer;
	bool tile_lock;

	// Init
	void variables_init();
	void gui_init();
	
public:
	DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultEditorMode();

	// Methods
	void update_input(const float& dt);
	void update_gui(const float& dt);
	void update(const float &dt);

	void render_gui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif