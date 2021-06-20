#include "stdafx.h"
#include "Weapon.h"

void Weapon::variables_init(){
	this->range = 100;
	this->damage_min = 1;
	this->damage_max = 2;

	this->attack_timer.restart();
	this->attack_timer_max = 400;
}

Weapon::Weapon(unsigned value, std::string texture_file)
	:Item(value){

	this->variables_init();

	if (!this->weapon_texture.loadFromFile(texture_file)) {
		std::cout << "ERROR:: NO TEXTURE LOADED FOR WEAPON IN WEAOIB FILE:: " + texture_file;
	}
	
	this->weapon_sprite.setTexture(weapon_texture);

}

Weapon::~Weapon()
{
}

// Getters
const unsigned & Weapon::get_range() const{

	return this->range;
}

const unsigned & Weapon::get_damage_min() const{
	return this->damage_min;
}

const unsigned & Weapon::get_damage_max() const{
	return this->damage_max;
}

const bool Weapon::get_attack_timer(){
	//std::cout << "Zegar MAX: " << this->attack_timer_max << " Zegar ELAPSED" << this->attack_timer.getElapsedTime().asMilliseconds() << " OBIEKT: " << this << "\n";
	if (this->attack_timer.getElapsedTime().asMilliseconds() >= this->attack_timer_max) {
		std::cout << "MOZNA UDERZYC!\n";
		this->attack_timer.restart();
		return true;
	}
	return false;
}
