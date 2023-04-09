#include "Wolf.h"
#include "World.h"
#include "Libraries.h"


void Wolf::Draw() {
	int x = (GetX() * 2) + 1;
	int y = GetY() + 1;
	World::MoveCursor(x, y);
	_putch('W');
}

Wolf::Wolf(World& ref_world) : Animal(ref_world) {
	SetStrength(9);
	SetInitiative(5);
}