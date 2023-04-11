#include "Wolf.h"
#include "World.h"
#include "Libraries.h"


void Wolf::Draw() {
	int x = (GetX() * 2);
	int y = GetY();
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch('W');
}

Wolf::Wolf(World& ref_world) : Animal(ref_world) {
	SetStrength(9);
	SetInitiative(5);
}

Wolf::Wolf(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(9);
	SetInitiative(5);
}

std::unique_ptr<Animal> Wolf::Breed() const {
	return std::make_unique<Wolf>(world, GetX(), GetY());
}