#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"
class Tile;

class EnemySpawnerTile : public Tile{
private:
	sf::Vector2i grid_position;
	int enemy_type;
	int enemy_amount;
	int enemy_time_spawn;
	float enemy_max_distance;
	bool spawned;

public:
	EnemySpawnerTile(
		int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_type, int enemy_amount, int enemy_time_spawn, float enemy_max_distance
		);
	virtual ~EnemySpawnerTile();

	// Getters
	virtual const std::string to_string() const;
	const bool& get_spawned() const;
	// Setters
	void set_spawned(const bool spawned);

	// Methods
	void update();
	void render(sf::RenderTarget & target, sf::Shader* shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f());
};

#endif // !ENEMYSPAWNER_H
