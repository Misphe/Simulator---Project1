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
	SetStrength(99);
}

WolfBerries::WolfBerries(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(99);
}

char WolfBerries::GetSymbol() const {
	return WOLFBERRIES_SYMBOL_1;
}

char WolfBerries::GetSymbol2() const {
	return WOLFBERRIES_SYMBOL_2;
}

int WolfBerries::DefenseResult(Organism& attacker) {
	attacker.Die();
	return ATTACKER_WINS;
}
