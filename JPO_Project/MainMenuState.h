#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class GameState;
class Gui;
class EditorState;
class SettingsState;

class MainMenuState :
	public State
{
private:
	// Variables
	sf::Texture background_texture;
	sf::RectangleShape background;
	sf::Font font;

	sf::RectangleShape btn_background;
	std::map<std::string, gui::Button*> buttons;

	// Methods
	void variables_init();
	void key_binds_init();
	void fonts_init();
	void gui_init();
	void reset_gui();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Methods
	void update_input(const float& dt);
	void update_gui();
	void update(const float &dt);
	void render(sf::RenderTarget* target = nullptr);
	void render_gui(sf::RenderTarget& target);
};

#endif