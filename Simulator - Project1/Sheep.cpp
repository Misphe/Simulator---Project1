#include "Sheep.h"
#include "World.h"
#include "Libraries.h"


void Sheep::Draw() const  {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(SHEEP_SYMBOL);
}

Sheep::Sheep(World& ref_world) : Animal(ref_world) {
	SetStrength(4);
	SetInitiative(4);
}

Sheep::Sheep(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(4);
	SetInitiative(4);
}

char Sheep::GetSymbol() const {
	return SHEEP_SYMBOL;
}

std::unique_ptr<Animal> Sheep::Breed() const {
	return std::make_unique<Sheep>(world, GetX(), GetY());
}