#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float max_velocity, float acceleration, float deceleration)
	: sprite(sprite), max_velocity(max_velocity), acceleration(acceleration), deceleration(deceleration){
	this->max_velocity = max_velocity;
}

MovementComponent::~MovementComponent(){

}

// Getters
const sf::Vector2f & MovementComponent::get_velocity() const {
	return this->velocity;
}

const float & MovementComponent::get_max_velocity() const{
	return this->max_velocity;
}

// Methods

bool MovementComponent::get_state(const short unsigned state){

	switch (state) {
	case IDLE:
		if (this->velocity.x == 0.f and this->velocity.y == 0.f) 
			return true;
		break;

	case MOVING:
		if (this->velocity.x != 0.f or this->velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.f) {
			return true;
		}
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f) {
			return true;
		}
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;

	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;
	}

	return false;
}

void MovementComponent::stop_velocity(){
	// zatrzymanie obiektu
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stop_velocity_x(){
	// Zatrzymanie obiektu na osi x
	this->velocity.x = 0.f;
}

void MovementComponent::stop_velocity_y(){
	// zatrzymanie obiektu na osi y
	this->velocity.y = 0.f;
}

void MovementComponent::update(const float & dt){
	// Ustawiamy granice, max predkosc i przyspieszenie
	
	// X
	if (this->velocity.x > 0.f) { // x positive

		// Max predkosc
		if (this->velocity.x > this->max_velocity) {
			this->velocity.x = this->max_velocity;
		}

		// Spowolnienie obiektu
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}

	else if (this->velocity.x < 0.f) { // x negative
		// Max predkosc
		if (this->velocity.x < -this->max_velocity) {
			this->velocity.x = -this->max_velocity;
		}

		// Spowolnienie obiektu
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}


	// Y
	if (this->velocity.y > 0.f) {

		// Max predkosc
		if (this->velocity.y > this->max_velocity) { // y positive
			this->velocity.y = this->max_velocity;
		}

		// Spowolnienie obiektu
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}

	else if (this->velocity.y < 0.f) {
		// Max predkosc
		if (this->velocity.y < -this->max_velocity) { // y negative
			this->velocity.y = -this->max_velocity;
		}

		// Spowolnienie obiektu
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	// Moving
	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt){
	// Przyspieszenie obiektu
	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}
