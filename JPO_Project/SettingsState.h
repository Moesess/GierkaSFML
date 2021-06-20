#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class State;
class Gui;

class SettingsState :
	public State{
private:
	// Variables
	sf::Texture background_texture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropdowns;

	sf::Text options_text;

	std::vector<sf::VideoMode> modes;

	// Methods
	void variables_init();
	void key_binds_init();
	void fonts_init();
	void gui_init();
	void reset_gui();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	// Getters

	// Methods
	void update_input(const float& dt);
	void update_gui(const float& dt);
	void update(const float &dt);
	void render(sf::RenderTarget* target = nullptr);
	void render_gui(sf::RenderTarget& target);
};

#endif