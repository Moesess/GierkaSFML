#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Slime.h"

enum EnemyTypes {SLIME = 0};

class EnemySystem{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& enemies;

public:
	EnemySystem(std::vector<Enemy*>& enemies, std::map<std::string, sf::Texture>& textures);
	virtual ~EnemySystem();

	// Getters

	// Setters

	// Methods
	void create_enemy(const short type, const float x, const float y);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif