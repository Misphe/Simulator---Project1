#include "Antelope.h"
#include "World.h"
#include "Libraries.h"


void Antelope::Draw() const {
	world.SetColor(SET_BG_LIGHTMAGENTA);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

void Antelope::Action() {

	world.DeleteOrganismFromSlot(*this);
	UpdatePrevPosition();

	// the while statement stands for not allowing moving into walls
	do {
		if (rand() % 2) {
			rand() % 2 ? this->MoveX(ANTELOPE_JUMP) : this->MoveX(-ANTELOPE_JUMP);
		}
		else {
			rand() % 2 ? this->MoveY(ANTELOPE_JUMP) : this->MoveY(-ANTELOPE_JUMP);
		}
	} while (GetPosition() == GetPrevPosition());

	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
	alive_time++;
}

void Antelope::Collision() {
	Organism* defender = world.CheckForCollision(*this);
	if (defender != nullptr) {
		if (typeid(*defender) == typeid(*this)) {
			GoBack();
			std::unique_ptr<Animal> new_animal = Breed();
			if (new_animal->SetChildsPosition(this->GetPosition(), defender->GetPosition())) {
				//new_animal->Draw();
				world.PushNewLog(world.CreateBreedLog(*new_animal));
				world.AddNewOrganism(std::move(new_animal));
			}
			return;
		}
		if (AntelopeEscaped()) {
			// do nothing else
			return;
		}
		Animal::Collision();
	}
	world.SetOrganismToSlot(*this);
}

int Antelope::DefenseResult(Organism& attacker)
{
	// explanation for that in if statement
	UpdatePrevPosition();
	if (AntelopeEscaped()) {

		// we do it to ensure that we are changing pointer to nullptr only for slot that is under
		// the current antelope. If we didnt do it, some bugs could appear.
		// e.g. antelope moves from (2,0) to (4,0). Fox moves to (2,0), Wolf kills antelope -> Antelope could po-
		// tentially delete pointer to fox if it used with PrevPos at (2,0)
		world.UpdateAnimalSlot(*this);

		return DEFENDER_RUNS_AWAY;
	}

	return Animal::DefenseResult(attacker);
}

Antelope::Antelope(World& ref_world) : Animal(ref_world) {
	SetStrength(ANTELOPE_STRENGTH);
	SetInitiative(ANTELOPE_INITIATIVE);
}

Antelope::Antelope(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(ANTELOPE_STRENGTH);
	SetInitiative(ANTELOPE_INITIATIVE);
}

std::unique_ptr<Animal> Antelope::Breed() const {
	return std::make_unique<Antelope>(world, GetX(), GetY());
}

bool Antelope::AntelopeEscaped() {
	if (rand() % 2) {
		return false;
	}

	// if empty adjacent cell found -> Antelope moves
	Position tmp = GetEmptyAdjacent();
	if (tmp.x != NO_EMPTY_ADJACENT) {
		world.DecrementSlot(GetPosition());
		SetPosition(tmp);
		world.IncrementSlot(GetPosition());
		return true;
	}

	return false;
}

char Antelope::GetSymbol() const {
	return ANTELOPE_SYMBOL;
}

std::string Antelope::GetName() const {
	return "Antelope";
}
