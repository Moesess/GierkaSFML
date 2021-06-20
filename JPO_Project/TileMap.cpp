#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear(){
	if (!this->map.empty()) {
		for (unsigned x = 0; x < this->map.size(); x++) {

			for (unsigned y = 0; y < this->map[x].size(); y++) {

				for (unsigned z = 0; z < this->map[x][y].size(); z++) {
					for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = nullptr;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file){
	
	this->grid_size_f = grid_size;
	this->grid_size_i = static_cast<int>(this->grid_size_f);
	this->max_world_size.x = width;
	this->max_world_size.y = height;
	this->max_world_size_f.x = static_cast<float>(width) * grid_size;
	this->max_world_size_f.y = static_cast<float>(height) * grid_size;
	this->layers = 1;
	this->texture_file = texture_file;

	this->from_x = 0;
	this->from_y = 0;
	this->to_x = 0;
	this->to_x = 0;
	this->layer = 0;

	this->map.resize(this->max_world_size.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->max_world_size.x; x++){

		for (int y = 0; y < this->max_world_size.y; y++) {
			this->map[x].resize(this->max_world_size.y, std::vector<std::vector<Tile*>>());

			for (int z = 0; z < this->layers; z++) {
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}


	if (!this->texture_sheet.loadFromFile(texture_file))
		std::cout << "ERROR: TILEMAP NO TEXTURE SHEET LOADED Filename: " + texture_file + "\n";

	//std::cout << "DEBUG grid_size_u: " << this->grid_size_u << "\n";
	//std::cout << "DEBUG grid_size_f: " << this->grid_size_f << "\n";
	//std::cout << "DEBUG max_size x: " << this->max_size.x << "\n";
	//std::cout << "DEBUG max_size y: " << this->max_size.y << "\n";

	this->collision_box.setSize(sf::Vector2f(grid_size, grid_size));
	this->collision_box.setFillColor(sf::Color(255, 0, 0, 50));
	this->collision_box.setOutlineColor(sf::Color::Red);
	this->collision_box.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string file_name){
	this->from_x = 0;
	this->from_y = 0;
	this->to_x = 0;
	this->to_x = 0;
	this->layer = 0;

	this->load_from_file(file_name);

	this->collision_box.setSize(sf::Vector2f(this->grid_size_f, this->grid_size_f));
	this->collision_box.setFillColor(sf::Color(255, 0, 0, 50));
	this->collision_box.setOutlineColor(sf::Color::Red);
	this->collision_box.setOutlineThickness(1.f);
}

TileMap::~TileMap(){
	this->clear();
}

// Getters

const sf::Texture * TileMap::get_texture_sheet() const {
	return &this->texture_sheet;
}

const int TileMap::get_layer_size(const int x, const int y, const int layer) const{
	if (x >= 0 and x < static_cast<int>(this->map.size())) {
		if (y >= 0 and y < static_cast<int>(this->map[x].size())) {
			if(layer >= 0 and layer < static_cast<int>(this->map[x][y].size())){
				return this->map[x][y][layer].size();
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

const sf::Vector2i & TileMap::get_max_world_grid_size_i() const{
	return this->max_world_size;
}

const sf::Vector2f & TileMap::get_max_world_grid_size_f() const{
	return this->max_world_size_f;
}

const bool TileMap::tile_empty(const int x, const int y, const int z) const{
	if (x >= 0 and x < this->max_world_size.x and
		y >= 0 and y < this->max_world_size.y and
		z >= 0 and z < this->layers) {

		return this->map[x][y][z].empty();
	}

	return false;
}

const bool TileMap::check_tile_type(const int x, const int y, const int type) const{
	// Zwraca typ klocka na danych koordynatach
	return this->map[x][y][this->layer].back()->get_type() == type;
}


// Methods
void TileMap::add_tile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& colliding, const short& type) {
	// Dodaj tile na pozycje w ktorej znajduje sie mysz

	if (x < this->max_world_size.x and x >= 0 and
		y < this->max_world_size.y and y >= 0 and
		z < this->layers and z >= 0) {

		this->map[x][y][z].push_back(new RegularTile(type, x, y, this->grid_size_f, this->texture_sheet, texture_rect, colliding));
		//std::cout << "Dodano kafelek\n";
	}
}

void TileMap::add_tile(const int x, const int y, const int z, const sf::IntRect & texture_rect, const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_max_distance){
	if (x < this->max_world_size.x and x >= 0 and
		y < this->max_world_size.y and y >= 0 and
		z < this->layers and z >= 0) {
		
		this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->grid_size_f, this->texture_sheet, texture_rect,
			enemy_type, enemy_amount, enemy_tts, enemy_max_distance));
	}
}

void TileMap::remove_tile(const int x, const int y, const int z, const int type) {
	// Usun tile na pozycji w ktorej znajduje sie mysz
	if (x < this->max_world_size.x and x >= 0 and
		y < this->max_world_size.y and y >= 0 and
		z < this->layers and z >= 0) {

		if (!this->map[x][y][z].empty()) {
			// jezeli tile tam istnieje, usun
			if (type >= 0) {
				if (this->map[x][y][z].back()->get_type() == type) {
					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
					//std::cout << "Usunieto kafelek\n";
				}
			}
			else {
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
				//std::cout << "Usunieto kafelek\n";
			}
		}
	}
}

void TileMap::save_to_file(const std::string file_name){
	/*
		Save Format:
		Size x, y
		grid size
		layers
		texture file

		grid pos x, y, layer
		texture rect x, y
		collliding
		type
	*/

	std::ofstream save_file;
	save_file.open(file_name);

	if (save_file.is_open()) {
		save_file << this->max_world_size.x << " " << this->max_world_size.y << "\n"
			<< this->grid_size_i << "\n"
			<< this->layers << "\n"
			<< this->texture_file << "\n";

		for (int x = 0; x < this->max_world_size.x; x++) {

			for (int y = 0; y < this->max_world_size.y; y++) {

				for (int z = 0; z < this->layers; z++) {

					if (!this->map[x][y][z].empty()) {
						for (size_t k = 0; k < this->map[x][y][z].size(); k++){
							save_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->to_string() << " ";
						}
					}
				}
			}
		}
	}
	else {
		std::cout << "COULD NOT OPEN A SAVE FILE " + file_name + " IN SAVE_TO_FILE TILEMAP";
	}

	save_file.close();
}

void TileMap::load_from_file(const std::string file_name){
	/*
		Save Format:
		Size x, y
		grid size
		layers
		texture file

		type
		grid pos x, y, layer
		texture rect x, y
		collliding
	*/

	std::ifstream save_file;
	save_file.open(file_name);

	if (save_file.is_open()) {
		
		sf::Vector2i size;
		int grid_size = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int tr_x = 0;
		int tr_y = 0;
		bool colliding = false;
		short type = 0;

		// Ustawienia mapy
		save_file >> size.x >> size.y >> grid_size >> layers >> texture_file;
		
		// Ustawienia tiles
		this->grid_size_f = static_cast<float>(grid_size);
		this->grid_size_i = grid_size;
		this->max_world_size.x = size.x;
		this->max_world_size.y = size.y;
		this->max_world_size_f.x = static_cast<float>(size.x * grid_size);
		this->max_world_size_f.y = static_cast<float>(size.y * grid_size);
		this->layers = layers;
		this->texture_file = texture_file;

		this->clear();

		this->map.resize(this->max_world_size.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < max_world_size.x; x++) {

			for (int y = 0; y < max_world_size.y; y++) {
				this->map[x].resize(this->max_world_size.y, std::vector < std::vector<Tile*>>());

				for (int z = 0; z < this->layers; z++) {
					this->map[x][y].resize(this->layers, std::vector <Tile*>());
				}
			}
		}

		// Tiles
		while (save_file >> x >> y >> z >> type) {
			if (type == TileTypes::ENEMY_SPAWNER) {
				int enemy_type = 0;
				int enemy_amount = 0;
				int enemy_tts = 0;
				float enemy_max_distance = 0;

				save_file >> tr_x >> tr_y >> enemy_type >> enemy_amount >> enemy_tts >> enemy_max_distance;
				
				this->map[x][y][z].push_back(
					new EnemySpawnerTile(
						x, y,
						this->grid_size_f,
						this->texture_sheet,
						sf::IntRect(tr_x, tr_y, this->grid_size_i / 2, this->grid_size_i / 2), // UWAGA TO TYMCZASOWE
						enemy_type,
						enemy_amount,
						enemy_tts,
						enemy_max_distance
					)
				);
			}
			else {
				save_file >> tr_x >> tr_y >> colliding;
				this->map[x][y][z].push_back(
					new RegularTile(
						type,
						x, y,
						this->grid_size_f,
						this->texture_sheet,
						sf::IntRect(tr_x, tr_y,this->grid_size_i / 2, this->grid_size_i / 2), // UWAGA TO TYMCZASOWE
						colliding
					)
				);
			}
		}
		
		if (!this->texture_sheet.loadFromFile(texture_file))
			std::cout << "ERROR: TILEMAP NO TEXTURE SHEET LOADED Filename: " + texture_file + "\n";
	}
	else {
		std::cout << "COULD NOT OPEN A SAVE FILE " + file_name + " IN LOAD_FROM_FILE TILEMAP";
	}

	save_file.close();
}

void TileMap::update_world_border_collision(Entity * entity, const float & dt) {
	// Sprawdzam granice mapy i zatrzymuje gracza jesli je przekroczy
	if (entity->get_position().x < 0.f) {
		entity->stop_velocity_x();
		entity->set_pos(0.f, entity->get_position().y);
	}
	else if (entity->get_position().x + entity->get_global_bounds().width > this->max_world_size_f.x) {
		entity->stop_velocity_x();
		entity->set_pos(this->max_world_size_f.x - entity->get_global_bounds().width, entity->get_position().y);
	}

	if (entity->get_position().y < 0.f) {
		entity->stop_velocity_y();
		entity->set_pos(entity->get_position().x, 0.f);
	}
	else if (entity->get_position().y + entity->get_global_bounds().height > this->max_world_size_f.y) {
		entity->stop_velocity_y();
		entity->set_pos(entity->get_position().x, this->max_world_size_f.y - entity->get_global_bounds().height);
	}
}

void TileMap::update_tile_collision(Entity * entity, const float & dt) {
	// Sprawdzam tile w przód
	this->layer = 0;

	this->from_x = entity->get_grid_position(this->grid_size_i).x - 1;
	if (this->from_x < 0)
		this->from_x = 0;
	else if (this->from_x > this->max_world_size.x)
		this->from_x = this->max_world_size.x - 1;

	this->to_x = entity->get_grid_position(this->grid_size_i).x + 3;
	if (this->to_x < 0)
		this->to_x = 0;
	else if (this->to_x > this->max_world_size.x)
		this->to_x = this->max_world_size.x - 1;

	this->from_y = entity->get_grid_position(this->grid_size_i).y - 1;
	if (this->from_y < 0)
		this->from_y = 0;
	else if (this->from_y > this->max_world_size.x)
		this->from_y = this->max_world_size.x;

	this->to_y = entity->get_grid_position(this->grid_size_i).y + 3;
	if (this->to_y < 0)
		this->to_y = 0;
	else if (this->to_y > this->max_world_size.x)
		this->to_y = this->max_world_size.x;


	for (int x = this->from_x; x < this->to_x; x++) {

		for (int y = this->from_y; y < this->to_y; y++) {

			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {

				sf::FloatRect player_bounds = entity->get_global_bounds();
				sf::FloatRect wall_bounds = this->map[x][y][this->layer][k]->get_global_bounds();
				sf::FloatRect next_pos = entity->get_next_pos(dt);

				if (this->map[x][y][this->layer][k]->get_collision() and this->map[x][y][this->layer][k]->intersects(next_pos)) {

					// Kolizja górnej krawêdzi klocka
					if (player_bounds.top < wall_bounds.top and
						player_bounds.top + player_bounds.height < wall_bounds.top + wall_bounds.height and
						player_bounds.left < wall_bounds.left + wall_bounds.width and
						player_bounds.left + player_bounds.width > wall_bounds.left) {

						entity->stop_velocity_y();
						entity->set_pos(player_bounds.left, wall_bounds.top - player_bounds.height);
					}


					// Kolizja dolnej krawêdzi klocka
					else if (player_bounds.top > wall_bounds.top and
						player_bounds.top + player_bounds.height > wall_bounds.top + wall_bounds.height and
						player_bounds.left < wall_bounds.left + wall_bounds.width and
						player_bounds.left + player_bounds.width > wall_bounds.left) {

						entity->stop_velocity_y();
						entity->set_pos(player_bounds.left, wall_bounds.top + wall_bounds.height);
					}

					// Kolizja lewej krawedzi klocka
					if (player_bounds.left < wall_bounds.left and
						player_bounds.left + player_bounds.width < wall_bounds.left + wall_bounds.width and
						player_bounds.top < wall_bounds.top + wall_bounds.height and
						player_bounds.top + player_bounds.height > wall_bounds.top) {

						entity->stop_velocity_x();
						entity->set_pos(wall_bounds.left - player_bounds.width, player_bounds.top);
					}

					// Kolizja prawej krawedzi klocka
					else if (player_bounds.left > wall_bounds.left and
						player_bounds.left + player_bounds.width > wall_bounds.left + wall_bounds.width and
						player_bounds.top < wall_bounds.top + wall_bounds.height and
						player_bounds.top + player_bounds.height > wall_bounds.top) {

						entity->stop_velocity_x();
						entity->set_pos(wall_bounds.left + wall_bounds.width, player_bounds.top);
					}
				}
			}
		}
	}
}

void TileMap::update_tiles(Entity * entity, const float & dt, EnemySystem& enemy_system) {
	// Sprawdzam tile w przód
	this->layer = 0;

	this->from_x = entity->get_grid_position(this->grid_size_i).x - 25;
	if (this->from_x < 0)
		this->from_x = 0;
	else if (this->from_x > this->max_world_size.x)
		this->from_x = this->max_world_size.x - 1;

	this->to_x = entity->get_grid_position(this->grid_size_i).x + 25;
	if (this->to_x < 0)
		this->to_x = 0;
	else if (this->to_x > this->max_world_size.x)
		this->to_x = this->max_world_size.x - 1;

	this->from_y = entity->get_grid_position(this->grid_size_i).y - 16;
	if (this->from_y < 0)
		this->from_y = 0;
	else if (this->from_y > this->max_world_size.x)
		this->from_y = this->max_world_size.x;

	this->to_y = entity->get_grid_position(this->grid_size_i).y + 16;
	if (this->to_y < 0)
		this->to_y = 0;
	else if (this->to_y > this->max_world_size.x)
		this->to_y = this->max_world_size.x;


	for (int x = this->from_x; x < this->to_x; x++) {

		for (int y = from_y; y < this->to_y; y++) {

			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {

				this->map[x][y][this->layer][k]->update();

				if (this->map[x][y][this->layer][k]->get_type() == TileTypes::ENEMY_SPAWNER) {

					EnemySpawnerTile* spawner = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);
					
					if (spawner) {
						if (!spawner->get_spawned()) {
							enemy_system.create_enemy(SLIME, x * this->grid_size_f, y * this->grid_size_f);
							spawner->set_spawned(true);
						}
					}
				}
			}
		}
	}
}

void TileMap::update(Entity * entity, const float& dt) {
	
}

void TileMap::render_delayed_tiles(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f player_pos){
	// Renderuj tile które s¹ opóŸnione, np liœcie drzew

	while (!this->delayed_tiles.empty()) {
		if(shader)
			delayed_tiles.top()->render(target, shader, player_pos);
		else
			delayed_tiles.top()->render(target);

		delayed_tiles.pop();
	}
}

void TileMap::render(sf::RenderTarget & target,
	const sf::Vector2i& grid_pos,
	sf::Shader* shader,
	const sf::Vector2f player_pos,
	const bool show_hitbox){
	this->layer = 0;

	this->from_x = grid_pos.x - 15;
	if (this->from_x < 0)
		this->from_x = 0;
	else if (this->from_x > this->max_world_size.x)
		this->from_x = this->max_world_size.x;

	this->to_x = grid_pos.x + 16;
	if (this->to_x < 0)
		this->to_x = 0;
	else if (this->to_x > this->max_world_size.x)
		this->to_x = this->max_world_size.x;

	this->from_y = grid_pos.y - 9;
	if (this->from_y < 0)
		this->from_y = 0;
	else if (this->from_y > this->max_world_size.x)
		this->from_y = this->max_world_size.x;

	this->to_y = grid_pos.y + 9;
	if (this->to_y < 0)
		this->to_y = 0;
	else if (this->to_y > this->max_world_size.x)
		this->to_y = this->max_world_size.x;

	for (int x = this->from_x; x < this->to_x; x++) {

		for (int y = from_y; y < this->to_y; y++) {
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++){

				if (this->map[x][y][this->layer][k]->get_type() == TileTypes::ABOVE_PLAYER) {
					this->delayed_tiles.push(this->map[x][y][this->layer][k]);
				}
				else {
					if (shader) {
						this->map[x][y][this->layer][k]->render(target, shader, player_pos);
					}
					else
						this->map[x][y][this->layer][k]->render(target);
					
				}

				if (show_hitbox) {
					if (this->map[x][y][this->layer][k]->get_collision()) {
						this->collision_box.setPosition(map[x][y][this->layer][k]->get_position());
						target.draw(this->collision_box);
					}
				}
				
				if (this->map[x][y][this->layer][k]->get_type() == TileTypes::ENEMY_SPAWNER) {
					if(show_hitbox){
						this->collision_box.setPosition(map[x][y][this->layer][k]->get_position());
						target.draw(this->collision_box);
					}
				}
			}
		}
	}
}

void TileMap::render_whole(sf::RenderTarget & target, const bool show_hitbox) {
	this->layer = 0;

	for (unsigned x = 0; x < this->map.size(); x++) {

		for (unsigned y = 0; y < this->map[x].size(); y++) {
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {

				if (this->map[x][y][this->layer][k]->get_type() == TileTypes::ABOVE_PLAYER) {
					this->delayed_tiles.push(this->map[x][y][this->layer][k]);
				}
				else {
					this->map[x][y][this->layer][k]->render(target);

				}

				if (show_hitbox) {
					if (this->map[x][y][this->layer][k]->get_collision()) {
						this->collision_box.setPosition(map[x][y][this->layer][k]->get_position());
						this->collision_box.setFillColor(sf::Color(255, 20, 20, 100));
						this->collision_box.setOutlineColor(sf::Color::Red);
						target.draw(this->collision_box);
					}
				}

				if (this->map[x][y][this->layer][k]->get_type() == TileTypes::ENEMY_SPAWNER) {
					if (show_hitbox) {
						this->collision_box.setPosition(map[x][y][this->layer][k]->get_position());
						this->collision_box.setFillColor(sf::Color(20, 20, 255, 100));
						this->collision_box.setOutlineColor(sf::Color::Blue);
						target.draw(this->collision_box);
					}
				}
			}
		}
	}
}
