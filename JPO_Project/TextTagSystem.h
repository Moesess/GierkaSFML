#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

class TextTagSystem{
private:
	class TextTag {
	public:

	};

public:
	TextTagSystem();
	virtual ~TextTagSystem();

	// Methods
	void add_text_tag(TextTag* text_tag);
	void remove_text_tag();

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif