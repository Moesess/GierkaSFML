#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
	:State(state_data) {
	this->texture_res = 32.f;

	this->variables_init();
	this->editor_state_data_init();
	this->view_init();
	this->fonts_init();
	this->key_binds_init();
	this->pause_menu_init();
	this->buttons_init();
	this->tile_map_init();
	this->gui_init();

	this->modes_init();
}

EditorState::~EditorState() {
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

	delete this->pmenu;
	delete this->tile_map;

	for (size_t i = 0; i < this->modes.size(); i++){
		delete this->modes[i];
	}
}

// Init
void EditorState::variables_init() {
	this->camera_speed = 900.f;
}

void EditorState::editor_state_data_init(){
	this->editor_state_data.view = &this->view;
	this->editor_state_data.font = &this->font;
	this->editor_state_data.keytime = &this->keytime;
	this->editor_state_data.keytime_max = &this->keytime_max;
	this->editor_state_data.key_binds = &this->key_binds;
	this->editor_state_data.mouse_pos_grid = &this->mouse_pos_grid;
	this->editor_state_data.mouse_pos_view = &this->mouse_pos_view;
	this->editor_state_data.mouse_pos_screen = &this->mouse_pos_screen;
	this->editor_state_data.mouse_pos_window = &this->mouse_pos_window;
	
}

void EditorState::view_init(){
	// Init widoku, jego wielkosc i centrowanie

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->state_data->gf_settings->resolution.width),
		static_cast<float>(this->state_data->gf_settings->resolution.height)
	));
	this->view.setCenter(
		static_cast<float>(this->state_data->gf_settings->resolution.width) / 2.f,
		static_cast<float>(this->state_data->gf_settings->resolution.height) / 2.f
	);
}

void EditorState::key_binds_init() {
	// zaladowanie zbindowanych klawiszy z pliku

	std::ifstream key_f("Config/editorstate_keybinds.ini");

	if (key_f.is_open()) {
		std::string key = "";
		std::string key_val = "";

		while (key_f >> key >> key_val) {
			this->key_binds[key] = this->keys->at(key_val);
		}
	}

	key_f.close();
}

void EditorState::fonts_init() {
	if (!this->font.loadFromFile("Fonts/PressStart2P_1.ttf")) {
		throw("ERROR: EDITORSTATE NO FONT LOADED");
	}
}

void EditorState::buttons_init() {
}

void EditorState::pause_menu_init() {
	const sf::VideoMode& vm = this->state_data->gf_settings->resolution;
	this->pmenu = new PauseMenu(this->state_data->gf_settings->resolution, this->font);

	this->pmenu->add_button("QUIT", gui::p2p_y(74.f, vm), gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm), gui::calc_font_size(vm), "Quit");
	this->pmenu->add_button("LOAD", gui::p2p_y(46.f, vm), gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm), gui::calc_font_size(vm), "Load");
	this->pmenu->add_button("SAVE", gui::p2p_y(37.f, vm), gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm), gui::calc_font_size(vm), "Save");
}

void EditorState::gui_init(){

}

void EditorState::tile_map_init(){
	this->tile_map = new TileMap(this->state_data->grid_size, 100, 100, "Resources/Images/Tiles/tile_sheet2.png");
}

void EditorState::modes_init(){
	this->modes.push_back(new DefaultEditorMode(this->state_data, this->tile_map, &this->editor_state_data));
	this->modes.push_back(new EnemyEditorMode(this->state_data, this->tile_map, &this->editor_state_data));

	this->active_mode = EditorModes::DEFAULT_EDITOR_MODE;
}

// Updates
void EditorState::update_input(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("QUIT"))) and this->get_keytime()) {
		if (!this->paused)
			this->pause_state();
		else
			this->unpause_state();
	}
}

void EditorState::update_editor_input(const float & dt){

	// Ruchy kamery
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CAMERA_UP")))) {
		this->view.move(0.f, -std::floor(this->camera_speed * dt));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CAMERA_DOWN")))) {
		this->view.move(0.f, std::floor(this->camera_speed * dt));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CAMERA_LEFT")))) {
		this->view.move(-std::floor(this->camera_speed * dt), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("CAMERA_RIGHT")))) {
		this->view.move(std::floor(this->camera_speed * dt), 0.f );
	}

	// Zmiana trybu edytora
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("EDITOR_MODE_UP")))) {
		if (this->active_mode < this->modes.size() - 1) {
			this->active_mode++;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("EDITOR_MODE_DOWN")))) {
		if (this->active_mode > 0) {
			this->active_mode--;
		}
	}
}

void EditorState::update_buttons() {
	// Sprawdzanie stanu przyciskow
	for (auto &it : this->buttons) {
		it.second->update(this->mouse_pos_window);
	}
}

void EditorState::update_pause_menu_buttons() {
	if (this->pmenu->is_button_pressed("QUIT") and this->get_keytime())
		this->end_state();

	if (this->pmenu->is_button_pressed("SAVE") and this->get_keytime())
		this->tile_map->save_to_file("map.jpo");

	if (this->pmenu->is_button_pressed("LOAD") and this->get_keytime())
		this->tile_map->load_from_file("map.jpo");
}

void EditorState::update_modes(const float & dt){
	this->modes[this->active_mode]->update(dt);
}

void EditorState::update_gui(const float& dt) {
}

void EditorState::update(const float &dt) {

	this->update_mouse_pos(&this->view);
	this->update_keytime(dt);
	this->update_input(dt);

	// Editor State
	if (!this->paused) {
		this->update_gui(dt);
		this->update_buttons();
		this->update_editor_input(dt);
		this->update_modes(dt);
	}
	// Pause Menu
	else {
		this->pmenu->update(this->mouse_pos_window);
		this->update_pause_menu_buttons();
	}
}


// Renders
void EditorState::render_buttons(sf::RenderTarget& target) {

	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::render_gui(sf::RenderTarget & target){
	
}

void EditorState::render_modes(sf::RenderTarget & target){
	this->modes[this->active_mode]->render(target);
}

void EditorState::render(sf::RenderTarget* target) {

	if (!target) target = this->window;
	
	target->setView(this->view);
	//this->tile_map->render(*target, this->mouse_pos_grid, nullptr, sf::Vector2f(), true);
	this->tile_map->render_whole(*target, true);
	this->tile_map->render_delayed_tiles(*target);

	target->setView(this->window->getDefaultView());
	this->render_buttons(*target);

	this->render_gui(*target);

	this->render_modes(*target);

	if (this->paused) {
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}

}