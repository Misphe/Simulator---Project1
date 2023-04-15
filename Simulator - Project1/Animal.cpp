#include "Animal.h"
#include "Libraries.h"
#include "World.h"
#include <memory>

void Animal::Action() {
	// starts with unlinking current animal from its position in the map
	world.DeleteOrganismFromSlot(*this);

	UpdatePrevPosition();
	RandomMove();
	alive_time++;
}

void Animal::Collision() {
	Organism* defender = world.CheckForCollision(*this);
	if (defender != nullptr) {
		if (!defender->IsAlive()) return;

		// breeding case
		if (typeid(*defender) == typeid(*this)) {

			// Both animals stay in their places
			GoBack();

			std::unique_ptr<Animal> new_animal = Breed();
			if (new_animal->SetChildsPosition(this->GetPosition(), defender->GetPosition())) {
				
				// if no space for child -> nothing happens
				world.AddNewOrganism(std::move(new_animal));
			}
		}
		else {
			int result = FightResult(defender);
			switch (result) {
			case ATTACKER_WINS:

				defender->Die();
				world.DeleteOrganismFromSlot(*defender);
				break;
			case DEFENDER_WINS:

				// as attacker is unlinked from the field ( see Action() ) it doesnt 
				// have to be removed like in the previous case
				this->Die();
				break;
			case ATTACKER_RETREATS:
				GoBack();
				break;
			case DEFENDER_RUNS_AWAY:
				break;
			};
		}
	}

	// After a turn of every Animal, if it is still alive -> its position is saved in the map
	world.SetOrganismToSlot(*this);
}

void Animal::RandomMove() {
	do {
		if (rand() % 2) {
			rand() % 2 ? this->MoveX(1) : this->MoveX(-1);
		}
		else {
			rand() % 2 ? this->MoveY(1) : this->MoveY(-1);
		}
	} while (GetPosition() == GetPrevPosition());

	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
}

int Animal::FightResult(Organism*& victim) {
	return victim->DefenseResult(*this);
}

int Animal::DefenseResult(Organism& attacker) {
	if (this->GetStrength() > attacker.GetStrength()) {
		return DEFENDER_WINS;
	}
	else if (this->GetStrength() < attacker.GetStrength()) {
		return ATTACKER_WINS;
	}
	else if (this->GetAliveTime() > attacker.GetAliveTime()){
		return DEFENDER_WINS;
	}
	else if (this->GetAliveTime() < attacker.GetAliveTime()) {
		return ATTACKER_WINS;
	}
	else {
		return ATTACKER_WINS;
	}
}

// returns true if found space for the child
bool Animal::SetChildsPosition(const Position& parent1_pos, const Position& parent2_pos) {
	Position adjacent[] = { { 1, 0 }, { -1,0 }, { 0,1 }, { 0,-1 } };
	bool tested[] = { false,false,false,false };
	int random;
	Position tmp;
	for (int i = 0; i < 4; i++) {
		while (true) {
			random = rand() % 4;
			if (tested[random] != true) {
				tested[random] = true;
				tmp = { parent1_pos.x + adjacent[random].x, parent1_pos.y + adjacent[random].y };
				if (tmp.InsideWorld(world.GetSizeX(), world.GetSizeY()) && world.IsEmpty(tmp)) {
					SetPosition(tmp);
					UpdatePrevPosition();
					return true;
				}
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		tested[i] = false;
	}
	for (int i = 0; i < 4; i++) {
		while (true) {
			random = rand() % 4;
			if (tested[random] != true) {
				tested[random] = true;
				tmp = { parent2_pos.x + adjacent[random].x, parent2_pos.y + adjacent[random].y };
				if (tmp.InsideWorld(world.GetSizeX(), world.GetSizeY()) && world.IsEmpty(tmp)) {
					SetPosition(tmp);
					UpdatePrevPosition();
					return true;
				}
				break;
			}
		}
	}
	return false;
}

const Position& Animal::GetPrevPosition() const {
	return prev_position;
}

void Animal::UpdatePrevPosition() {
	prev_position = position;
}

void Animal::GoBack() {
	world.DecrementSlot(GetPosition());
	SetPosition(GetPrevPosition());
	world.IncrementSlot(GetPosition());
}

Animal::Animal(World& ref_world, int set_x, int set_y) : Organism(ref_world, set_x, set_y) {
	prev_position = position;
}

Animal::Animal(World& ref_world) : Organism(ref_world) {
	prev_position = position;
}