#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font): font(font){
	this->loose = false;

	// Ustawiamy t³o menu
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height))
	);

	this->background.setFillColor(sf::Color(20, 20, 20, 100));


	// Ustawiamy kontener do przechowywania menu
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height)
		)
	);

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	// Ustawiamy pozycje menu pauzy
	this->container.setPosition(
		static_cast<float>(vm.width) / 4.f - this->container.getSize().x / 2.f,
		0.f
	);

	// Init tekstu
	this->menu_text.setFont(font);
	this->menu_text.setFillColor(sf::Color(255, 255, 255, 255));
	this->menu_text.setCharacterSize(gui::calc_font_size(vm));
	this->menu_text.setString("MENU");
	this->menu_text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menu_text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2p_y(4.f, vm)
	);
}

PauseMenu::~PauseMenu(){
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

// Getters
std::map<std::string, gui::Button*>& PauseMenu::get_buttons(){
	return this->buttons;
}

const bool PauseMenu::get_loose() const{
	return this->loose;
}

const bool PauseMenu::get_win() const{
	return this->win;
}

// Methods
void PauseMenu::update(sf::Vector2i& mouse_position_window){
	for (auto &it : this->buttons) {
		it.second->update(mouse_position_window);
	}
}

void PauseMenu::set_loose(){
	this->loose = true;
	this->menu_text.setString("YOU LOST");
	this->menu_text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menu_text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f);
}

void PauseMenu::set_win(){
	this->win = true;
	this->menu_text.setString("YOU WON");
	this->menu_text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menu_text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f);
}

const bool PauseMenu::is_button_pressed(const std::string key){
	return this->buttons[key]->is_pressed();
}

void PauseMenu::add_button(const std::string key, const float y, const float width, const float height, const unsigned font_size, const std::string text){

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		text, &this->font, font_size,
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void PauseMenu::render(sf::RenderTarget & target){
	target.draw(background);
	target.draw(container);

	for (auto &it : this->buttons) {
		it.second->render(target);
	}

	target.draw(this->menu_text);
}