#include "Plant.h"
#include "World.h"
#include "Libraries.h"

void Plant::Action() {
	// 5% to continue
	if (rand() % PLANT_SPREAD_CHANCE) {
		return;
	}
	
	Position new_pos = GetEmptyAdjacent();
	if (new_pos.x == NO_EMPTY_ADJACENT) return;

	std::unique_ptr<Plant> new_plant = Spread();
	new_plant->SetPosition(new_pos);
	world.PushNewLog(world.CreateBreedLog(*new_plant));
	world.AddNewOrganism(std::move(new_plant));
	alive_time++;
}

void Plant::Collision() {
	return;
}

Plant::Plant(World& ref_world) : Organism(ref_world) {
	SetInitiative(PLANT_STRENGTH);
}

int Plant::DefenseResult(Organism& attacker) {
	return ATTACKER_EATS;
}

Plant::Plant(World& ref_world, int set_x, int set_y) : Organism(ref_world, set_x, set_y) {
	SetInitiative(PLANT_STRENGTH);
}
