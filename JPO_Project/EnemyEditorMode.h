#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;
class EnemySpawner;

class EnemyEditorMode :
	public EditorMode{

private:
	// Vars
	sf::Text cursor_text;
	sf::RectangleShape sidebar;
	sf::RectangleShape selector_shape; // kwadrat zaznaczajacy tile
	sf::IntRect texture_rect;

	int type;
	int amount;
	int time_to_spawn;
	float max_distance;

	// Methods
	void gui_init();
	void variables_init();

public:
	EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EnemyEditorMode();

	// Methods
	void update_input(const float& dt);
	void update_gui(const float& dt);
	void update(const float &dt);

	void render_gui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif