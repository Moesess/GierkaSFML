#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
	:State(state_data){
	this->variables_init();
	this->fonts_init();
	this->key_binds_init();
	this->gui_init();
}

SettingsState::~SettingsState(){
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

	for (auto it = this->dropdowns.begin(); it != this->dropdowns.end(); ++it) {
		delete it->second;
	}
}


// Private Methods
void SettingsState::variables_init() {
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::key_binds_init() {
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

void SettingsState::fonts_init() {
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		throw("ERROR: MAINMENUSTATE NO FONT LOADED");
	}
}

void SettingsState::gui_init() {
	const sf::VideoMode& vm = this->state_data->gf_settings->resolution;

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

	this->buttons["BACK"] = new gui::Button(
		gui::p2p_x(78.f, vm), gui::p2p_y(80.f, vm)+2.f,
		gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm),
		"Back", &this->font, gui::calc_font_size(vm),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2p_x(65.f, vm), gui::p2p_y(80.f, vm),
		gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm),
		"Apply", &this->font, gui::calc_font_size(vm),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &it : this->modes) {
		modes_str.push_back(std::to_string(it.width) + 'x' + std::to_string(it.height));
	}

	this->dropdowns["RESOLUTION"] = new gui::DropDownList(
		gui::p2p_x(40.f, vm), gui::p2p_y(40.f, vm),
		gui::p2p_x(10.f, vm), gui::p2p_y(5.f, vm)
		, modes_str.data(), font, modes_str.size());

	// Text
	this->options_text.setFont(this->font);
	this->options_text.setPosition(sf::Vector2f(gui::p2p_x(5.f, vm), gui::p2p_y(41.f, vm)));
	this->options_text.setCharacterSize(gui::calc_font_size(vm, 80));
	this->options_text.setFillColor(sf::Color(255, 255, 255, 200));

	this->options_text.setString(
		"Resolution \n\nFullScreen \n\nVsync \n\nAntiAliasing"
	);
}

void SettingsState::reset_gui() {
	for (auto it : this->buttons) {
		delete it.second;
	}
	this->buttons.clear();

	for (auto it : this->dropdowns) {
		delete it.second;
	}
	this->dropdowns.clear();

	this->gui_init();
}

// Public Methods
void SettingsState::update_input(const float & dt) {

}

void SettingsState::update_gui(const float& dt) {
	// Aktualizacja stanu przyciskow
	for (auto &it : this->buttons) {
		it.second->update(this->mouse_pos_window);
	}

	/*Funkcje przyciskow*/

	// Quit 
	if (this->buttons["BACK"]->is_pressed()) {
		this->end_state();
	}

	// Apply settings
	if (this->buttons["APPLY"]->is_pressed()) {
	
		this->state_data->gf_settings->resolution = this->modes[this->dropdowns["RESOLUTION"]->get_active_id()];
	
		this->window->create(this->state_data->gf_settings->resolution, this->state_data->gf_settings->title, sf::Style::Default);

		this->reset_gui();
	}

	// Aktualizacja list
	for (auto &it : this->dropdowns) {
		it.second->update(this->mouse_pos_window, dt);
	}

	/*DROPDOWNS FUNCTIONS*/
	

}

void SettingsState::update(const float &dt) {

	this->update_mouse_pos();
	this->update_input(dt);

	this->update_gui(dt);
}

// Renders
void SettingsState::render(sf::RenderTarget* target) {

	if (!target) target = this->window;

	target->draw(this->background);

	this->render_gui(*target);

	target->draw(this->options_text);

	// FOR DEBUG ONLY
	sf::Text mouse_text;
	mouse_text.setPosition(this->mouse_pos_view.x, this->mouse_pos_view.y + 20);
	mouse_text.setFont(this->font);
	mouse_text.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mouse_pos_view.x << " " << this->mouse_pos_view.y;
	mouse_text.setString(ss.str());

	target->draw(mouse_text);
}

void SettingsState::render_gui(sf::RenderTarget& target) {

	for (auto &it : this->buttons) {
		it.second->render(target);
	}

	for (auto &it : this->dropdowns) {
		it.second->render(target);
	}
}