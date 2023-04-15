#include "Turtle.h"
#include "World.h"
#include "Libraries.h"


void Turtle::Draw() const {
	world.SetColor(SET_BG_CYAN);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

void Turtle::Action() {
	// unlinking 
	world.DeleteOrganismFromSlot(*this);
	UpdatePrevPosition();

	// if rand() returns 0 -> animal moves (that's 25% chance)
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
