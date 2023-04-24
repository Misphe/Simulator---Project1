#include "Wolf.h"
#include "World.h"
#include "Libraries.h"


void Wolf::Draw() const {
	world.SetColor(SET_BG_GRAY);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

Wolf::Wolf(World& ref_world) : Animal(ref_world) {
	SetStrength(WOLF_STRENGTH);
	SetInitiative(WOLF_INITIATIVE);
}

Wolf::Wolf(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(WOLF_STRENGTH);
	SetInitiative(WOLF_INITIATIVE);
}

char Wolf::GetSymbol() const {
	return WOLF_SYMBOL;
}

std::string Wolf::GetName() const {
	return "Wolf";
}

int Wolf::GetColor() const {
	return WOLF_COLOR;
}

std::unique_ptr<Animal> Wolf::Breed() const {
	return std::make_unique<Wolf>(world, GetX(), GetY());
}