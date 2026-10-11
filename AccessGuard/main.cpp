#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "button.h"
#include "input.h"

enum AppState { Menu, Employees, Rooms, Cards, Simulation, Add, Remove, List };

void deactivateAllInputs(Input& input_add, Input& input_remove, Input& input_id, Input& input_level, Input& input_card, Input& input_room)
{
	input_add.deactivateInput();
	input_remove.deactivateInput();
	input_id.deactivateInput();
	input_level.deactivateInput();
	input_card.deactivateInput();
	input_room.deactivateInput();
}

void mouseClick(AppState& state_, sf::Vector2i mouse_position_, System& system_, sf::Text& status_text_, sf::Sprite& back_button_, Button& button_employee_, Button& button_room_, Button& button_card_, Button& button_simulation_, Button& button_add_, Button& button_remove_, Button& button_list_, Button& button_confirm_1_, Button& button_confirm_2_, Input& input_add_, Input& input_remove_, Input& input_id_, Input& input_level_, Input& input_card_, Input& input_room_) {
	sf::Vector2f mouse_position_float(static_cast<float>(mouse_position_.x), static_cast<float>(mouse_position_.y));

	if (state_ != Menu && back_button_.getGlobalBounds().contains(mouse_position_float)) {
		deactivateAllInputs(input_add_, input_remove_, input_id_, input_level_, input_card_, input_room_);

		if (state_ == Add || state_ == Remove || state_ == List) {
			state_ = Employees;
			status_text_.setString("Status: Wrocono do menu pracownika");
		}
		else {
			state_ = Menu;
			status_text_.setString("Status: Wrocono do menu");
		}
		return;
	}

	if (state_ == Menu) {
		if (button_employee_.isButtonClicked(mouse_position_)) {
			state_ = Employees;
			status_text_.setString("Status: Otwarto menu pracownika");
		}
		else if (button_room_.isButtonClicked(mouse_position_)) {
			state_ = Rooms;
			status_text_.setString("Status: Otwarto liste pokojow");
		}
		else if (button_card_.isButtonClicked(mouse_position_)) {
			state_ = Cards;
			status_text_.setString("Status: Otwarto menu wydawania karty dostepu");
		}
		else if (button_simulation_.isButtonClicked(mouse_position_)) {
			state_ = Simulation;
			status_text_.setString("Status: Otwarto menu symulacji wejscia");
		}
	}

	else if (state_ == Employees) {
		if (button_add_.isButtonClicked(mouse_position_)) {
			state_ = Add;
			status_text_.setString("Status: Otwarto menu dodawania pracownika");
		}
		else if (button_remove_.isButtonClicked(mouse_position_)) {
			state_ = Remove;
			status_text_.setString("Status: Otwarto menu usuniencia pracownika");
		}
		else if (button_list_.isButtonClicked(mouse_position_)) {
			state_ = List;
			status_text_.setString("Status: Otwarto liste pracownikow");
		}
	}

	else if (state_ == Add) {
		input_add_.updateSelection(mouse_position_);

		if (button_confirm_1_.isButtonClicked(mouse_position_)) {
			std::string employee_name = input_add_.getText();

			if (!employee_name.empty()) {
				try {
					int employee_random_id = 1000 + (rand() % 9000);
					status_text_.setString("Dodano pracownika: " + employee_name + " | ID: " + std::to_string(employee_random_id));

					system_.addEmployee(employee_name, employee_random_id);

					employee_name.clear();
					input_add_.clearInput();
				}
				catch (const std::exception& error) {
					status_text_.setString(std::string("Blad: ") + error.what());
				}
			}
		}
	}

	else if (state_ == Remove) {
		input_remove_.updateSelection(mouse_position_);

		if (button_confirm_1_.isButtonClicked(mouse_position_)) {
			std::string employee_id = input_remove_.getText();

			if (!employee_id.empty()) {
				try {
					std::string employee_remove_name = system_.removeEmployee(std::stoi(employee_id));
					status_text_.setString("Usunieto pracownika: " + employee_remove_name + " | ID: " + employee_id);

					employee_id.clear();
					input_remove_.clearInput();
				}
				catch (const std::exception& error) {
					status_text_.setString(std::string("Blad: ") + error.what());
				}
			}
		}
	}

	else if (state_ == Cards) {
		input_id_.updateSelection(mouse_position_);
		input_level_.updateSelection(mouse_position_);

		if (button_confirm_2_.isButtonClicked(mouse_position_)) {
			std::string employee_id_for_card = input_id_.getText();
			std::string card_level = input_level_.getText();

			if (!employee_id_for_card.empty() && !card_level.empty()) {
				try {
					int card_random_number = 100 + (rand() % 900);
					system_.giveCard(std::stoi(employee_id_for_card), card_random_number, card_level);
					status_text_.setString("Dodano karte dla pracownika o ID: " + employee_id_for_card + " | Numer: " + std::to_string(card_random_number) + " | Poziom: " + card_level);

					employee_id_for_card.clear();
					card_level.clear();
					input_id_.clearInput();
					input_level_.clearInput();
				}
				catch (const std::exception& error) {
					status_text_.setString(std::string("Blad: ") + error.what());
				}
			}
		}
	}

	else if (state_ == Simulation) {
		input_card_.updateSelection(mouse_position_);
		input_room_.updateSelection(mouse_position_);

		if (button_confirm_2_.isButtonClicked(mouse_position_)) {
			std::string card_number_for_room = input_card_.getText();
			std::string room_name = input_room_.getText();

			if (!card_number_for_room.empty() && !room_name.empty()) {
				try {
					std::string empl_name = system_.loginSimulation(std::stoi(card_number_for_room), room_name);
					status_text_.setString("Pracownik " + empl_name + " wszedl do pokoju " + room_name);

					card_number_for_room.clear();
					room_name.clear();
					input_card_.clearInput();
					input_room_.clearInput();
				}
				catch (const std::exception& error) {
					status_text_.setString(std::string("Blad: ") + error.what());
				}
			}
		}
	}
}

void drawEmployeeList(sf::RenderWindow& window_, const System& system_, const sf::Font& font_, sf::Text& status_text_, sf::Text& esc_text_, sf::Sprite& back_button_, sf::RectangleShape& top_bar_, sf::Text& title_text_) {
	window_.draw(top_bar_);
	window_.draw(title_text_);

	const auto& employees_list = system_.getEmployees();
	float y_offset = 150.f;

	if (employees_list.empty()) {
		sf::Text empty_text(font_, "Brak pracownikow w systemie", 20);
		empty_text.setFillColor(sf::Color::White);
		empty_text.setPosition({ 50.f, y_offset });
		window_.draw(empty_text);
	}
	else {
		for (const auto& e : employees_list) {
			std::string card_info = " [Brak karty]";

			if (e->getEmployeeCard()) {
				Card* card = e->getEmployeeCard();

				std::string level_str_1 = card->getLevelName();
				std::string status_str;

				if (card->getCardStatus() == Blocked) {
					status_str = "Zablokowana";
				}
				else {
					status_str = "Aktywna";
				}

				card_info = " [Karta: " + std::to_string(card->getCardNumber()) + " | Poziom: " + level_str_1 + " | Status: " + status_str + "]";
			}

			std::string info_str_1 = "- " + e->getEmployeeName() + " (ID: " + std::to_string(e->getEmployeeId()) + ")" + card_info;

			sf::Text emp_text(font_, info_str_1, 20);
			emp_text.setFillColor(sf::Color::White);
			emp_text.setPosition({ 50.f, y_offset });
			window_.draw(emp_text);

			y_offset += 30.f;
		}
	}

	window_.draw(status_text_);
	window_.draw(esc_text_);
	window_.draw(back_button_);
}

void drawRoomsList(sf::RenderWindow& window_, const System& system_, const sf::Font& font_, sf::Text& status_text_, sf::Text& esc_text_, sf::Sprite& back_button_, sf::RectangleShape& top_bar_, sf::Text& title_text_) {
	window_.draw(top_bar_);
	window_.draw(title_text_);

	const auto& rooms_list = system_.getRooms();
	float y_offset = 150.f;

	for (const auto& r : rooms_list) {
		std::string level_str_2 = "Guest";

		if (r->getRoomLevel() == Worker) {
			level_str_2 = "Worker";
		}
		else if (r->getRoomLevel() == Admin) {
			level_str_2 = "Admin";
		}

		std::string info_str_2 = "- Pokoj: " + r->getRoomName() + " | Poziom: " + level_str_2;

		sf::Text room_text(font_, info_str_2, 20);
		room_text.setFillColor(sf::Color::White);
		room_text.setPosition({ 50.f, y_offset });
		window_.draw(room_text);

		y_offset += 30.f;
	}

	window_.draw(status_text_);
	window_.draw(esc_text_);
	window_.draw(back_button_);
}

void renderInterface(sf::RenderWindow& window_, AppState state_, const System& system_, const sf::Font& font_, sf::RectangleShape& top_bar_, sf::Text& title_text_, sf::Text& status_text_, sf::Text& esc_text_, sf::Sprite& back_button_, Button& button_employee_, Button& button_room_, Button& button_card_, Button& button_simulation_, Button& button_add_, Button& button_remove_, Button& button_list_, Button& button_confirm_1_, Button& button_confirm_2_, Input& input_add_, Input& input_remove_, Input& input_id_, Input& input_level_, Input& input_card_, Input& input_room_) {
	window_.clear(sf::Color(24, 28, 36));

	if (state_ == Menu) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		button_employee_.drawButton(window_);
		button_room_.drawButton(window_);
		button_card_.drawButton(window_);
		button_simulation_.drawButton(window_);
		window_.draw(status_text_);
	}
	else if (state_ == Employees) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		button_add_.drawButton(window_);
		button_remove_.drawButton(window_);
		button_list_.drawButton(window_);
		window_.draw(status_text_);
		window_.draw(esc_text_);
		window_.draw(back_button_);
	}
	else if (state_ == Add) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		input_add_.drawInput(window_);
		button_confirm_1_.drawButton(window_);
		window_.draw(status_text_);
		window_.draw(esc_text_);
		window_.draw(back_button_);
	}
	else if (state_ == Remove) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		input_remove_.drawInput(window_);
		button_confirm_1_.drawButton(window_);
		window_.draw(status_text_);
		window_.draw(esc_text_);
		window_.draw(back_button_);
	}
	else if (state_ == List) {
		drawEmployeeList(window_, system_, font_, status_text_, esc_text_, back_button_, top_bar_, title_text_);
	}
	else if (state_ == Rooms) {
		drawRoomsList(window_, system_, font_, status_text_, esc_text_, back_button_, top_bar_, title_text_);
	}
	else if (state_ == Cards) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		input_id_.drawInput(window_);
		input_level_.drawInput(window_);
		button_confirm_2_.drawButton(window_);
		window_.draw(status_text_);
		window_.draw(esc_text_);
		window_.draw(back_button_);
	}
	else if (state_ == Simulation) {
		window_.draw(top_bar_);
		window_.draw(title_text_);
		input_card_.drawInput(window_);
		input_room_.drawInput(window_);
		button_confirm_2_.drawButton(window_);
		window_.draw(status_text_);
		window_.draw(esc_text_);
		window_.draw(back_button_);
	}

	window_.display();
}

int main() {
	srand(time(0));

	System system;
	AppState state = Menu;

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "AccesGuard");
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.openFromFile("JosefinSans-SemiBold.ttf")) {
		std::cerr << "Nie udalo sie zaladowac czcionki JosefinSans-SemiBold.ttf" << std::endl;
		return -1;
	}

	sf::Texture back_texture;
	if (!back_texture.loadFromFile("icons8-left-2-100.png")) {
		std::cerr << "Nie udalo sie zaladowac ikony icons8-left-2-100.png" << std::endl;
		return -1;
	}
	back_texture.setSmooth(true);

	sf::Sprite back_button(back_texture);
	back_button.setPosition({ 20.f, 40.f });
	back_button.setScale({ 0.5f, 0.5f });

	sf::RectangleShape top_bar({ 800.f, 120.f });
	top_bar.setFillColor(sf::Color(35, 40, 50));

	sf::Text title_text(font, "System Kontroli Dostepu", 36);
	title_text.setFillColor(sf::Color::White);
	title_text.setOrigin({ (float)(int)(title_text.getLocalBounds().position.x + title_text.getLocalBounds().size.x) / 2.0f, (float)(int)(title_text.getLocalBounds().position.y + title_text.getLocalBounds().size.y / 2.0f) });
	title_text.setPosition({ 400.f, 65.f });

	sf::Text status_text(font, "Status: Gotowy", 20);
	status_text.setFillColor(sf::Color(180, 200, 255));
	status_text.setPosition({ 50.f, 500.f });

	sf::Text esc_text(font, "ESC - Powrot", 20);
	esc_text.setFillColor(sf::Color(180, 200, 255));
	esc_text.setPosition({ 50.f, 525.f });

	Button button_employee("Menu Pracownika", { 300.f, 60.f }, { 250.f, 160.f }, font, sf::Color(52, 120, 246));
	Button button_room("Lista Pokojow", { 300.f, 60.f }, { 250.f, 240.f }, font, sf::Color(52, 120, 246));
	Button button_card("Karta Dostepu", { 300.f, 60.f }, { 250.f, 320.f }, font, sf::Color(52, 120, 246));
	Button button_simulation("Symulacja Wejscia", { 300.f, 60.f }, { 250.f, 400.f }, font, sf::Color(52, 120, 246));
	Button button_confirm_1("Zapisz", { 200.f, 50.f }, { 300.f, 320.f }, font, sf::Color(52, 120, 246));
	Button button_confirm_2("Zapisz", { 200.f, 50.f }, { 300.f, 360.f }, font, sf::Color(52, 120, 246));
	Button button_add("Dodac Pracownika", { 300.f, 60.f }, { 250.f, 190.f }, font, sf::Color(52, 120, 246));
	Button button_remove("Usunac Pracownika", { 300.f, 60.f }, { 250.f, 270.f }, font, sf::Color(52, 120, 246));
	Button button_list("Lista Pracownikow", { 300.f, 60.f }, { 250.f, 350.f }, font, sf::Color(52, 120, 246));

	Input input_add({ 400.f, 50.f }, { 200.f, 250.f }, font, "Wprowadz imie pracownika");
	Input input_remove({ 400.f, 50.f }, { 200.f, 250.f }, font, "Wprowadz ID pracownika");
	Input input_id({ 400.f, 50.f }, { 200.f, 220.f }, font, "Wprowadz ID");
	Input input_level({ 400.f, 50.f }, { 200.f, 290.f }, font, "Poziom (Guest/Worker/Admin)");
	Input input_card({ 400.f, 50.f }, { 200.f, 220.f }, font, "Wprowadz numer karty");
	Input input_room({ 400.f, 50.f }, { 200.f, 290.f }, font, "Nazwa pokoju");

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseEvent->button == sf::Mouse::Button::Left) {
					sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
					mouseClick(state, mouse_position, system, status_text, back_button, button_employee, button_room, button_card, button_simulation, button_add, button_remove, button_list, button_confirm_1, button_confirm_2, input_add, input_remove, input_id, input_level, input_card, input_room);
				}
			}
			if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
				if (input_add.isActive()) {
					input_add.keyboardInput(textEvent->unicode);
				}
				else if (input_remove.isActive()) {
					input_remove.keyboardInput(textEvent->unicode);
				}
				else if (input_id.isActive()) {
					input_id.keyboardInput(textEvent->unicode);
				}
				else if (input_level.isActive()) {
					input_level.keyboardInput(textEvent->unicode);
				}
				else if (input_card.isActive()) {
					input_card.keyboardInput(textEvent->unicode);
				}
				else if (input_room.isActive()) {
					input_room.keyboardInput(textEvent->unicode);
				}
			}
			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
				if (keyEvent->code == sf::Keyboard::Key::Escape)
				{
					deactivateAllInputs(input_add, input_remove, input_id, input_level, input_card, input_room);

					if (state == Add || state == Remove || state == List) {
						state = Employees;
						status_text.setString("Status: Wrocono do menu pracownika");
					}
					else {
						state = Menu;
						status_text.setString("Status: Wrocono do menu");
					}
				}
			}
		}

		renderInterface(window, state, system, font, top_bar, title_text, status_text, esc_text, back_button, button_employee, button_room, button_card, button_simulation, button_add, button_remove, button_list, button_confirm_1, button_confirm_2, input_add, input_remove, input_id, input_level, input_card, input_room);
	}

	return 0;
}