#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributesComponent.h"
#include "SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributesComponent;
class SkillComponent;

class Entity{
private:
	void variables_init();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitbox_component;
	MovementComponent* movement_component;
	AnimationComponent* animation_component;
	AttributesComponent* attributes_component;
	SkillComponent* skill_component;

public:
	Entity();
	virtual ~Entity();

	// Components
	void create_hitbox_component(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void create_movement_component(const float max_velocity, const float acceleration, const float deceleration);
	void create_animation_component(sf::Texture & texture_sheet);
	void create_attributes_component(const unsigned level);
	void create_skill_component();

	// Setters
	void set_texture(sf::Texture& texture);

	// Getters
	virtual const sf::Vector2f& get_position() const;
	virtual const sf::Vector2f get_center() const;
	virtual const sf::Vector2i get_grid_position(const int grid_size_i) const;
	virtual const sf::FloatRect get_global_bounds() const;
	virtual const sf::FloatRect get_next_pos(const float& dt) const;

	// Methods
	virtual void set_pos(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void stop_velocity();
	virtual void stop_velocity_x();
	virtual void stop_velocity_y();

	virtual const float get_distance(const Entity& en) const;

	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, bool show_hitbox) = 0;
};

#endif