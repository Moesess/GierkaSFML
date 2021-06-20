#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"
class MainMenuState;

class Game{
	private:
		// Variables
		GraphicsSettings gf_settings;
		StateData state_data;
		sf::RenderWindow *window;
		sf::Event sf_event;
		float grid_size;
		float tile_res;

		// Zarzadzanie klatkami
		sf::Clock dtClock;
		float dt;

		std::stack<State*>  states;

		std::map<std::string, int> keys;

		//Init
		void variables_init();
		void graphics_settings_init();
		void window_init();
		void state_data_init();
		void keys_init();
		void states_init();
	

	public:
		Game();
		virtual ~Game();

		void quit_app();

		void update_dt();
		void update_SFML_events();
		void update();

		void render();
		
		void run();
};

#endif