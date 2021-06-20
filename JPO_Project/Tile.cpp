#include "stdafx.h"
#include "Tile.h"

Tile::Tile(){
	this->type = 0;
	this->colliding = false;
}

Tile::Tile(short type, int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, const bool colliding){
	//this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
	//this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(x) * grid_size_f, static_cast<float>(y) * grid_size_f);
	this->shape.setTexture(texture);
	this->shape.scale(2.f, 2.f);
	this->shape.setTextureRect(texture_rect);

	this->colliding = colliding;
	this->type = type;
}

Tile::~Tile(){

}

// Getters
const sf::Vector2f & Tile::get_position() const
{
	return this->shape.getPosition();
}

const short & Tile::get_type() const{
	return this->type;
}

const sf::FloatRect Tile::get_global_bounds() const{
	return this->shape.getGlobalBounds();
}

const bool & Tile::get_collision() const{
	return this->colliding;
}

// Methods
const bool Tile::intersects(const sf::FloatRect bounds) const{
	return this->shape.getGlobalBounds().intersects(bounds);
}
