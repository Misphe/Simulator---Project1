#include "Organism.h"
#include "World.h"

void Organism::SetX(int new_x) {
	if (new_x <= world.GetSize() && new_x >= 1) {
		position.x = new_x;
	}
}

void Organism::SetY(int new_y) {
	if (new_y <= world.GetSize() && new_y >= 1) {
		position.y = new_y;
	}
}

void Organism::SetStrength(int new_strength) {
	strength = new_strength;
}

void Organism::SetInitiative(int new_initiative) {
	initiative = new_initiative;
}

void Organism::SetPosition(Position new_position) {
	position = new_position;
}

void Organism::MoveX(int change) {
	SetX(GetX() + change);
}

void Organism::MoveY(int change) {
	SetY(GetY() + change);
}

const int& Organism::GetX() const {
	return position.x;
}

const int& Organism::GetY() const {
	return position.y;
}

const int& Organism::GetStrength() const {
	return strength;
}

const int& Organism::GetInitiative() const {
	return initiative;
}

const int& Organism::GetAliveTime() const {
	return alive_time;
}

const Position& Organism::GetPosition() const {
	return position;
}

Organism::Organism(World& ref_world) : world(ref_world), alive_time(1) {
	int set_x = rand() % world.GetSize() + 1;
	int set_y = rand() % world.GetSize() + 1;
	SetX(set_x);
	SetY(set_y);
}

Organism::Organism(World& ref_world, int set_x, int set_y) : world(ref_world), alive_time(1) {
	SetX(set_x);
	SetY(set_y);
}