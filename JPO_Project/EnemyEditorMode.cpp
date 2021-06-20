#include "stdafx.h"
#include "EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data):
	EditorMode(state_data, tile_map, editor_state_data){

	this->variables_init();
	this->gui_init();
}

EnemyEditorMode::~EnemyEditorMode(){

}

// Init
void EnemyEditorMode::gui_init() {
	// init tekstu wyswietlanego obok kursora

	this->cursor_text.setPosition(this->editor_state_data->mouse_pos_view->x, this->editor_state_data->mouse_pos_view->y + 20.f);
	this->cursor_text.setFillColor(sf::Color::White);
	this->cursor_text.setFont(*this->editor_state_data->font);
	this->cursor_text.setCharacterSize(20);

	// Init GUI, pasek boczny, kursor myszy, oraz  menu wyboru tekstur
	this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->state_data->gf_settings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selector_shape.setSize(sf::Vector2f(this->state_data->grid_size, this->state_data->grid_size));
	this->selector_shape.setFillColor(sf::Color::Color(255, 255, 255, 150));

	this->selector_shape.setOutlineThickness(1.f);
	this->selector_shape.setOutlineColor(sf::Color::Blue);
}

void EnemyEditorMode::variables_init(){
	this->type = 0;
	this->amount = 1;
	this->time_to_spawn = 20;
	this->max_distance = 1000.f;
}

// Methods
void EnemyEditorMode::update_input(const float & dt){
	// Dodawanie tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->get_keytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editor_state_data->mouse_pos_window))) {

			this->tile_map->add_tile(
				this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0,
				this->texture_rect, this->type, this->amount, this->time_to_spawn, this->max_distance
			);
			
		}
	}

	// Usuwanie tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and this->get_keytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editor_state_data->mouse_pos_window))) {

			this->tile_map->remove_tile(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0, TileTypes::ENEMY_SPAWNER);
		}
	}

	// Ustawianie Typu przeicwnika
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("TYPE_UP"))) and this->get_keytime()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (this->type > 0)
				this->type--;
		}
		else if (this->type < 100)
			this->type++;

		else 
			this->type = 0;
	}

	// Ustawianie ilosci przeciwnikow
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("AMOUNT_UP"))) and this->get_keytime()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (this->amount > 0)
				this->amount--;
		}
		else if (this->amount < 100)
			this->amount++;
		else
			this->amount = 0;
	}

	// Ustawianie Czasu spawnowania
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("TTS_UP"))) and this->get_keytime()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (this->time_to_spawn > 0)
				this->time_to_spawn--;
		}
		else if (this->time_to_spawn < 100)
			this->time_to_spawn++;
		else 
			this->time_to_spawn = 0;
	}

	// Ustawianie odleg³oœci spawnowania
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("MD_UP")))) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (this->max_distance > 0)
				this->max_distance--;
		}
		else if (this->max_distance < 1000)
			this->max_distance++;
		else
			this->max_distance = 0;
	}
}

void EnemyEditorMode::update_gui(const float & dt){
	this->selector_shape.setPosition(this->editor_state_data->mouse_pos_grid->x * this->state_data->grid_size, this->editor_state_data->mouse_pos_grid->y * this->state_data->grid_size);
	
	this->cursor_text.setPosition(this->editor_state_data->mouse_pos_view->x + 30.f, this->editor_state_data->mouse_pos_view->y + 20.f);

	std::stringstream ss;

	ss <<
		"Type: " << this->type << "\n" <<
		"Amount: " << this->amount <<"\n" <<
		"Time to spawn: " << this->time_to_spawn << "\n" <<
		"Max distance: " << this->max_distance << "\n";

	this->cursor_text.setString(ss.str());
}

void EnemyEditorMode::update(const float & dt){
	this->update_input(dt);
	this->update_gui(dt);
}

void EnemyEditorMode::render_gui(sf::RenderTarget & target){
	target.setView(*this->editor_state_data->view);
	target.draw(this->selector_shape);
	target.draw(this->cursor_text);

	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget & target){
	this->render_gui(target);
}
