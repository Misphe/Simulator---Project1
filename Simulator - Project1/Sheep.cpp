#include "Sheep.h"
#include "World.h"
#include "Libraries.h"


void Sheep::Draw() {
	int x = (GetX() * 2) + 1;
	int y = GetY() + 1;
	World::MoveCursor(x, y);
	_putch('S');
}

Sheep::Sheep(World& ref_world) : Animal(ref_world) {
	SetStrength(4);
	SetInitiative(4);
}