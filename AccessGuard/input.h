#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input {
private:
	sf::RectangleShape input_shape;
	sf::Text input_text;
	std::string input_variable;
	bool is_selected;
	sf::Text placeholder_text;
	std::string placeholder_string;
public:
	Input(const sf::Vector2f input_size_, const sf::Vector2f input_position_, const sf::Font& input_font_, std::string placeholder_);
	void drawInput(sf::RenderWindow& window_);
	void updateSelection(sf::Vector2i mouse_position_);
	void keyboardInput(uint32_t unicode);
	void deactivateInput();
	std::string getText();
	bool isActive();
	void clearInput();
};

#endif