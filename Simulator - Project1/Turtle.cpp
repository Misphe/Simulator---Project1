#include "Turtle.h"
#include "World.h"
#include "Libraries.h"


void Turtle::Draw() const {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(TURTLE_SYMBOL);
}

void Turtle::Action() {
	// if rand() returns 0 -> animal moves (that's 25% chance)
	UpdatePrevPosition();
	if (!(rand() % 4)) {
		Animal::Action();
		return;
	}
	alive_time++;
}

int Turtle::DefenseResult(Organism& attacker)
{
	if (attacker.GetStrength() < 5) {
		return ATTACKER_RETREATS;
	}
	else {
		return Animal::DefenseResult(attacker);
	}
}

char Turtle::GetSymbol() const {
	return TURTLE_SYMBOL;
}

Turtle::Turtle(World& ref_world) : Animal(ref_world) {
	SetStrength(2);
	SetInitiative(1);
}

Turtle::Turtle(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(2);
	SetInitiative(1);
}

std::unique_ptr<Animal> Turtle::Breed() const {
	return std::make_unique<Turtle>(world, GetX(), GetY());
}
