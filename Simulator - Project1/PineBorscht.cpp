#include "PineBorscht.h"
#include "World.h"
#include "Libraries.h"

void PineBorscht::Draw() const {
	world.SetColor(SET_BG_LIGHTRED);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

std::unique_ptr<Plant> PineBorscht::Spread() const {
	return std::make_unique<PineBorscht>(world, GetX(), GetY());
}

PineBorscht::PineBorscht(World& ref_world) : Plant(ref_world) {
	SetStrength(PINEBORSCHT_STRENGTH);
}

PineBorscht::PineBorscht(World& ref_world, int set_x, int set_y) : Plant(ref_world, set_x, set_y) {
	SetStrength(PINEBORSCHT_STRENGTH);
}

char PineBorscht::GetSymbol() const {
	return PINEBORSCHT_SYMBOL_1;
}

char PineBorscht::GetSymbol2() const {
	return PINEBORSCHT_SYMBOL_2;
}

void PineBorscht::Action() {
	KillAdjacent();
	Plant::Action();
}

int PineBorscht::DefenseResult(Organism& attacker) {
	return BOTH_DIED;
}

std::string PineBorscht::GetName() const {
	return "Pine Borscht";
}

void PineBorscht::KillAdjacent() {
	int x = GetX();
	int y = GetY();
	Position variations[] = { {1,0},{-1,0},{0,1},{0,-1} };
	for (Position& slot : variations) {

		Position adjacent = { x + slot.x, y + slot.y };
		if (!adjacent.InsideWorld(world.GetSizeX(), world.GetSizeY())) continue;

		Organism* victim = world.GetOrganismAtPos(adjacent);
		if (!dynamic_cast<Animal*>(victim)) continue;

		victim->Die();
		world.DeleteOrganismFromSlot(*victim);
		world.PushNewLog(world.CreateLog(*this, *victim, ATTACKER_WINS));

	}
}