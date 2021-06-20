#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings {
public:
	GraphicsSettings();

	// Vars
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vsync;

	unsigned framerate;
	sf::ContextSettings context_settings;
	std::vector<sf::VideoMode> resolutions;

	// Methods
	void save_to_file(const std::string path);

	void load_from_file(const std::string path);
};

#endif