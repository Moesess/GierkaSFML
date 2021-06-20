#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect next_pos;

	float offset_x;
	float offset_y;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	// Getters
	const sf::Vector2f& get_position() const;
	const sf::FloatRect get_global_bounds() const;
	const sf::FloatRect& get_next_pos(const sf::Vector2f& velocity);

	// Setters
	void set_position(const sf::Vector2f& position);
	void set_position(const float x, const float y);

	// Methods
	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

#endif
