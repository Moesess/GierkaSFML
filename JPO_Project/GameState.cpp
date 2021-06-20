#include "stdafx.h"
#include "GameState.h"

GameState::GameState(StateData* state_data)
	:State(state_data){

	this->render_def_init();
	this->view_init();
	this->key_binds_init();
	this->fonts_init();
	this->textures_init();
	this->pause_menu_init();

	this->shaders_init();

	this->player_init();
	this->player_gui_init();
	this->enemy_system_init();
	this->tile_map_init();

}

GameState::~GameState(){
	delete this->pmenu;
	delete this->player;
	delete this->player_gui;
	delete this->enemy_system;
	delete this->tile_map;

	for (size_t i = 0; i < this->active_enemies.size(); i++)
	{
		delete this->active_enemies[i];
	}

	
}

// Init
void GameState::render_def_init(){
	// Inicjalizacja tekstury do wyrenderowania na ca³¹ mapê, 
	// pozwala to unikniêcia buga w sfml który sprawia ¿e pomiêdzy p³ytkami przy ruchu mog¹ pojawiæ siê przerwy

	this->render_texture.create(
		this->state_data->gf_settings->resolution.width,
		this->state_data->gf_settings->resolution.height
	);

	this->render_sprite.setTexture(this->render_texture.getTexture());
	this->render_sprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->state_data->gf_settings->resolution.width,
			this->state_data->gf_settings->resolution.height)
	);

}

void GameState::view_init() {
	// Inicjalizacja widoku, ustawiamy wielkoœæ i centrum.

	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->state_data->gf_settings->resolution.width),
		static_cast<float>(this->state_data->gf_settings->resolution.height))
	);

	this->view.setCenter(sf::Vector2f(
		static_cast<float>(this->state_data->gf_settings->resolution.width) / 2.f,
		static_cast<float>(this->state_data->gf_settings->resolution.height) / 2.f
	));
}

void GameState::key_binds_init(){
	// Za³adowanie przypisanych klawiszy z pliku konfiguracyjnego

	std::ifstream key_f("Config/gamestate_keybinds.ini");
	if (key_f.is_open()) {
		std::string key = "";
		std::string key_val ="";

		while (key_f >> key >> key_val) {
			this->key_binds[key] = this->keys->at(key_val);
		}
	}

	key_f.close();
}

void GameState::fonts_init() {
	// Inicjalizacja fontów
	if (!this->font.loadFromFile("Fonts/PressStart2P_1.ttf")) {
		throw("ERROR: GAMESTATE NO FONT LOADED");
	}
}

void GameState::tile_map_init(){
	// Inicjalizacja mapy, wielkosæ tile, x, y, plik tekstur
	//this->tile_map = new TileMap(this->state_data->grid_size, 100, 100, "Resources/Images/Tiles/tile_sheet2.png");
	//this->tile_map->load_from_file("map.jpo");

	this->tile_map = new TileMap("map.jpo");
}

void GameState::enemy_system_init(){
	this->enemy_system = new EnemySystem(this->active_enemies, this->textures);
}

void GameState::textures_init(){
	// Inicjalizacja pliku z teksturami
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player_sheet.png")) {
		throw "ERROR: GAME_STATE COULND'T LOAD PLAYER TEXTURE";
	}
	if (!this->textures["ENEMY_SLIME_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/Slime/slime_sprite_sheet.png")) {
		throw "ERROR: GAME_STATE COULND'T LOAD ENEMY_SHEET";
	}
}

void GameState::player_init(){
	// Inicjalizacja gracza
	this->player = new Player(200, 200, this->textures["PLAYER_SHEET"]);
}

void GameState::player_gui_init(){
	this->player_gui = new PlayerGui(this->player, this->state_data->gf_settings->resolution);
}

void GameState::pause_menu_init(){
	// Inicjalizacja menu pauzy.
	const sf::VideoMode& vm = this->state_data->gf_settings->resolution;
	this->pmenu = new PauseMenu(this->state_data->gf_settings->resolution, this->font);

	this->pmenu->add_button("QUIT", gui::p2p_y(74.f, vm), gui::p2p_x(13.f, vm), gui::p2p_y(6.f, vm), gui::calc_font_size(vm), "Quit");
}

void GameState::shaders_init(){
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")) {
		std::cout << "ERROR: GAMESTATE COULDNT LOAD SHADERS\n";
	}
}

// Methods
void GameState::update_view(const float & dt){
	// Centrujemy widok na postaci gracza i u¿ywamy funkcji floor, do zaokr¹glenia koordynat do 1 miejsca po przecinku. Pomaga w tych przerwach miêdzy blokami

	this->view.setCenter(
		std::floor(this->player->get_position().x + (static_cast<float>(this->mouse_pos_window.x) - static_cast<float>(this->state_data->gf_settings->resolution.width / 2)) / 10.f),
		std::floor(this->player->get_position().y + (static_cast<float>(this->mouse_pos_window.y) - static_cast<float>(this->state_data->gf_settings->resolution.height / 2)) / 10.f)
	);

	// Kamera nie wychodzi poza granice mapy
	if (this->view.getSize().x <= this->tile_map->get_max_world_grid_size_f().x) {
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}

		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tile_map->get_max_world_grid_size_f().x)
		{
			this->view.setCenter(this->tile_map->get_max_world_grid_size_f().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->view.getSize().y <= this->tile_map->get_max_world_grid_size_f().y) {
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f) {
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}

		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tile_map->get_max_world_grid_size_f().y) {
			this->view.setCenter(this->view.getCenter().x, this->tile_map->get_max_world_grid_size_f().y - this->view.getSize().y / 2.f);
		}

	}

	this->view_grid_pos.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->grid_size);
	this->view_grid_pos.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->grid_size);
}

void GameState::update_input(const float & dt){

	// Przypisujemy klawisz escape do menu pauzy. Powinienem zmieniæ nazwê z QUIT na escape
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("QUIT"))) and this->get_keytime()) {
		if (!this->paused)
			this->pause_state();
		else {
			if(!this->pmenu->get_loose())
				this->unpause_state();
			if (!this->pmenu->get_win()) {
				this->unpause_state();
			}
		}
			
	}
}

void GameState::update_pause_menu_buttons(){

	// Nadajemy funkcje przyciskom w menu pauzy
	if (this->pmenu->is_button_pressed("QUIT"))
		this->end_state();
}

void GameState::update_player_input(const float & dt){

	// Przypisujemy klawisze do ruchów postaci gracza.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_LEFT")))) {
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->key_binds.at("MOVE_RIGHT")))) {
		this->player->move(1.f, 0.f, dt);
		//if (this->get_keytime())
		//	this->player->gain_exp(10);
	}
}

void GameState::update_tile_map(const float & dt){

	this->tile_map->update_world_border_collision(this->player, dt);
	this->tile_map->update_tile_collision(this->player, dt);
	this->tile_map->update_tiles(this->player, dt, *this->enemy_system);
}

void GameState::update_player_gui(const float & dt){
	this->player_gui->update(dt);
}

void GameState::update_player(const float & dt){

}

void GameState::update_enemies(const float & dt){
	srand(time(NULL));

	unsigned index = 0;

	for (auto* enemy : this->active_enemies) {
		//std::cout << "SPAWN: " << &enemy << "\n";

		float x = -2.f + rand() % (5 - 2 + 2);
		float y = -2.f + rand() % (5 - 2 + 2);

		//std::cout << "x:y " << x << ":" << y << "\n";
		enemy->update(dt, this->mouse_pos_view);

		enemy->move(x, y, dt);

		this->tile_map->update_world_border_collision(enemy, dt);
		
		this->tile_map->update_tile_collision(enemy, dt);

		this->update_combat(enemy, index, dt);

		if (enemy->is_dead()) {

			this->player->gain_exp(enemy->get_exp_gain());

			this->active_enemies.erase(this->active_enemies.begin() + index);
			--index;
		}


		++index;
	}
	if (index <= 0) {
		//std::cout << "Count: 0\n";
		this->pmenu->set_win();
		this->pause_state();
		this->player_gui->update(dt);
	}
	//for (int i = 0; i < this->active_enemies.size(); i++) {
	//	std::cout << "ADD: " << &active_enemies[i] << "\n";
	//}
}

void GameState::update_combat(Enemy* enemy, const int index, const float & dt){
	//std::cout << "CHECK: " << active_enemies[index] << "\n";
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->player->attacking = true;

		//std::cout << "UDERZONO SLIME " << &enemy << " " <<  << "\n";
	
		if (//this->player->get_weapon()->get_attack_timer()
			enemy->get_global_bounds().contains(this->mouse_pos_view)
			and enemy->get_distance(*this->player) <= 1.5f * this->player->get_weapon()->get_range()) {
			//std::cout << "UDERZONO SLIME " << &en << " " << &(*enemy) << "\n";
			enemy->take_damage(this->player->get_weapon()->get_damage_min() * this->player->get_attributes_component()->strength);
			//std::cout << enemy->get_attribute_comp()->hp << "\n";
		}

		//std::cout << "DAMAGE: " << this->player->get_weapon()->get_damage_min() * this->player->get_attributes_component()->strength << "\n";
	}

	if (enemy->get_global_bounds().intersects(this->player->get_global_bounds()) and this->player->get_damage_timer())
	{
		//std::cout << "UDERZONO GRACZA " << &enemy << " " << &*enemy << "\n";
		int dmg = enemy->get_attribute_comp()->damage_min;
		this->player->loose_hp(dmg);

		if (this->player->get_attributes_component()->hp <= 0) {
			this->pmenu->set_loose();
			this->pause_state();
			this->player_gui->update(dt);
		}
	}

	//std::cout << "Count: " << this->active_enemies.size() << "\n";
}

void GameState::update(const float &dt){
	this->update_mouse_pos(&this->view);
	this->update_keytime(dt);
	this->update_input(dt);

	// Odpauzowany widok
	if (!this->paused) {
		this->update_view(dt);

		this->update_player_input(dt);

		this->update_tile_map(dt);

		this->player->update(dt, this->mouse_pos_view);

		this->player_gui->update(dt);

		this->update_enemies(dt);

	}
	// Zapauzowany widok
	else {
		this->pmenu->update(this->mouse_pos_window);
		this->update_pause_menu_buttons();
	}
}

void GameState::render(sf::RenderTarget* target){
	// Wyczyœæ mapê, wyrenderuj wszystko do render_texture i wyrenderuj t¹ teksture, dziêki temu nie ma tych przerw miêdzy tiles.
	if (!target) 
		target = this->window;
	
	// Wyczyœæ ekran
	this->render_texture.clear();

	// Mapa
	this->render_texture.setView(this->view);
	this->tile_map->render(
		this->render_texture,
		this->view_grid_pos,
		nullptr,
		sf::Vector2f(), 
		false
	);

	// Przeciwnicy
	for (auto *enemy : this->active_enemies) {
		enemy->render(this->render_texture, nullptr, true);
	}

	// Gracz
	this->player->render(this->render_texture, &this->core_shader, true);

	// OpóŸnione tile
	//this->tile_map->render_delayed_tiles(this->render_texture, &this->core_shader, this->player->get_center());
	this->tile_map->render_delayed_tiles(this->render_texture, nullptr, sf::Vector2f());

	// Player gui
	this->render_texture.setView(this->render_texture.getDefaultView());
	this->player_gui->render(this->render_texture);

	if (this->paused) {
		//this->render_texture.setView(this->render_texture.getDefaultView());
		this->pmenu->render(this->render_texture);
	}

	// Main render
	this->render_texture.display();
	this->render_sprite.setTexture(this->render_texture.getTexture());
	target->draw(this->render_sprite);	
}
