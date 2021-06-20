#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data){

	this->variables_init();
	this->fonts_init();
	this->key_binds_init();
	this->gui_init();
	this->reset_gui();
}

MainMenuState::~MainMenuState() {
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

// Init
void MainMenuState::variables_init(){

}

void MainMenuState::key_binds_init() {
	std::ifstream key_f("Config/mainmenustate_keybinds.ini");

	if (key_f.is_open()) {
		std::string key = "";
		std::string key_val = "";

		while (key_f >> key >> key_val) {
			this->key_binds[key] = this->keys->at(key_val);
		}
	}

	key_f.close();
}

void MainMenuState::fonts_init(){
	if (!this->font.loadFromFile("Fonts/PressStart2P_1.ttf")) {
		throw("ERROR: MAINMENUSTATE NO FONT LOADED");
	}
}

void MainMenuState::gui_init(){
	
	const sf::VideoMode& vm = this->state_data->gf_settings->resolution;

	// init tla menu glownego
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->background_texture.loadFromFile("Resources/Images/Backgrounds/background1.png")) {
		throw "ERROR: MAIN_MENU_STATE FAILED TO LOAD BACKGROUND";
	}

	this->background.setTexture(&this->background_texture);

	// Init t³a dla przycisków
	this->btn_background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width / 4),
			static_cast<float>(vm.height)
		)
	);
	this->btn_background.setPosition(gui::p2p_x(2.f, vm), 0.f);
	this->btn_background.setFillColor(sf::Color(10, 10, 10, 100));


	// Init przycisków
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2p_x(8.f, vm), gui::p2p_y(25.f, vm),
		gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm),
		"Start", &this->font, gui::calc_font_size(vm),
		sf::Color(230, 230, 230, 220), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2p_x(8.f, vm), gui::p2p_y(35.f, vm),
		gui::p2p_x(13.f, vm), gui:: p2p_y(6.f, vm),
		"Settings", &this->font, gui::calc_font_size(vm),
		sf::Color(230, 230, 230, 220), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2p_x(8.f, vm), gui::p2p_y(45.f, vm),
		gui:: p2p_x(13.f, vm), gui:: p2p_y(6.f, vm),
		"Editor", &this->font, gui::calc_font_size(vm),
		sf::Color(230, 230, 230, 220), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2p_x(8.f, vm), gui::p2p_y(60.f, vm),
		gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm),
		"Quit", &this->font, gui::calc_font_size(vm),
		sf::Color(230, 230, 230, 220), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void MainMenuState::reset_gui(){
	for (auto it : this->buttons) {
		delete it.second;
	}
	this->buttons.clear();
	this->gui_init();
}


// Updates
void MainMenuState::update_input(const float & dt) {

}

void MainMenuState::update_gui(){
	// Aktualizacja stanu przyciskow
	for (auto &it : this->buttons) {
		it.second->update(this->mouse_pos_window);
	}

	/*Funkcje przyciskow*/
	// New game
	if (this->buttons["GAME_STATE"]->is_pressed()) {
		this->states->push(new GameState(this->state_data));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->is_pressed()) {
		this->states->push(new SettingsState(this->state_data));
	}

	// Editor
	if (this->buttons["EDITOR_STATE"]->is_pressed()) {
		this->states->push(new EditorState(this->state_data));
	}

	// Quit game
	if (this->buttons["EXIT_STATE"]->is_pressed()) {
		this->end_state();
	}
}

void MainMenuState::update(const float &dt) {

	this->update_mouse_pos();
	this->update_input(dt);

	this->update_gui();
}

// Renders
void MainMenuState::render_gui(sf::RenderTarget& target) {


	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {

	if (!target) target = this->window;

	target->draw(this->background);

	target->draw(this->btn_background);

	this->render_gui(*target);

	// FOR DEBUG ONLY
	//sf::Text mouse_text;
	//mouse_text.setPosition(this->mouse_pos_view.x, this->mouse_pos_view.y + 20);
	//mouse_text.setFont(this->font);
	//mouse_text.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mouse_pos_view.x << " " << this->mouse_pos_view.y;
	//mouse_text.setString(ss.str());

	//target->draw(mouse_text);
}
