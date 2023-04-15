#include "Plant.h"
#include "World.h"
#include "Libraries.h"

void Plant::Action() {
	// 25% to continue
	if (rand() % 4) {
		return;
	}
	
	Position new_pos = GetEmptyAdjacent();
	if (new_pos.x == NO_EMPTY_ADJACENT) return;

	std::unique_ptr<Plant> new_plant = Spread();
	new_plant->SetPosition(new_pos);
	world.AddNewOrganism(std::move(new_plant));
}

void Plant::Collision() {
	return;
}

Plant::Plant(World& ref_world) : Organism(ref_world) {
	SetInitiative(0);
}

int Plant::DefenseResult(Organism& attacker) {
	return ATTACKER_WINS;
}

Plant::Plant(World& ref_world, int set_x, int set_y) : Organism(ref_world, set_x, set_y) {
	SetInitiative(0);
}
