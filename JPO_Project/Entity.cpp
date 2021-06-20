#include "stdafx.h"
#include "Entity.h"

Entity::Entity(){
	this->variables_init();
}

Entity::~Entity(){
	delete this->hitbox_component;
	delete this->movement_component;
	delete this->animation_component;
	delete this->attributes_component;
	delete this->skill_component;
}

void Entity::variables_init() {
	this->hitbox_component = nullptr;
	this->movement_component = nullptr;
	this->animation_component = nullptr;
	this->attributes_component = nullptr;
	this->skill_component = nullptr;
}

// Components

void Entity::create_hitbox_component(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) {
	this->hitbox_component = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::create_movement_component(const float max_velocity, const float acceleration, const float deceleration) {
	this->movement_component = new MovementComponent(this->sprite, max_velocity, acceleration, deceleration);
}

void Entity::create_animation_component(sf::Texture & texture_sheet) {
	this->animation_component = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::create_attributes_component(const unsigned level) {
	this->attributes_component = new AttributesComponent(level);
}

void Entity::create_skill_component(){
	this->skill_component = new SkillComponent();
}

// Setters
void Entity::set_texture(sf::Texture& texture) {
	this->sprite.setTexture(texture);
}

void Entity::set_pos(const float x, const float y) {
	// Je¿eli obiekt ma hitbox, ustawiamy pozycje hitboxa
	
	if (this->hitbox_component)
		this->hitbox_component->set_position(x, y);
	
	else
		this->sprite.setPosition(x, y);

}

// Getters
const sf::Vector2f& Entity::get_position() const{
	// Je¿eli obiekt ma hitbox, zwracamy pozycje hitboxa
	if (this->hitbox_component)
		return this->hitbox_component->get_position();

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::get_center() const{

	if (this->hitbox_component)
		return this->hitbox_component->get_position() + sf::Vector2f(
			this->hitbox_component->get_global_bounds().width / 2.f,
			this->hitbox_component->get_global_bounds().height / 2.f
		);

	return this->sprite.getPosition() + sf::Vector2f(
		this->sprite.getGlobalBounds().width / 2.f,
		this->sprite.getGlobalBounds().height / 2.f
	);
}

const sf::Vector2i Entity::get_grid_position(const int grid_size_i) const{
	if (this->hitbox_component)
		return sf::Vector2i(
			static_cast<int>(this->hitbox_component->get_position().x / grid_size_i),
			static_cast<int>(this->hitbox_component->get_position().y / grid_size_i)
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x / grid_size_i),
		static_cast<int>(this->sprite.getPosition().y / grid_size_i)
	);
}

const sf::FloatRect Entity::get_global_bounds() const{
	if (this->hitbox_component)
		return this->hitbox_component->get_global_bounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::get_next_pos(const float& dt) const{

	if (this->hitbox_component and this->movement_component) {
		return this->hitbox_component->get_next_pos(this->movement_component->get_velocity() * dt);
	}

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// Methods
void Entity::move(const float dir_x, const float dir_y, const float& dt){

	if (this->movement_component) {
		this->movement_component->move(dir_x, dir_y, dt);
	}

	if (this->skill_component) {
		this->skill_component->gain_exp(SKILLS::ENDURANCE, 1);
		//std::cout << this->skill_component->get_skill(SKILLS::ENDURANCE) << "\n";
	}
		
}

void Entity::stop_velocity(){
	if (this->movement_component) {
		this->movement_component->stop_velocity();
	}
}

void Entity::stop_velocity_x(){
	if (this->movement_component) {
		this->movement_component->stop_velocity_x();
	}
}

void Entity::stop_velocity_y(){
	if (this->movement_component) {
		this->movement_component->stop_velocity_y();
	}
}

const float Entity::get_distance(const Entity& en) const{
	
	//std::cout << "Distance: " << std::sqrt(std::pow((this->get_center().x - en.get_center().x), 2) + std::pow((this->get_center().y - en.get_center().y), 2)) << "\n";
	return std::sqrt(std::pow((this->get_center().x - en.get_center().x), 2) + std::pow((this->get_center().y - en.get_center().y), 2));
}
