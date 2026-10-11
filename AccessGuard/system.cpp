#include "system.h"

System::System() {
	rooms.push_back(new Room("Enter", Guest));
	rooms.push_back(new Room("Hall", Guest));
	rooms.push_back(new Room("Office", Worker));
	rooms.push_back(new Room("Archive", Worker));
	rooms.push_back(new Room("Administration", Admin));
}

System::~System() {
	for (size_t i = 0; i < employees.size(); i++) {
		delete employees[i];
	}
	employees.clear();

	for (size_t i = 0; i < rooms.size(); i++) {
		delete rooms[i];
	}
	rooms.clear();
}

void System::addEmployee(std::string employee_name_, int employee_id_) {
	for (size_t i = 0; i < employees.size(); i++) {
		if (employees[i]->getEmployeeId() == employee_id_) {
			throw std::runtime_error("Pracownik o takim ID juz istnieje");
		}
	}
	employees.push_back(new Employee(employee_name_, employee_id_));
}

std::string System::removeEmployee(int employee_id_) {
	for (size_t i = 0; i < employees.size(); i++) {
		if (employees[i]->getEmployeeId() == employee_id_) {
			std::string employee_removed_name = employees[i]->getEmployeeName();

			delete employees[i];
			employees.erase(employees.begin() + i);

			return employee_removed_name;
		}
	}
	throw std::runtime_error("Nie znalieziono pracownika o takim ID");
}

void System::giveCard(int employee_id_, int card_number_, std::string card_level_) {
	for (size_t i = 0; i < employees.size(); i++) {
		if (employees[i]->getEmployeeCard() && employees[i]->getEmployeeCard()->getCardNumber() == card_number_) {
			throw std::runtime_error("Karta o takim numeru juz istnieje");
		}
	}

	Card* new_card = nullptr;

	if (card_level_ == "Guest") {
		new_card = new GuestCard(card_number_, Active);
	}
	else if (card_level_ == "Worker") {
		new_card = new WorkerCard(card_number_, Active);
	}
	else if (card_level_ == "Admin") {
		new_card = new AdminCard(card_number_, Active);
	}
	else {
		throw std::runtime_error("Niepoprawny poziom dostepu");
	}

	for (size_t i = 0; i < employees.size(); i++) {
		if (employees[i]->getEmployeeId() == employee_id_) {
			employees[i]->assignCard(new_card);
			return;
		}
	}

	delete new_card;
	throw std::runtime_error("Nie znaleziono pracownika o takim ID");
}

std::string System::loginSimulation(int card_number_, std::string room_name_) {
	Employee* foundEmployee = nullptr;
	Room* foundRoom = nullptr;

	for (size_t i = 0; i < employees.size(); i++) {
		if (employees[i]->getEmployeeCard() && employees[i]->getEmployeeCard()->getCardNumber() == card_number_) {
			foundEmployee = employees[i];
			break;
		}
	}

	for (size_t i = 0; i < rooms.size(); i++) {
		if (rooms[i]->getRoomName() == room_name_) {
			foundRoom = rooms[i];
			break;
		}
	}

	if (!foundEmployee) {
		throw std::runtime_error("Karta nie istnieje w systemie");
	}

	if (!foundRoom) {
		throw std::runtime_error("Pokoj nie istnieje w systemie");
	}

	if (foundEmployee->getEmployeeCard()->getCardStatus() == Blocked) {
		throw std::runtime_error("Karta jest zablokowana");
	}

	if (foundEmployee->getEmployeeCard()->getCardLevel() < foundRoom->getRoomLevel()) {
		foundEmployee->getEmployeeCard()->addAttempt();

		throw std::runtime_error("Brak uprawnien");
	}

	foundEmployee->getEmployeeCard()->resetAttempt();

	return foundEmployee->getEmployeeName();
}