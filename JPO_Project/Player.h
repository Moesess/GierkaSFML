#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"
#include "Inventory.h"

class Entity;
class Sword;

class Player :
	public Entity{
private:
	// Variables
	Inventory* inventory;

	Sword* sword;

	sf::Clock damage_timer;
	sf::Int32 damage_timer_max;

	// Init
	void variables_init();
	void components_init();
	void animations_init();
	void inventory_init();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	bool attacking;

	// Getters
	AttributesComponent* get_attributes_component();
	Weapon* get_weapon() const;
	const bool get_damage_timer();

	// Methods
	void loose_hp(const int hp);
	void gain_hp(const int hp);
	void loose_exp(const int exp);
	void gain_exp(const int exp);
	void update_animation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false);
};

#endif