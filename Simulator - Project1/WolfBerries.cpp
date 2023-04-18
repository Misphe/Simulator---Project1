#include "WolfBerries.h"
#include "Libraries.h"
#include "World.h"

void WolfBerries::Draw() const {
	world.SetColor(SET_BG_DARKGRAY);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

std::unique_ptr<Plant> WolfBerries::Spread() const {
	return std::make_unique<WolfBerries>(world, GetX(), GetY());
}

WolfBerries::WolfBerries(World& ref_world) : Plant(ref_world) {
	SetStrength(WOLFBERRIES_STRENGTH);
}

WolfBerries::WolfBerries(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(WOLFBERRIES_STRENGTH);
}

char WolfBerries::GetSymbol() const {
	return WOLFBERRIES_SYMBOL;
}

int WolfBerries::GetColor() const {
	return SET_BG_DARKGRAY;
}

int WolfBerries::DefenseResult(Organism& attacker) {
	return BOTH_DIED;
}

std::string WolfBerries::GetName() const {
	return "Wolf Berries";
}
