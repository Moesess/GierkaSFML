#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Sword.h"

class GameState:public State{
private:
	sf::View view; 
	sf::Vector2i view_grid_pos; 
	sf::RenderTexture render_texture;
	sf::Sprite render_sprite;

	PauseMenu* pmenu;
	sf::Font font;

	sf::Shader core_shader;

	// Gracz, tekstury
	Player* player;
	PlayerGui* player_gui;
	sf::Texture texture;

	// Mapa
	TileMap* tile_map;

	// Przeciwnicy
	std::vector<Enemy*> active_enemies;
	EnemySystem* enemy_system;

	// Init
	void render_def_init();
	void view_init();
	void key_binds_init();
	void textures_init();
	void player_init();
	void player_gui_init();
	void pause_menu_init();
	void shaders_init();
	void fonts_init();
	void tile_map_init();
	void enemy_system_init();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	// Getters

	//Methods
	void update_view(const float& dt);
	void update_input(const float& dt);
	void update_pause_menu_buttons();
	void update_player_input(const float& dt);
	void update_tile_map(const float& dt);
	void update_player_gui(const float& dt);
	void update_player(const float& dt);
	void update_enemies(const float& dt);
	void update_combat(Enemy* enemy, const int index, const float & dt);
	void update(const float &dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif