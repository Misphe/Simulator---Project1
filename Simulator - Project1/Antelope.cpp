#include "Antelope.h"
#include "World.h"
#include "Libraries.h"


void Antelope::Draw() const {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(ANTELOPE_SYMBOL);
}

void Antelope::Action() {
	// if rand() returns 0 -> animal moves (that's 25% chance)
	UpdatePrevPosition();
	do {
		if (rand() % 2) {
			rand() % 2 ? this->MoveX(2) : this->MoveX(-2);
		}
		else {
			rand() % 2 ? this->MoveY(2) : this->MoveY(-2);
		}
	} while (GetPosition() == GetPrevPosition());

	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
	alive_time++;
}

void Antelope::Collision(Organism* defender) {
	if (typeid(*defender) == typeid(*this)) {
		GoBack();
		std::unique_ptr<Animal> new_animal = Breed();
		if (new_animal->SetChildsPosition(this->GetPosition(), defender->GetPosition())) {
			//new_animal->Draw();
			world.AddNewOrganism(std::move(new_animal));
		}
		return;
	}
	if (AntelopeEscaped()) {
		//this->Draw();
		//defender->Draw();
		return;
	}
	Animal::Collision(defender);
}

int Antelope::DefenseResult(Organism& attacker)
{
	if (AntelopeEscaped()) {
		//this->Draw();
		//attacker.Draw();
		return DEFENDER_RUNS_AWAY;
	}
	return Animal::DefenseResult(attacker);
}

Antelope::Antelope(World& ref_world) : Animal(ref_world) {
	SetStrength(4);
	SetInitiative(4);
}

Antelope::Antelope(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(4);
	SetInitiative(4);
}

std::unique_ptr<Animal> Antelope::Breed() const {
	return std::make_unique<Antelope>(world, GetX(), GetY());
}

bool Antelope::AntelopeEscaped() {
	if (rand() % 2) {
		return false;
	}
	Position adjacent[] = { { 1, 0 }, { -1,0 }, { 0,1 }, { 0,-1 } };
	bool tested[] = { false,false,false,false };
	int random;
	Position tmp;
	for (int i = 0; i < 4; i++) {
		while (true) {
			random = rand() % 4;
			if (tested[random] != true) {
				tested[random] = true;
				tmp = { GetX() + adjacent[random].x, GetY() + adjacent[random].y };
				if (tmp.InsideWorld(world.GetSizeX(), world.GetSizeY()) && world.IsEmpty(tmp)) {
					world.DecrementSlot(GetPosition());
					SetPosition(tmp);
					world.IncrementSlot(GetPosition());
					world.UpdateOrganismSlot(*this);

					return true;
				}
				break;
			}
		}
	}
	return false;
}

char Antelope::GetSymbol() const {
	return ANTELOPE_SYMBOL;
}
