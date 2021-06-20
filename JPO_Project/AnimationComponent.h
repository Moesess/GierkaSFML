#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

class AnimationComponent{
private:
	class Animation {
	public:
		// Variables
		sf::Sprite& sprite;
		sf::Texture& texture_sheet;
		float animation_speed;
		float timer;
		int width;
		int height;
		bool done;
		sf::IntRect start_rect;
		sf::IntRect current_rect;
		sf::IntRect end_rect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animation_speed, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), texture_sheet(texture_sheet), timer(0.f), done(false), animation_speed(animation_speed), width(width), height(height){

			this->timer = 0.f;
			this->start_rect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->current_rect = this->start_rect;
			this->end_rect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->texture_sheet, true);
			this->sprite.setTextureRect(this->start_rect);
		}

		// Getters
		const bool& is_done() const {
			return this->done;
		}

		// Methods
		const bool& play(const float& dt) {
			this->done = false;

			// Timer animacji
			this->timer += 100.f * dt;
			
			if (this->timer >= this->animation_speed) {
				
				// reset timer;
				this->timer = 0;

				// Animacja
				if (this->current_rect != this->end_rect) {
					this->current_rect.left += this->width;
				}

				else { // Powtórz
					this->current_rect.left = this->start_rect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->current_rect);
			}
			return this->done;
		}

		const bool& play(const float& dt, float mod_percentage) {
			this->done = false;

			// timer animacji
			if (mod_percentage < 0.3f)
				mod_percentage = 0.3f;
			
			this->timer += mod_percentage * 100.f * dt;

			if (this->timer >= this->animation_speed) {

				// reset timer;
				this->timer = 0.f;

				// Animacja
				if (this->current_rect != this->end_rect) {
					this->current_rect.left += this->width;
				}

				else { // powtórz
					this->current_rect.left = this->start_rect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->current_rect);
			}
			return this->done;
		}

		void reset() {
			this->timer = this->animation_speed;
			this->current_rect = this->start_rect;
		}
	};

	// Vars
	sf::Sprite& sprite;
	sf::Texture& texture_sheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	// Getters
	const bool& is_done(const std::string key);

	// Methods
	void add_animation(const std::string key, float animation_speed,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

#endif