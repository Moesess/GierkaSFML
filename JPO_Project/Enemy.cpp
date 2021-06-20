#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(){
	this->variables_init();
	this->animations_init();
}

Enemy::~Enemy(){

}

const unsigned & Enemy::get_exp_gain() const{

	return this->exp_gain;
}

// Init
void Enemy::variables_init() {
	this->exp_gain = 20;
}

void Enemy::components_init() {

}

void Enemy::animations_init() {

}


void Enemy::take_damage(const int damage){
	if (this->attributes_component) {
		this->attributes_component->loose_hp(damage);
	}
}

const bool Enemy::is_dead() const{
	if(this->attributes_component)
		return this->attributes_component->is_dead();

	return false;
}

const AttributesComponent * Enemy::get_attribute_comp() const{
	if(this->attributes_component)
		return this->attributes_component;

	else {
		std::cout << "ERROR: NO ATTRIBUTE COMPONENT \n";
		return nullptr;
	}
}

// Methods
void Enemy::update_animation(const float & dt) {

}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view) {

}

void Enemy::render(sf::RenderTarget & target, sf::Shader* shader, const bool show_hitbox) {
}
