#include "stdafx.h"
#include "Gui.h"

// BUTTON ==================================================
// Metody do obliczania procentów dla ró¿nych rozdzielczoœci ekranu
const float gui::p2p_x(const float percent, const sf::VideoMode& vm) {
	return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float gui::p2p_y(const float percent, const sf::VideoMode& vm) {
	return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}

const unsigned gui::calc_font_size(const sf::VideoMode& vm, const unsigned modifier) {
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}


gui::Button::Button(float x, float y, float width, float height,
	std::string text, sf::Font * font, unsigned character_size,
	sf::Color text_color_idle, sf::Color text_color_hover, sf::Color text_color_active,
	sf::Color color_idle, sf::Color color_hover, sf::Color color_active,
	sf::Color outline_color_idle, sf::Color outline_color_hover, sf::Color outline_color_active,
	short unsigned id){
	
	this->button_state = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color_idle);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_color_idle);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_color_idle);
	this->text.setCharacterSize(character_size);
	
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y
	);

	this->text_color_idle = text_color_idle;
	this->text_color_hover = text_color_hover;
	this->text_color_active = text_color_active;

	this->color_idle = color_idle;
	this->color_hover = color_hover;
	this->color_active = color_active;

	this->outline_color_idle = outline_color_idle;
	this->outline_color_hover = outline_color_hover;
	this->outline_color_active = outline_color_active;
}

gui::Button::~Button(){

}

// Getters
const bool gui::Button::is_pressed() const
{
	if (this->button_state == BTN_ACTIVE) 
		return true;

	return false;
}

const std::string gui::Button::get_text() const{

	return this->text.getString();
}

const short unsigned gui::Button::get_id() const{
	return this->id;
}

// Setters
void gui::Button::set_text(const std::string text){

	this->text.setString(text);
}

void gui::Button::set_id(const short unsigned id){
	this->id = id;
}

// Methods
void gui::Button::render(sf::RenderTarget & target){
	target.draw(this->shape);
	target.draw(this->text);
}

void gui::Button::update(sf::Vector2i& mouse_pos_window){
	// Ustawiam default stan przycisku
	this->button_state = BTN_IDLE;

	// Sprawdzam czy mysz najecha³a na przycisk
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window))) {
		this->button_state = BTN_HOVER;

		// Sprawdzam czy klikniety
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->button_state = BTN_ACTIVE;
		}
	}

	switch (this->button_state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->color_idle);
		this->shape.setOutlineColor(this->outline_color_idle);
		this->text.setFillColor(this->text_color_idle);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->color_hover);
		this->shape.setOutlineColor(this->outline_color_hover);
		this->text.setFillColor(this->text_color_hover);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->color_active);
		this->shape.setOutlineColor(this->outline_color_active);
		this->text.setFillColor(this->text_color_active);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setOutlineColor(sf::Color::Yellow);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

// DROPDOWN ==================================================

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	std::string list[], sf::Font& font,
	unsigned nr_of_elements, unsigned default_index)
	:font(font), showed(false), keytime_max(1.f), keytime(0.f){

	this->active = new gui::Button(
		x, y, width, height,
		list[default_index], &this->font, 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(150, 150, 150, 50),
		sf::Color(50, 50, 50, 200), sf::Color(70, 70, 70, 200), sf::Color(30, 30, 30, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(30, 30, 30, 255)
	);

	for (unsigned i = 0; i < nr_of_elements; i++){
		
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height,
				list[i], &this->font, 14,
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(150, 150, 150, 150),
				sf::Color(50, 50, 50, 200), sf::Color(70, 70, 70, 200), sf::Color(30, 30, 30, 200),
				sf::Color(50, 50, 50, 0), sf::Color(70, 70, 70, 0), sf::Color(30, 30, 30, 0),
				i
			)
		);

	}
}

gui::DropDownList::~DropDownList(){
	
	delete this->active;
	
	for (size_t i = 0; i < this->list.size(); i++){

		delete this->list[i];
	}
}

// Getters
const bool gui::DropDownList::get_keytime(){
	if (this->keytime >= this->keytime_max) {
		this->keytime = 0.f;
		return true;
	}
		
	return false;
}

const unsigned short gui::DropDownList::get_active_id() const{
	return this->active->get_id();
}

// Methods

void gui::DropDownList::render(sf::RenderTarget & target){

	this->active->render(target);

	if (this->showed) {
		for (auto &it : this->list) {
			it->render(target);
		}
	}
}

void gui::DropDownList::update(sf::Vector2i & mouse_pos_window, const float& dt){
	
	this->update_keytime(dt);
	this->active->update(mouse_pos_window);

	// Chowanie i wyswietlanie listy
	if (this->active->is_pressed() and this->get_keytime()) {
		if(this->showed)
			this->showed = false;
		else
			this->showed = true;
	}

	if (this->showed) {
		for (auto &it : this->list) {
			it->update(mouse_pos_window);

			if (it->is_pressed() and this->get_keytime()) {
				this->showed = false;
				this->active->set_text(it->get_text());
				this->active->set_id(it->get_id());
			}
		}
	}

}

void gui::DropDownList::update_keytime(const float& dt){
	if (this->keytime < this->keytime_max) {
		this->keytime += 10.f * dt;
	}
}


// TEXTURE SELECTOR ===============================================
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
	float grid_size, float tile_res, const sf::Texture* texture_sheet,
	sf::Font& font, std::string text):keytime_max(1.f), keytime(0.f){

	this->active = false;
	this->grid_size = grid_size;
	this->tile_res = tile_res;
	this->hidden = true;
	float offset_x = 100.f;
	float offset_y = 10.f;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset_x, y + offset_y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset_x, y + offset_y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x + offset_x, y + offset_y);
	this->selector.setSize(sf::Vector2f(tile_res, tile_res));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->texture_rect.width = static_cast<int>(tile_res);
	this->texture_rect.height = static_cast<int>(tile_res);

	this->hide_btn = new gui::Button(
		x+15.f, y+10.f, 50.f, 50.f,
		text, &font, 16,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

gui::TextureSelector::~TextureSelector(){
	delete this->hide_btn;
}


// Getters
const bool & gui::TextureSelector::get_active() const{
	return this->active;
}

const sf::IntRect & gui::TextureSelector::get_texture_rect() const{
	return this->texture_rect;
}

void gui::TextureSelector::var_init(){
	
}

const bool gui::TextureSelector::get_keytime() {
	if (this->keytime >= this->keytime_max) {
		this->keytime = 0.f;
		return true;
	}

	return false;
}

// Methods
void gui::TextureSelector::update_keytime(const float& dt) {
	if (this->keytime < this->keytime_max) {
		this->keytime += 10.f * dt;
	}
}

void gui::TextureSelector::update(sf::Vector2i& mouse_pos_window, const float& dt){

	this->update_keytime(dt);
	this->hide_btn->update(mouse_pos_window);

	if (this->hide_btn->is_pressed() and this->get_keytime()) {
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (!this->hidden) {
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window))) {
			this->active = true;
		}
		else this->active = false;

		// Je¿eli mysz najecha³a na menu z teksturami, zmieniamy kursor na odpowiedni

		if (this->active) {
			this->mouse_pos_grid.x = (mouse_pos_window.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->tile_res);
			this->mouse_pos_grid.y = (mouse_pos_window.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->tile_res);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mouse_pos_grid.x * this->tile_res,
				this->bounds.getPosition().y + this->mouse_pos_grid.y * this->tile_res
			);

			// Zmieniamy teksture któr¹ rysujemy
			this->texture_rect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->texture_rect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}

	
}

void gui::TextureSelector::render(sf::RenderTarget & target){

	if (!this->hidden) {
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}

	this->hide_btn->render(target);
}

gui::ProgressBar::ProgressBar(
	float width_, float height_, float x_, float y_,
	int max_value, unsigned font_size, sf::Color inner_color,
	sf::VideoMode& vm, sf::Font* font){
	float width = gui::p2p_x(width_, vm);
	float height = gui::p2p_y(height_, vm);
	float x = gui::p2p_x(x_, vm);
	float y = gui::p2p_y(y_, vm);

	this->max_width = width;
	this->max_value = max_value;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition(x, y);

	this->fill.setSize(sf::Vector2f(width, height));
	this->fill.setFillColor(inner_color);
	this->fill.setPosition(this->back.getPosition().x + gui::p2p_x(0.06f, vm), this->back.getPosition().y);

	if (font) {
		this->text.setFont(*font);
		this->text.setCharacterSize(gui::calc_font_size(vm, font_size));
		this->text.setPosition(
			this->fill.getPosition().x + gui::p2p_x(0.6f, vm),
			this->fill.getPosition().y + gui::p2p_y(0.6f, vm)
		);
	}
	
}

gui::ProgressBar::~ProgressBar(){

}

// Methods
void gui::ProgressBar::update(const int current_value, const int max_value) {
	this->max_value = max_value;
	float percent = static_cast<float>(current_value) / static_cast<float>(this->max_value);

	this->fill.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->max_width * percent)), this->fill.getSize().y
		)
	);
	this->string = std::to_string(current_value) + " / " + std::to_string(this->max_value);
	this->text.setString(this->string);
}

void gui::ProgressBar::render(sf::RenderTarget & target) {
	target.draw(this->back);
	target.draw(this->fill);
	target.draw(this->text);
}