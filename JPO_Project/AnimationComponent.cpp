#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), texture_sheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr){

}

AnimationComponent::~AnimationComponent(){
	for (auto &it : this->animations) {
		delete it.second;
	}
}

// Getters

const bool & AnimationComponent::is_done(const std::string key){
	return this->animations[key]->is_done();
}

// Methods
void AnimationComponent::add_animation(const std::string key, float animation_speed,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height){

	this->animations[key] = new Animation(
		this->sprite, this->texture_sheet,
		animation_speed, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority){
	if (this->priorityAnimation) { // Animacja priorytetowa, np atak
		if (this->priorityAnimation == this->animations[key]) {

			if (this->lastAnimation != this->animations[key]) {

				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}

				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			// Jezeli priorytet sie zakonczyl usun obiekt
			if (this->animations[key]->play(dt)) {
				this->priorityAnimation = nullptr;
			}
			
		}
	}
	else { // Zwykla animacja
		if (this->lastAnimation != this->animations[key]) {
			if (priority) {
				this->priorityAnimation = this->animations[key];
			}

			if (this->lastAnimation == nullptr) {
				this->lastAnimation = this->animations[key];
			}
			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
	return this->animations[key]->is_done();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority) {

	if (this->priorityAnimation) { // Animacja priorytetowa, np atak
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animations[key];
				}
				else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			// Jezeli priorytet sie zakonczyl usun obiekt
			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else { // Zwykla animacja
		if (this->lastAnimation != this->animations[key]) {

			if (priority) {
				this->priorityAnimation = this->animations[key];
			}

			if (this->lastAnimation == nullptr) {
				this->lastAnimation = this->animations[key];
			}

			else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->is_done();
}
