#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
class Weapon :
	public Item{
private:
	void variables_init();

protected:
	unsigned range;
	unsigned damage_min;
	unsigned damage_max;

	sf::Texture weapon_texture;
	sf::Sprite weapon_sprite;

	sf::Clock attack_timer;
	sf::Int32 attack_timer_max;

public:
	Weapon(unsigned value,  std::string texture_file);
	virtual ~Weapon();

	// Getters
	const unsigned& get_range() const;
	const unsigned& get_damage_min() const;
	const unsigned& get_damage_max() const;
	const bool get_attack_timer();

	// Methods
	virtual Item* clone() = 0;

	virtual void update(sf::Vector2f& mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

#endif