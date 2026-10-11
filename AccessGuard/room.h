#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "card.h"

class Room {
private:
	std::string room_name;
	level room_level;
public:
	Room(std::string room_name_, level room_level_);
	~Room();
	std::string getRoomName();
	level getRoomLevel();
};

#endif