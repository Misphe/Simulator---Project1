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
	if (attacker.GetStrength() <= MIN_ATTACK_TO_KILL) {
		return ATTACKER_RETREATS;
	}
	else {
		return Animal::DefenseResult(attacker);
	}
}

char Turtle::GetSymbol() const {
	return TURTLE_SYMBOL;
}

std::string Turtle::GetName() const {
	return "Turtle";
}

int Turtle::GetColor() const {
	return TURTLE_COLOR;
}

Turtle::Turtle(World& ref_world) : Animal(ref_world) {
	SetStrength(TURTLE_STRENGTH);
	SetInitiative(TURTLE_INITIATIVE);
}

Turtle::Turtle(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(TURTLE_STRENGTH);
	SetInitiative(TURTLE_INITIATIVE);
}

std::unique_ptr<Animal> Turtle::Breed() const {
	return std::make_unique<Turtle>(world, GetX(), GetY());
}
