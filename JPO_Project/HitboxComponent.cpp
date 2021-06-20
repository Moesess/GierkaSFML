#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite & sprite, float offset_x, float offset_y, float width, float height):
	sprite(sprite), offset_x(offset_x), offset_y(offset_y){

	this->next_pos.left = 0.f;
	this->next_pos.top = 0.f;
	this->next_pos.width = width;
	this->next_pos.height = height;

	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x, this->sprite.getPosition().y + this->offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Blue);
}

HitboxComponent::~HitboxComponent(){

}

// Getters
const sf::Vector2f & HitboxComponent::get_position() const{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::get_global_bounds() const{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect & HitboxComponent::get_next_pos(const sf::Vector2f & velocity){
	
	this->next_pos.left = this->hitbox.getPosition().x + velocity.x;
	this->next_pos.top = this->hitbox.getPosition().y + velocity.y;

	return this->next_pos;
}


// Setters
void HitboxComponent::set_position(const sf::Vector2f& position){
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offset_x, position.y - this->offset_y);
}

void HitboxComponent::set_position(const float x, const float y){
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offset_x, y - this->offset_y);
}


// Methods
bool HitboxComponent::intersects(const sf::FloatRect& frect){

	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update(){
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x, this->sprite.getPosition().y + this->offset_y);
}

void HitboxComponent::render(sf::RenderTarget & target){
	target.draw(this->hitbox);
}
