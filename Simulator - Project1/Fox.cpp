#include "Fox.h"
#include "World.h"
#include "Libraries.h"


void Fox::Draw() const {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(FOX_SYMBOL);
}

void Fox::Action() {
	// unlinking
	world.DeleteOrganismFromSlot(*this);
	UpdatePrevPosition();

	// smart type of movement -> Fox never goes where he loses
	FoxMove();

	alive_time++;
	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
}

Fox::Fox(World& ref_world) : Animal(ref_world) {
	SetStrength(3);
	SetInitiative(7);
}

Fox::Fox(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(3);
	SetInitiative(7);
}

std::unique_ptr<Animal> Fox::Breed() const {
	return std::make_unique<Fox>(world, GetX(), GetY());
}

void Fox::FoxMove() {
	Position adjacent[] = { { 1, 0 }, { -1,0 }, { 0,1 }, { 0,-1 } };
	bool tested[] = { false,false,false,false };
	int random;
	Position tmp;
	for (int i = 0; i < 4; i++) {
		while (true) {
			random = rand() % 4;
			if (tested[random] != true) {
				tested[random] = true;
				tmp = { GetX() + adjacent[random].x, GetY() + adjacent[random].y};
				if (tmp.InsideWorld(world.GetSizeX(), world.GetSizeY()) && FoxSafeAtSpot(tmp)) {
					SetPosition(tmp);
					return;
				}
				break;
			}
		}
	}
}

bool Fox::FoxSafeAtSpot(Position spot) {
	Organism* adjacent = world.GetOrganismAtPos(spot);
	if (adjacent == nullptr) {
		return true;
	}
	if (dynamic_cast<Fox*>(adjacent)) {
		return true;
	}
	if (GetStrength() > adjacent->GetStrength()) {
		return true;
	}
	else if (GetStrength() < adjacent->GetStrength()) {
		return false;
	}
	else if (GetAliveTime() > adjacent->GetAliveTime()) {
		return true;
	}
	else return false;
}

char Fox::GetSymbol() const {
	return FOX_SYMBOL;
}
