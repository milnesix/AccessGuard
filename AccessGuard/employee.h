#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "card.h"

class Employee {
private:
	std::string employee_name;
	int employee_id;
	Card* employee_card;
public:
	Employee(std::string employee_name_, int employee_id_);
	~Employee();
	std::string getEmployeeName();
	int getEmployeeId();
	Card* getEmployeeCard();
	void assignCard(Card* employee_card_);
};

#endif