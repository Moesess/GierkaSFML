#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "Gui.h"

class Player;
class sf::RectangleShape;
class sf::Font;

class PlayerGui{
private:
	Player* player;
	sf::VideoMode& vm;
	sf::Font font;

	// Pasek z poziomem
	std::string lv_bar_string;
	sf::Text lv_bar_text;
	sf::RectangleShape lv_bar_back;

	// Pasek doœwiadczenia
	gui::ProgressBar* exp_bar;

	// Pasek ¿ycia
	gui::ProgressBar* hp_bar;

	void font_init();
	void level_bar_init();
	void hp_bar_init();
	void exp_bar_init();

public:
	PlayerGui(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGui();
	
	// Methods
	void update_hp_bar();
	void update_lv_bar();
	void update_exp_bar();
	void update(const float& dt);

	void render_hp_bar(sf::RenderTarget & target);
	void render_lv_bar(sf::RenderTarget & target);
	void render_exp_bar(sf::RenderTarget & target);
	void render(sf::RenderTarget& target);
};

#endif