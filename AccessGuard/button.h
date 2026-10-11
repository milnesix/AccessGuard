#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape button_shape;
	sf::Text button_text;
public:
	Button(std::string button_text_, const sf::Vector2f button_size_, const sf::Vector2f button_position_, const sf::Font& button_font_, const sf::Color button_color_);
	void drawButton(sf::RenderWindow& window_);
	bool isButtonClicked(sf::Vector2i mouse_position_);
};

#endif