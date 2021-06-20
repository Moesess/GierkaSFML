#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class GraphicsSettings;
class Player;
class State;

class StateData {
public:
	StateData() {}

	// Vars
	sf::RenderWindow *window;
	std::map<std::string, int>* keys;
	std::stack<State*>* states;
	GraphicsSettings* gf_settings;
	float grid_size;
	float tile_res;

};

class State{
private:

protected:
	StateData* state_data;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int> key_binds;
	std::map<std::string, int>* keys;
	bool quit;
	bool paused;
	float keytime;
	float keytime_max;
	float grid_size;
	float tile_res;

	// Mouse Vars
	sf::Vector2i mouse_pos_screen;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;
	sf::Vector2i mouse_pos_grid;

	// Resources
	std::map<std::string, sf::Texture> textures;

	// Methods
	virtual void key_binds_init() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	// State managements
	void pause_state();
	void unpause_state();
	virtual void end_state();

	// Getters
	const bool& get_quit();
	const bool get_keytime();

	// Methods
	virtual void update_mouse_pos(sf::View* view = nullptr);
	virtual void update_keytime(const float& dt);
	virtual void update_input(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif