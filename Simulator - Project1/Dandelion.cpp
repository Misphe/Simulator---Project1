#include "Dandelion.h"
#include "Libraries.h"
#include "World.h"

void Dandelion::Draw() const {
	world.SetColor(SET_BG_YELLOW);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

std::unique_ptr<Plant> Dandelion::Spread() const {
	return std::make_unique<Dandelion>(world, GetX(), GetY());
}

void Dandelion::Action() {
	for (int i = 0; i < 3; i++) {
		Plant::Action();
	}
}

Dandelion::Dandelion(World& ref_world) : Plant(ref_world) {
	SetStrength(0);
}

Dandelion::Dandelion(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(0);
}

char Dandelion::GetSymbol() const {
	return DANDELION_SYMBOL;
}