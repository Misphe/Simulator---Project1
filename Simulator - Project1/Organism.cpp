#include "Organism.h"
#include "World.h"
#include "Libraries.h"

void Organism::SetX(int new_x) {
	if (new_x < world.GetSizeX() && new_x >= 0) {
		position.x = new_x;
	}
}

void Organism::SetY(int new_y) {
	if (new_y < world.GetSizeY() && new_y >= 0) {
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

// returns position to the randomly picked adjacent empty cell. If that cell doesn't exist
// returns position with error x and y
Position Organism::GetEmptyAdjacent() {
	int x = this->GetX();
	int y = this->GetY();
	Position adjacent[] = { { 1, 0 }, { -1,0 }, { 0,1 }, { 0,-1 } };
	bool tested[] = { false,false,false,false };
	int random;
	Position tmp;
	for (int i = 0; i < 4; i++) {
		while (true) {
			random = rand() % 4;
			if (tested[random] != true) {
				tested[random] = true;
				tmp = { x + adjacent[random].x, y + adjacent[random].y };
				if (tmp.InsideWorld(world.GetSizeX(), world.GetSizeY()) && world.IsEmpty(tmp)) {
					return tmp;
				}
				break;
			}
		}
	}
	return { NO_EMPTY_ADJACENT, NO_EMPTY_ADJACENT };
}

void Organism::Die() {
	alive = false;
	world.DecrementSlot(GetPosition());
}

const bool& Organism::IsAlive() const {
	return alive;
}

Organism::Organism(World& ref_world) : world(ref_world), alive_time(1) {
	int set_x = rand() % world.GetSizeX();
	int set_y = rand() % world.GetSizeY();
	while (!world.IsEmpty({set_x, set_y})) {
		int set_x = rand() % world.GetSizeX();
		int set_y = rand() % world.GetSizeY();
	}
	SetX(set_x);
	SetY(set_y);
	alive = true;
}

Organism::Organism(World& ref_world, int set_x, int set_y) : world(ref_world), alive_time(1) {
	SetX(set_x);
	SetY(set_y);
	alive = true;
}