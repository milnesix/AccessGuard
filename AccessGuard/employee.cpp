#include "employee.h"

Employee::Employee(std::string employee_name_, int employee_id_) {
	employee_name = employee_name_;
	employee_id = employee_id_;
	employee_card = nullptr;
}

Employee::~Employee() {
	delete employee_card;
}

std::string Employee::getEmployeeName() {
	return employee_name;
}

int Employee::getEmployeeId() {
	return employee_id;
}

Card* Employee::getEmployeeCard() {
	return employee_card;
}

void Employee::assignCard(Card* employee_card_) {
	delete employee_card;
	employee_card = employee_card_;
}