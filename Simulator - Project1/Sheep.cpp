#include "Sheep.h"
#include "World.h"
#include "Libraries.h"


void Sheep::Draw() {
	int x = (GetX() * 2);
	int y = GetY();
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch('S');
}

Sheep::Sheep(World& ref_world) : Animal(ref_world) {
	SetStrength(4);
	SetInitiative(4);
}

std::unique_ptr<Animal> Sheep::Breed() const {
	return std::make_unique<Sheep>(world);
}