#include "stdafx.h"
#include "DefaultEditorMode.h"

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	:EditorMode(state_data, tile_map, editor_state_data){

	this->variables_init();
	this->gui_init();
}

DefaultEditorMode::~DefaultEditorMode(){
	delete this->texture_selector;
}


// Init
void DefaultEditorMode::variables_init() {
	// Init zmiennych do edytora, czy tile ktory dodajemy ma kolizje, typ, predkosc kamery etc.
	float percent = this->state_data->grid_size / this->texture_res;
	this->texture_rect = sf::IntRect(0, 0, static_cast<int>(this->state_data->grid_size / percent), static_cast<int>(this->state_data->grid_size / percent));

	this->colliding = false;
	this->type = TileTypes::DEFAULT;
	this->layer = 0;
	this->tile_lock = false;
}

void DefaultEditorMode::gui_init(){
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

	this->selector_shape.setTexture(this->tile_map->get_texture_sheet());
	this->selector_shape.setTextureRect(this->texture_rect);

	this->texture_selector = new gui::TextureSelector(
		0.f, 0.f, 448.f, 320.f,
		this->state_data->grid_size, 32.f, this->tile_map->get_texture_sheet(),
		*this->editor_state_data->font, "TILES");
}

// Methods
void DefaultEditorMode::update_input(const float & dt){
	// Dodawanie tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->get_keytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editor_state_data->mouse_pos_window))) {

			if (!this->texture_selector->get_active()) {
				if (this->tile_lock) {
					if (this->tile_map->tile_empty(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0))
						this->tile_map->add_tile(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0, this->texture_rect, this->colliding, this->type);
				}
				else
					this->tile_map->add_tile(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0, this->texture_rect, this->colliding, this->type);
			}

			else {
				this->texture_rect = this->texture_selector->get_texture_rect();
			}
		}
	}

	// Usuwanie tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and this->get_keytime()) {

		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editor_state_data->mouse_pos_window))) {

			if (!this->texture_selector->get_active())
				this->tile_map->remove_tile(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, 0);
		}
	}

	// Ustawianie kolizji Tile
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("TOGGLE_COLLISION"))) and this->get_keytime()) {
		if (this->colliding)
			this->colliding = false;
		else
			this->colliding = true;
	}

	// Ustawianie stanu tile
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("INC_TYPE"))) and this->get_keytime()) {
		// IF LIMIT TODO
		++this->type;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("DEC_TYPE"))) and this->get_keytime()) {
		if (this->type > 0)
			--this->type;
	}

	// Ustawianie blokady by nie mozna bylo dodac wiecej blokow na siebie
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editor_state_data->key_binds->at("TOGGLE_LOCK"))) and this->get_keytime()) {
		if (this->tile_lock)
			this->tile_lock = false;
		else
			this->tile_lock = true;
	}
}

void DefaultEditorMode::update_gui(const float & dt){
	// Aktualizacja danych przekazywanych do gui

	this->texture_selector->update(*this->editor_state_data->mouse_pos_window, dt);

	if (!this->texture_selector->get_active()) {
		this->selector_shape.setTextureRect(this->texture_rect);
		this->selector_shape.setPosition(this->editor_state_data->mouse_pos_grid->x * this->state_data->grid_size, this->editor_state_data->mouse_pos_grid->y * this->state_data->grid_size);
	}

	this->cursor_text.setPosition(this->editor_state_data->mouse_pos_view->x + 30.f, this->editor_state_data->mouse_pos_view->y + 20.f);
	std::stringstream ss;

	ss << this->editor_state_data->mouse_pos_view->x << " " << this->editor_state_data->mouse_pos_view->y << "\n" <<
		this->editor_state_data->mouse_pos_grid->x << " " << this->editor_state_data->mouse_pos_grid->y << "\n" <<
		this->texture_rect.left << " " << this->texture_rect.top << "\n" <<
		"Colliding: " << this->colliding << "\n" <<
		"Type: " << this->type << "\n" <<
		"Tiles: " << this->tile_map->get_layer_size(this->editor_state_data->mouse_pos_grid->x, this->editor_state_data->mouse_pos_grid->y, this->layer) << "\n" <<
		"Lock: " << this->tile_lock;

	this->cursor_text.setString(ss.str());
}

void DefaultEditorMode::update(const float & dt){
	this->update_input(dt);
	this->update_gui(dt);
}

void DefaultEditorMode::render_gui(sf::RenderTarget & target){
	if (!this->texture_selector->get_active()) {
		target.setView(*this->editor_state_data->view);
		target.draw(this->selector_shape);
	}

	target.setView(this->state_data->window->getDefaultView());
	this->texture_selector->render(target);
	target.draw(this->sidebar);

	target.setView(*this->editor_state_data->view);
	target.draw(this->cursor_text);
}

void DefaultEditorMode::render(sf::RenderTarget& target){
	this->render_gui(target);
}
