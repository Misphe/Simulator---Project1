#include "Guarana.h"
#include "Libraries.h"
#include "World.h"

void Guarana::Draw() const {
	world.SetColor(SET_BG_MAGENTA);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

std::unique_ptr<Plant> Guarana::Spread() const {
	return std::make_unique<Guarana>(world, GetX(), GetY());
}

Guarana::Guarana(World& ref_world) : Plant(ref_world) {
	SetStrength(0);
}

Guarana::Guarana(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(0);
}

char Guarana::GetSymbol() const {
	return GUARANA_SYMBOL;
}

int Guarana::DefenseResult(Organism& attacker) {
	attacker.SetStrength(attacker.GetStrength() + 3);
	return ATTACKER_WINS;
}
