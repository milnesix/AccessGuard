#include "card.h"

Card::Card(int card_number_, status card_status_) {
	card_number = card_number_;
	card_status = card_status_;
	amount = 0;
}

Card::~Card() {}

int Card::getCardNumber() {
	return card_number;
}

status Card::getCardStatus() {
	return card_status;
}

void Card::addAttempt() {
	amount++;

	if (amount >= 3) {
		card_status = Blocked;
	}
}

void Card::resetAttempt() {
	amount = 0;
}