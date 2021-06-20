#include "stdafx.h"
#include "State.h"
State::State(StateData* state_data) {
	this->state_data = state_data;
	this->window = state_data->window;
	this->keys = state_data->keys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytime_max = 10.f;
	this->grid_size = state_data->grid_size;
	this->tile_res = state_data->tile_res;
}

State::~State() {

}

// Getters
const bool & State::get_quit(){

	return this->quit;
}

const bool State::get_keytime(){
	if (this->keytime >= this->keytime_max) {

		this->keytime = 0.f;
		return true;
	}
	return false;
}


// Methods
void State::update_mouse_pos(sf::View* view){
	this->mouse_pos_screen = sf::Mouse::getPosition();
	this->mouse_pos_window = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mouse_pos_view = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mouse_pos_grid = sf::Vector2i(
		static_cast<int>(this->mouse_pos_view.x) / static_cast<int>(this->grid_size),
		static_cast<int>(this->mouse_pos_view.y) / static_cast<int>(this->grid_size)
	);

	this->window->setView(this->window->getDefaultView());
}

void State::update_keytime(const float& dt){
	if (this->keytime < this->keytime_max)
		this->keytime += 50.f * dt;
}


// Zarzadzanie stanami
void State::pause_state(){
	this->paused = true;
}

void State::unpause_state(){
	this->paused = false;
}

void State::end_state(){
	this->quit = true;
}
