#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& enemies, std::map<std::string, sf::Texture>& textures)
	:textures(textures), enemies(enemies){

}

EnemySystem::~EnemySystem(){

}

void EnemySystem::create_enemy(const short type, const float x, const float y){
	switch (type) {

	case EnemyTypes::SLIME:
		this->enemies.push_back(new Slime(x, y, this->textures["ENEMY_SLIME_SHEET"]));
		break;
	
	default:
		throw "ERROR:: NO TYPE EXIST IN ENEMY TYPE || ENEMYSYSTEM.CPP";
		break;
	}
}

void EnemySystem::update(const float & dt){

}

void EnemySystem::render(sf::RenderTarget * target){

}
