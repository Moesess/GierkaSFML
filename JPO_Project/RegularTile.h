#ifndef REGULARTILE_H
#define REGULARTILE_H

#include "Tile.h"

class RegularTile :
	public Tile{
private:

protected:

public:
	RegularTile(short type, int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, bool colliding = false);
	virtual ~RegularTile();

	// Getters

	// Methods
	virtual const std::string to_string() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f());

};

#endif