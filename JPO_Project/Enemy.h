#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"
class Entity;
class EnemySpawnerTile;

class Enemy :
	public Entity{
private:
	// Vars
	unsigned exp_gain;

	// Init
	virtual void variables_init() = 0;
	virtual void components_init() = 0;
	virtual void animations_init() = 0;

public:
	Enemy();
	virtual ~Enemy();

	// Getters
	const unsigned& get_exp_gain() const;

	// Methods
	virtual void take_damage(const int damage);
	virtual const bool is_dead() const;
	virtual const AttributesComponent* get_attribute_comp() const;

	virtual void update_animation(const float & dt) = 0;
	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false) = 0;
};

#endif