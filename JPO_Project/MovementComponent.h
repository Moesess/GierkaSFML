#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent{	
private:
	// Vars
	sf::Sprite& sprite;

	float max_velocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	// Init


public:
	MovementComponent(sf::Sprite& sprite, float max_velocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	// Geters
	const sf::Vector2f& get_velocity() const;
	const float& get_max_velocity() const;

	// Methods
	bool get_state(const short unsigned state);
	void stop_velocity();
	void stop_velocity_x();
	void stop_velocity_y();

	void update(const float& dt);
	void move(const float x, const float y, const float& dt);
};

#endif