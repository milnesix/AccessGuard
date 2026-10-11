#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include <stdexcept>
#include "card.h"
#include "employee.h"
#include "room.h"

class System {
private:
	std::vector<Employee*> employees;
	std::vector<Room*> rooms;
public:
	System();
	~System();

	void addEmployee(std::string employee_name_, int employee_id_);
	std::string removeEmployee(int employee_id_);
	void giveCard(int employee_id_, int card_number_, std::string card_level_);
	std::string loginSimulation(int card_number_, std::string room_name_);

	const std::vector<Employee*>& getEmployees() const {
		return employees;
	}
	const std::vector<Room*>& getRooms() const {
		return rooms;
	}
};

#endif