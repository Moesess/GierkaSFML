#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, sf::Texture& texture_sheet) {
	this->variables_init();
	this->sprite.setScale(sf::Vector2f(4.f, 4.f));

	this->create_hitbox_component(this->sprite, 16.f, 17.f, 36.f, 36.f);
	//this->create_hitbox_component(this->sprite, 80.f, 80.f, 180.f, 180.f);
	this->create_attributes_component(1);
	this->create_movement_component(300.f, 1500.f, 800.f);
	this->create_animation_component(texture_sheet);
	this->create_skill_component();


	this->set_pos(x, y);
	this->animations_init();

	this->inventory_init();

	std::cout << this->get_attributes_component()->print() << "\n";
}

Player::~Player(){
	delete this->sword;
	delete this->inventory;
}

AttributesComponent * Player::get_attributes_component(){
	return attributes_component;
}

Weapon * Player::get_weapon() const{
	return this->sword;
}

const bool Player::get_damage_timer(){
	if (this->damage_timer.getElapsedTime().asMilliseconds() >= this->damage_timer_max) {

		this->damage_timer.restart();
		return true;
	}
	return false;
}

// Init
void Player::variables_init() {
	this->attacking = false;
	this->sword = new Sword(0, "Resources/Images/Sprites/Weapons/weapon_sword_2.png");

	this->damage_timer.restart();
	this->damage_timer_max = 400;

	this->attacking = false;
}

void Player::components_init() {

}

void Player::animations_init() {
	// Animacje gracza
	this->animation_component->add_animation("IDLE", 20.f, 0, 1, 5, 1, 16, 16);
	this->animation_component->add_animation("RUN", 8.f, 0, 0, 5, 0, 16, 16);
	this->animation_component->add_animation("ATTACK", 14.f, 0, 2, 2, 2, 25, 16);
}

void Player::inventory_init(){
	this->inventory = new Inventory(8);
}

// Attributes Methods
void Player::loose_hp(const int hp){
	this->attributes_component->loose_hp(hp);
}

void Player::gain_hp(const int hp) {
	this->attributes_component->gain_hp(hp);
}

void Player::loose_exp(const int exp){
	this->attributes_component->loose_exp(exp);
}

void Player::gain_exp(const int exp){
	
	this->attributes_component->gain_exp(exp);
}

// Methods
void Player::update_animation(const float & dt){
	// Przypisanie animacji do stanów gracza
	if (this->attacking) {
		if (this->animation_component->play("ATTACK", dt, true)) {
			this->attacking = false;
		}
	}

	if (this->movement_component->get_state(IDLE))
		this->animation_component->play("IDLE", dt);

	else if (this->movement_component->get_state(MOVING_LEFT)) {

		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(17.f, 0.f);
			this->sprite.setScale(-4.f, 4.f);
		}

		this->animation_component->play("RUN", dt, this->movement_component->get_velocity().x, this->movement_component->get_max_velocity());
	}

	else if (this->movement_component->get_state(MOVING_RIGHT)) {

		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(4.f, 4.f);
		}

		this->animation_component->play("RUN", dt, this->movement_component->get_velocity().x, this->movement_component->get_max_velocity());
	}

	else if (this->movement_component->get_state(MOVING_DOWN)) {
		this->animation_component->play("RUN", dt, this->movement_component->get_velocity().y, this->movement_component->get_max_velocity());
	}

	else if (this->movement_component->get_state(MOVING_UP)) {
		this->animation_component->play("RUN", dt, this->movement_component->get_velocity().y, this->movement_component->get_max_velocity());
	}
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view){

	this->movement_component->update(dt);
	this->update_animation(dt);
	this->hitbox_component->update();
	
	this->sword->update(mouse_pos_view, sf::Vector2f(this->get_center().x, this->get_center().y + 8.f));
}

void Player::render(sf::RenderTarget & target, sf::Shader* shader, const bool show_hitbox){
	
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->get_center());

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->get_center());
		this->sword->render(target, shader); 
	}
	else {
		target.draw(this->sprite, shader);
		this->sword->render(target);
	}
		

	if(show_hitbox)
		this->hitbox_component->render(target);
}


