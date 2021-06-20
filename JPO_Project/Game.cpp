#include "stdafx.h"
#include "Game.h"

// Init
void Game::variables_init() {
	this->window = nullptr;

	this->dt = 0.f;

	this->grid_size = 64.f;
}

void Game::graphics_settings_init(){
	
	this->gf_settings.load_from_file("Config/graphics.ini");

	/*Creating SFML window*/
}

void Game::window_init(){
	
	if(this->gf_settings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gf_settings.resolution,
			this->gf_settings.title,
			sf::Style::Fullscreen,
			this->gf_settings.context_settings
		);
	else
		this->window = new sf::RenderWindow(
			this->gf_settings.resolution,
			this->gf_settings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gf_settings.context_settings
		);
		
	this->window->setFramerateLimit(this->gf_settings.framerate);
	this->window->setVerticalSyncEnabled(this->gf_settings.vsync);
}

void Game::state_data_init(){
	this->state_data.window = this->window;
	this->state_data.gf_settings = &this->gf_settings;
	this->state_data.keys = &this->keys;
	this->state_data.states = &this->states;
	this->state_data.grid_size = this->grid_size;
}

void Game::keys_init() {
	// Ladowanie dozwolonych klawiszy z pliku
	std::ifstream key_f("Config/keys.ini");

	if (key_f.is_open()) {
		std::string key = "";
		int key_val = 0;

		while (key_f >> key >> key_val) {
			this->keys[key] = key_val;
		}
	}

	key_f.close();
}

void Game::states_init(){
	// Dodaje stany aplikacji do stosu
	this->states.push(new MainMenuState(&this->state_data));
	
}

// Constructors
Game::Game() {
	this->variables_init();
	this->graphics_settings_init();
	this->window_init();
	this->keys_init();
	this->state_data_init();
	this->states_init();
}

// Destructor
Game::~Game() {
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

// Main Game
void Game::update_dt(){
	/* Aktualizujemy wewnetrzny licznik, pozwala okreslic ile zajmuje wygenerowanie i render klatki */

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::update_SFML_events(){
	// Sprawdzamy eventy w SFML

	while (this->window->pollEvent(this->sf_event)) {
		if (this->sf_event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update(){
	this->update_SFML_events();

	// Aktualizacja stanów aplikacji jeœli mamy aktualnie u¿ywamy okna gry
	if (!this->states.empty()) {
		
		if (this->window->hasFocus()) {

			this->states.top()->update(this->dt);

			// Wyjscie ze stanu
			if (this->states.top()->get_quit()) {

				this->states.top()->end_state();
				delete this->states.top();
				this->states.pop();
			}
		}
	}

	// Wyjscie z aplikacji
	else {
		this->quit_app();
		this->window->close();
	}
}

void Game::render(){
	this->window->clear();

	// Render stanu
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::quit_app(){
	std::cout << "Closing App\n";
}

void Game::run(){
	while (this->window->isOpen()) {
		this->update_dt();
		this->update();
		this->render();
	}
}

