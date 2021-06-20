#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, bool colliding)
	:Tile(type, x, y, grid_size_f, texture, texture_rect, colliding){
	
}

RegularTile::~RegularTile(){

}

// Getters


// Methods
const std::string RegularTile::to_string() const{
	// Zamiana tile na string do zapisu do pliku
	std::stringstream ss;

	ss << this->type << " "
		<< this->shape.getTextureRect().left << " "
		<< this->shape.getTextureRect().top << " "
		<< this->colliding;

	return ss.str();
}

void RegularTile::update(){

}

void RegularTile::render(sf::RenderTarget & target, sf::Shader * shader, const sf::Vector2f player_pos){
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_pos);
	}
	else {
		target.draw(this->shape);
	}
}

