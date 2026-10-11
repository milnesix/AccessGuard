#include "button.h"

Button::Button(std::string button_text_, const sf::Vector2f button_size_, const sf::Vector2f button_position_, const sf::Font& button_font_, const sf::Color button_color_) : button_text(button_font_, button_text_, 24) {
	button_shape.setSize(button_size_);
	button_shape.setFillColor(button_color_);
	button_shape.setPosition(button_position_);

	button_text.setFont(button_font_);
	button_text.setString(button_text_);
	button_text.setCharacterSize(24);
	button_text.setFillColor(sf::Color::White);

	button_text.setOrigin({ (float)(int)(button_text.getLocalBounds().position.x + button_text.getLocalBounds().size.x / 2.0f), (float)(int)(button_text.getLocalBounds().position.y + button_text.getLocalBounds().size.y / 2.0f) });

	button_text.setPosition({ button_position_.x + button_size_.x / 2.0f, button_position_.y + button_size_.y / 2.0f });
}

void Button::drawButton(sf::RenderWindow& window_) {
	window_.draw(button_shape);
	window_.draw(button_text);
}

bool Button::isButtonClicked(sf::Vector2i mouse_position_) {
	return button_shape.getGlobalBounds().contains({ (float)mouse_position_.x, (float)mouse_position_.y });
}