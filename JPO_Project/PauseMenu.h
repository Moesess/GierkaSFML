#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class Gui;

class PauseMenu{
private:
	sf::Font& font;
	sf::Text menu_text;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	bool loose;
	bool win;
	// Methods

public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	// Getters
	std::map<std::string, gui::Button*>& get_buttons();
	const bool get_loose() const;
	const bool get_win() const;

	//Setters
	void set_loose();
	void set_win();
	// Methods
	const bool is_button_pressed(const std::string key);
	void add_button(const std::string key, const float y, const float width, const float height, const unsigned font_size, const std::string text);
	void update(sf::Vector2i& mouse_position_window);
	void render(sf::RenderTarget& target);
};

#endif