#ifndef CARD_H
#define CARD_H

#include <iostream>

enum level {Guest, Worker, Admin};
enum status {Active, Blocked};

class Card {
protected:
	int card_number;
	status card_status;
	int amount;
public:
	Card(int card_number_, status card_status_);
	virtual ~Card();
	int getCardNumber();
	status getCardStatus();
	void addAttempt();
	void resetAttempt();
	virtual level getCardLevel() const = 0;
	virtual std::string getLevelName() const = 0;
};

class GuestCard : public Card {
public:
	GuestCard(int card_number_, status card_status_) : Card(card_number_, card_status_) {}
	level getCardLevel() const {
		return Guest;
	}
	std::string getLevelName() const {
		return "Guest";
	}
};

class WorkerCard : public Card {
public:
	WorkerCard(int card_number_, status card_status_) : Card(card_number_, card_status_) {}
	level getCardLevel() const {
		return Worker;
	}
	std::string getLevelName() const {
		return "Worker";
	}
};

class AdminCard : public Card {
public:
	AdminCard(int card_number_, status card_status_) : Card(card_number_, card_status_) {}
	level getCardLevel() const {
		return Admin;
	}
	std::string getLevelName() const {
		return "Admin";
	}
};

#endif