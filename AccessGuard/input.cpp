#include "input.h"

Input::Input(const sf::Vector2f input_size_, const sf::Vector2f input_position_, const sf::Font& input_font_, std::string placeholder_) : input_text(input_font_, "", 24), placeholder_text(input_font_, placeholder_, 24), is_selected(false) {
	input_shape.setSize(input_size_);
	input_shape.setPosition(input_position_);
	input_shape.setFillColor(sf::Color(100, 100, 100));
	input_shape.setOutlineThickness(2.f);
	input_shape.setOutlineColor(sf::Color::White);

	input_text.setFillColor(sf::Color::White);
	input_text.setPosition({ input_position_.x + 10.f, input_position_.y + 10.f });

	placeholder_text.setFillColor(sf::Color(200, 200, 200, 150));
	placeholder_text.setPosition({ input_position_.x + 10.f, input_position_.y + 10.f });
}

void Input::drawInput(sf::RenderWindow& window_) {
	window_.draw(input_shape);

	if (input_variable.empty()) {
		window_.draw(placeholder_text);
	}
	else {
		window_.draw(input_text);
	}
}

void Input::updateSelection(sf::Vector2i mouse_position_) {
	if (input_shape.getGlobalBounds().contains({ (float)mouse_position_.x, (float)mouse_position_.y })) {
		is_selected = true;
		input_shape.setFillColor(sf::Color(50, 50, 50));
	}
	else {
		is_selected = false;
		input_shape.setFillColor(sf::Color(100, 100, 100));
	}
}

void Input::keyboardInput(uint32_t unicode) {
	if (!is_selected) {
		return;
	}
	if (unicode == 8 && !input_variable.empty()) {
		input_variable.pop_back();
	}
	else if (unicode >= 32 && unicode < 128 && input_variable.length() < 20) {
		input_variable += static_cast<char>(unicode);	
	}

	input_text.setString(input_variable);
}

void Input::deactivateInput()
{
	is_selected = false;
	input_shape.setFillColor(sf::Color(100, 100, 100));
}

std::string Input::getText() {
	return input_variable;
}

bool Input::isActive() {
	return is_selected;
}

void Input::clearInput() {
	input_variable = "";
	input_text.setString("");
}