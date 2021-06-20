#include "stdafx.h"
#include "Slime.h"

Slime::Slime(float x, float y, sf::Texture& texture_sheet){

	this->variables_init();
	this->font_init();
	this->text_init();
	this->sprite.setScale(sf::Vector2f(4.f, 4.f));

	this->create_hitbox_component(this->sprite, 3.f, 21.f, 60.f, 35.f);
	this->create_movement_component(100.f, 1500.f, 800.f);
	this->create_animation_component(texture_sheet);
	this->create_attributes_component(1);
	this->attributes_component->hp_max = 100;
	this->attributes_component->hp = 100;
	this->attributes_component->damage_max = 2;
	this->attributes_component->damage_min = 1;

	this->set_pos(x, y);
	this->animations_init();

	//std::cout << "Slime: " << this << "\n";
}


Slime::~Slime(){

}


// Init
void Slime::variables_init() {

}

void Slime::components_init() {

}

void Slime::animations_init() {
	// Animacje Przeciwnika
	this->animation_component->add_animation("IDLE", 20.f, 0, 0, 5, 0, 16, 16);
	this->animation_component->add_animation("RUN", 8.f, 0, 1, 5, 1, 16, 16);
	this->animation_component->add_animation("ATTACK", 10.f, 0, 2, 2, 2, 25, 16);
}

void Slime::text_init(){
	this->info_text.setPosition(this->get_position().x + 80.f, this->get_position().y - 20.f);
	this->info_text.setFillColor(sf::Color::White);
	this->info_text.setFont(this->font);
	this->info_text.setCharacterSize(15);
}

void Slime::font_init(){
	// Inicjalizacja fontów
	if (!this->font.loadFromFile("Fonts/PressStart2P_1.ttf")) {
		throw("ERROR: GAMESTATE NO FONT LOADED");
	}
}



// Methods
void Slime::update_animation(const float & dt) {
	// Przypisanie animacji do stanów przeciwnika

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

void Slime::update_text(const float & dt){
	this->info_text.setPosition(this->get_position().x + 80.f, this->get_position().y - 20.f);
	std::stringstream ss;

	ss	<< "Enemy: " << "Slime\n" 
		//<< "Pos: " << this->get_grid_position(64.f).x << ":" << this->get_grid_position(64.f).y << "\n" 
		<< "HP: " << this->attributes_component->hp << "/" << this->attributes_component->hp_max << "\n";
	//std::cout << ss.str();
	this->info_text.setString(ss.str());
}

void Slime::update(const float& dt, sf::Vector2f& mouse_pos_view) {

	this->movement_component->update(dt);
	//this->update_attack();
	this->update_animation(dt);
	this->hitbox_component->update();
	this->update_text(dt);

}

void Slime::render(sf::RenderTarget & target, sf::Shader* shader, const bool show_hitbox) {
	
	target.draw(this->sprite, shader);
	target.draw(this->info_text);

	if (show_hitbox)
		this->hitbox_component->render(target);
}
