#ifndef TILEMAP_H
#define TILEMAP_H

#include "RegularTile.h"
#include "Entity.h"
#include "EnemySpawnerTile.h"
#include "EnemySystem.h"

class Tile;
class RegularTile;
class EnemySpawner;
class Enemy;
class Entity;

class TileMap{
private:
	void clear();

	float grid_size_f;
	int grid_size_i;
	int layers;

	sf::Vector2i max_world_size;
	sf::Vector2f max_world_size_f;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	std::stack<Tile*> delayed_tiles;  // Tiles ktore sa nad graczem, albo chcemy opoznic ich render
	std::string texture_file;
	sf::Texture texture_sheet;
	sf::RectangleShape collision_box;

	int from_x;
	int to_x;
	int from_y;
	int to_y;
	int layer;

public:
	TileMap(float grid_size, int width, int height, std::string texture_file);
	TileMap(const std::string file_name);
	virtual ~TileMap();

	// Getters
	const sf::Texture* get_texture_sheet() const;
	const int get_layer_size(const int x, const int y, const int layer) const;
	const sf::Vector2i& get_max_world_grid_size_i() const;
	const sf::Vector2f& get_max_world_grid_size_f() const;
	const bool tile_empty(const int x, const int y, const int z ) const;
	const bool check_tile_type(const int x, const int y, const int type) const;

	// Methods
	void render_delayed_tiles(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f());
	void render(sf::RenderTarget& target, const sf::Vector2i& grid_pos, sf::Shader* shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f(), const bool hitbox = false);
	void render_whole(sf::RenderTarget& target, const bool show_hitbox = false);

	void update_world_border_collision(Entity* entity, const float&dt);
	void update_tile_collision(Entity* entity, const float& dt);
	void update_tiles(Entity* entity, const float& dt, EnemySystem& enemy_system);
	void update(Entity* entity, const float& dt);

	void add_tile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& colliding, const short& type);
	void add_tile(const int x, const int y, const int z, const sf::IntRect & texture_rect, const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_max_distance);
	void remove_tile(const int x, const int y, const int z, const int type = -1);

	void save_to_file(const std::string file_name);
	void load_from_file(const std::string file_name);
};

#endif