#ifndef GUI_H
#define GUI_H

enum ButtonStates { BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVER };

namespace gui {
	const float p2p_x(const float percent, const sf::VideoMode& vm);
	const float p2p_y(const float percent, const sf::VideoMode& vm);
	const unsigned calc_font_size(const sf::VideoMode& vm, const unsigned modifier = 60);

	// BUTTON ========================================
	class Button {
	private:
		short unsigned button_state;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color text_color_idle;
		sf::Color text_color_hover;
		sf::Color text_color_active;

		sf::Color color_idle;
		sf::Color color_hover;
		sf::Color color_active;

		sf::Color outline_color_idle;
		sf::Color outline_color_hover;
		sf::Color outline_color_active;

	public:
		Button(float x, float y, float width, float height,
			std::string text, sf::Font * font, unsigned character_size,
			sf::Color text_color_idle, sf::Color text_color_hover, sf::Color text_color_active,
			sf::Color color_idle, sf::Color color_hover, sf::Color color_active,
			sf::Color outline_color_idle = sf::Color::Transparent, sf::Color outline_color_hover = sf::Color::Transparent, sf::Color outline_color_active = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		// Getters
		const bool is_pressed() const;
		const std::string get_text() const;
		const short unsigned get_id() const;

		// Setters
		void set_text(const std::string text);
		void set_id(const short unsigned id);

		// Methods
		void render(sf::RenderTarget& target);
		void update(sf::Vector2i& mouse_pos_window);
	};

	// DROPDOWN ========================================
	class DropDownList {
	private:
		// Vars
		float keytime;
		float keytime_max;

		sf::Font& font;
		gui::Button* active;
		std::vector<gui::Button*> list;
		bool showed;

	public:
		DropDownList(float x, float y, float width, float height,
			std::string list[], sf::Font& font,
			unsigned nr_of_elements, unsigned default_index = 0);
		virtual ~DropDownList();

		// Getters
		const bool get_keytime();
		const unsigned short get_active_id() const;

		// Methods
		void render(sf::RenderTarget& target);
		void update(sf::Vector2i& mouse_pos_window, const float& dt);
		void update_keytime(const float& dt);
	};

	class TextureSelector {
	private:
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mouse_pos_grid;
		sf::IntRect texture_rect;
		gui::Button* hide_btn;

		float keytime;
		const float keytime_max;
		float grid_size;
		float tile_res;
		bool active;
		bool hidden;

	public:
		TextureSelector(float x, float y, float width, float height,
			float grid_size, float tile_res, const sf::Texture* texture_sheet,
			sf::Font& font, std::string text);
		virtual ~TextureSelector();

		// Getters
		const bool& get_active() const;
		const sf::IntRect& get_texture_rect() const;
		const bool get_keytime();
		
		// Methods
		void var_init();
		void update_keytime(const float& dt);
		void update(sf::Vector2i& mouse_pos_window, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar {
	private:
		std::string string;
		sf::Text text;
		float max_width;
		int max_value;
		sf::RectangleShape back;
		sf::RectangleShape fill;

	public:
		ProgressBar(float x, float y, float width, float height, 
			int max_value, unsigned font_size, sf::Color inner_color,
			sf::VideoMode& vm, sf::Font* font = nullptr);

		virtual ~ProgressBar();

		// Getters

		// Setters

		// Methods
		void update(const int current_value, const int max_value);
		void render(sf::RenderTarget & target);
	};
}
#endif