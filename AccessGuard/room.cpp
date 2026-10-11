#include "room.h"

Room::Room(std::string room_name_, level room_level_) {
	room_name = room_name_;
	room_level = room_level_;
}

Room::~Room() {}

std::string Room::getRoomName() {
	return room_name;
}

level Room::getRoomLevel() {
	return room_level;
}