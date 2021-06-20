#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING, ABOVE_PLAYER, ENEMY_SPAWNER};

class Tile{
private:

protected:
	sf::Sprite shape;
	short type;
	bool colliding;

public:
	Tile();
	Tile(short type, int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect, const bool colliding);
	virtual ~Tile();

	// Getters
	virtual const sf::Vector2f& get_position() const;
	virtual const short& get_type() const;
	virtual const sf::FloatRect get_global_bounds() const;
	virtual const bool& get_collision() const;

	// Methods
	virtual const std::string to_string() const = 0;
	virtual const bool intersects(const sf::FloatRect bounds) const;

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f()) = 0;
};

#endif