#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(
	int x, int y, float grid_size_f, const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, int enemy_time_spawn, float enemy_max_distance)
	:Tile(TileTypes::ENEMY_SPAWNER, x, y, grid_size_f, texture, texture_rect, false){
	
	this->grid_position = grid_position;
	this->enemy_type = enemy_type;
	this->enemy_amount = enemy_amount;
	this->enemy_time_spawn = enemy_time_spawn;
	this->enemy_max_distance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile(){

}

const std::string EnemySpawnerTile::to_string() const{
	// Zamiana tile na string do zapisu do pliku
	std::stringstream ss;

	ss	<< this->type << " "
		<< this->shape.getTextureRect().left << " "
		<< this->shape.getTextureRect().top << " "
		<< this->enemy_type << " "
		<< this->enemy_amount << " "
		<< this->enemy_time_spawn << " "
		<< this->enemy_max_distance;

	return ss.str();
}

const bool & EnemySpawnerTile::get_spawned() const{

	return this->spawned;
}

void EnemySpawnerTile::set_spawned(const bool spawned){
	this->spawned = spawned;
}


// Methods
void EnemySpawnerTile::update(){

}

void EnemySpawnerTile::render(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f player_pos){
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_pos);
	}
	else {
		target.draw(this->shape);
	}
}
