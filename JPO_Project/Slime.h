#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"
class Slime :
	public Enemy{
private:
	sf::Text info_text;
	sf::Font font;

	// Init
	void variables_init();
	void components_init();
	void animations_init();
	void text_init();
	void font_init();

public:
	Slime(float x, float y, sf::Texture& texture_sheet);
	virtual ~Slime();

	// Methods
	void update_animation(const float & dt);
	void update_text(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);
	
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false);
};

#endif