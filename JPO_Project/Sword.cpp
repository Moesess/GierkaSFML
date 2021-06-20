#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned value, std::string texture_file):MeleeWeapon(value, texture_file){
	
	// Broñ gracza
	this->weapon_sprite.setOrigin(this->weapon_sprite.getGlobalBounds().width / 2.f, this->weapon_sprite.getGlobalBounds().height);
	this->weapon_sprite.scale(3.f, 3.f);
}

Sword::~Sword(){

}

void Sword::update(sf::Vector2f& mouse_pos_view, const sf::Vector2f center){
	// Aktualizacja broni
	this->weapon_sprite.setPosition(center);

	float dx = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dy = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265f;

	float deg = atan2(dy, dx) * 180 / PI;

	this->weapon_sprite.setRotation(deg + 90.f);
}

void Sword::render(sf::RenderTarget & target, sf::Shader* shader){
	if(shader)
		target.draw(this->weapon_sprite, shader);
	else
		target.draw(this->weapon_sprite);
}

Sword * Sword::clone(){
	return new Sword(*this);
}

