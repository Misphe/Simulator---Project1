#include "Wolf.h"
#include "World.h"
#include "Libraries.h"


void Wolf::Draw() const {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(WOLF_SYMBOL);
}

Wolf::Wolf(World& ref_world) : Animal(ref_world) {
	SetStrength(9);
	SetInitiative(5);
}

Wolf::Wolf(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(9);
	SetInitiative(5);
}

char Wolf::GetSymbol() const {
	return WOLF_SYMBOL;
}

std::unique_ptr<Animal> Wolf::Breed() const {
	return std::make_unique<Wolf>(world, GetX(), GetY());
}