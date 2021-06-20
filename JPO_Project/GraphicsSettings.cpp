#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->framerate = 120;
	this->vsync = false;
	this->context_settings.antialiasingLevel = 0;
	this->resolutions = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::save_to_file(const std::string path) {
	std::ofstream conf_f(path);

	// Jezeli otwarto plik z ustawieniami, laduje do niego dane
	if (conf_f.is_open()) {
		conf_f << this->title;
		conf_f << this->resolution.width << " " << this->resolution.height;
		conf_f << this->fullscreen;
		conf_f << this->framerate;
		conf_f << this->vsync;
		conf_f << this->context_settings.antialiasingLevel;
	}
	conf_f.close();
}

void GraphicsSettings::load_from_file(const std::string path) {
	std::ifstream conf_f(path);

	// Jezeli otwarto plik z ustawieniami, pobieram z niego dane
	if (conf_f.is_open()) {
		std::getline(conf_f, this->title);
		conf_f >> this->resolution.width >> this->resolution.height;
		conf_f >> this->fullscreen;
		conf_f >> this->framerate;
		conf_f >> this->vsync;
		conf_f >> this->context_settings.antialiasingLevel;
	}
	conf_f.close();
}