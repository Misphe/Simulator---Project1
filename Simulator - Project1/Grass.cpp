#include "Grass.h"
#include "Libraries.h"
#include "World.h"

void Grass::Draw() const {
	world.SetColor(SET_BG_LIGHTGREEN);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

std::unique_ptr<Plant> Grass::Spread() const {
	return std::make_unique<Grass>(world, GetX(), GetY());
}

Grass::Grass(World& ref_world) : Plant(ref_world) {
	SetStrength(0);
}

Grass::Grass(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(0);
}

char Grass::GetSymbol() const {
	return GRASS_SYMBOL;
}
