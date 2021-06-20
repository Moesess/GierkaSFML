#include "stdafx.h"
#include "PlayerGui.h"

PlayerGui::PlayerGui(Player* player, sf::VideoMode& vm):
	vm(vm) {
	this->player = player;

	this->font_init();
	this->level_bar_init();
	this->hp_bar_init();
	this->exp_bar_init();
}

PlayerGui::~PlayerGui() {
	delete this->hp_bar;
	delete this->exp_bar;
}

// Init
void PlayerGui::font_init(){
	this->font.loadFromFile("Fonts/PressStart2P_1.ttf");
}

void PlayerGui::level_bar_init(){
	float width = gui::p2p_x(2.f, this->vm);
	float height = gui::p2p_y(3.f, this->vm);
	float x = gui::p2p_x(1.f, this->vm);
	float y = gui::p2p_y(2.f, this->vm);

	this->lv_bar_back.setSize(sf::Vector2f(width, height));
	this->lv_bar_back.setFillColor(sf::Color(50, 50, 50, 200));
	this->lv_bar_back.setPosition(x, y);

	this->lv_bar_text.setFont(this->font);
	this->lv_bar_text.setCharacterSize(gui::calc_font_size(this->vm, 150));
	this->lv_bar_text.setPosition(
		this->lv_bar_back.getPosition().x + gui::p2p_x(0.55f, vm),
		this->lv_bar_back.getPosition().y + gui::p2p_y(0.7f, vm)
	);
}

void PlayerGui::hp_bar_init(){
	this->hp_bar = new gui::ProgressBar(
		20.f, 3.f, 1.f, 5.5f,
		this->player->get_attributes_component()->hp_max,
		150, sf::Color(255, 20, 20, 200),
		this->vm, &this->font);
}

void PlayerGui::exp_bar_init(){
	this->exp_bar = new gui::ProgressBar(
		20.f, 2.f, 1.f, 9.f,
		this->player->get_attributes_component()->exp_next,
		200, sf::Color(20, 255, 20, 200),
		this->vm, &this->font);
}

// Methods
void PlayerGui::update_hp_bar(){
	this->hp_bar->update(this->player->get_attributes_component()->hp, this->player->get_attributes_component()->hp_max);
}

void PlayerGui::update_lv_bar(){

	this->lv_bar_string = std::to_string(this->player->get_attributes_component()->level);
	this->lv_bar_text.setString(this->lv_bar_string);
}

void PlayerGui::update_exp_bar(){
	this->exp_bar->update(this->player->get_attributes_component()->exp, this->player->get_attributes_component()->exp_next);
}

void PlayerGui::update(const float & dt) {
	this->update_hp_bar();
	this->update_exp_bar();
	this->update_lv_bar();
}

void PlayerGui::render_hp_bar(sf::RenderTarget & target){
	hp_bar->render(target);
}

void PlayerGui::render_lv_bar(sf::RenderTarget & target){
	target.draw(this->lv_bar_back);
	target.draw(this->lv_bar_text);
}

void PlayerGui::render_exp_bar(sf::RenderTarget & target){
	this->exp_bar->render(target);
}

void PlayerGui::render(sf::RenderTarget & target) {
	this->render_lv_bar(target);
	this->render_hp_bar(target);
	this->render_exp_bar(target);
}