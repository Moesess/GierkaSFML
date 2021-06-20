#include "stdafx.h"
#include "AttributesComponent.h"

AttributesComponent::AttributesComponent(int level){
	
	// Leveling
	this->level = level;
	this->exp = 0;
	this->exp_next = 40;
	this->level_points = 2;

	//std::cout << "exp" << this->exp << " next" << this->exp_next << "\n";

	// Attributes
	this->strength = 1;
	this->vitality = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->update_level();
	this->update_stats(true);
}

AttributesComponent::~AttributesComponent(){
	
}

// Debug method
std::string AttributesComponent::print() const{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		//<< "Exp: " << this->exp << "\n"
		<< "Exp next: " << this->exp_next << "\n"
		//<< "HP: " << this->hp << "\n"
		<< "HP: " << this->hp_max << "\n"
		<< "Strength: " << this->strength << "\n";

	return ss.str();
}

// Methods
void AttributesComponent::update_level(){
	// Sprawdzanie poziomu obiektu, aktualizowanie poziomu

	if (this->exp >= this->exp_next) {
		
		++this->level;
		this->exp -= this->exp_next;

		this->exp_next = static_cast<int>((50 / 3) * (std::pow(this->level, 3) - 6 * std::pow(this->level, 2) + (this->level * 17) - 12));
		
		++this->hp_max;
		this->hp = this->hp_max;

		++this->strength;

		++this->level_points;

		std::cout << this->print() << "\n";
	}
}

void AttributesComponent::update_stats(const bool reset){
	// Aktualizowanie statystyk obiektu

	this->hp_max		= this->vitality * 5 + this->vitality + (this->strength * 2);
	this->damage_max	= this->strength * 2 + this->strength / 3;
	this->damage_min	= this->strength * 2 + this->strength / 6;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 3;
	this->defence		= this->agility * 2 + this->agility / 3;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;
	
	if (reset) {
		this->hp = this->hp_max;
	}
}

void AttributesComponent::update(){
	this->update_level();
}

void AttributesComponent::loose_hp(const int hp) {
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributesComponent::gain_hp(const int hp) {
	this->hp += hp;

	if (this->hp > this->hp_max)
		this->hp = this->hp_max;
}

void AttributesComponent::loose_exp(const int exp) {
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributesComponent::gain_exp(const int exp) {
	this->exp += exp;

	this->update_level();
}

const bool AttributesComponent::is_dead() const{
	return this->hp <= 0;
}
