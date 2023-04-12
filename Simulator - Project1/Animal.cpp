#include "Animal.h"
#include "Libraries.h"
#include "World.h"
#include <memory>

void Animal::Action() {
	//rand() % 2 ? MoveX(rand() % 2 ? 1 : -1) : MoveY(rand() % 2 ? 1 : -1);
	UpdatePrevPosition();
	RandomMove();
	alive_time++;
}

void Animal::Collision(std::unique_ptr<Organism>& collided) {
	if (!collided->IsAlive()) return;

	if (typeid(*collided) == typeid(*this)) {
		// breeding case
		GoBack();
		// Create a new instance of the same type as the current object
		std::unique_ptr<Animal> new_animal = Breed();
		if (new_animal->SetChildsPosition(this->GetPosition(), collided->GetPosition())) {
			new_animal->Draw();
			world.AddNewOrganism(std::move(new_animal));
		}
	}
	else {
 		if (AttackerWins(collided)) {
			collided->Die();
		}
		else {
			this->Die();
		}
	}
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

bool Animal::AttackerWins(std::unique_ptr<Organism>& victim) {
	return !victim->Defended(*this);
}

bool Animal::Defended(Organism& attacker) {
	if (this->GetStrength() > attacker.GetStrength()) {
		return true;
	}
	else if (this->GetStrength() < attacker.GetStrength()) {
		return false;
	}
	else {
		return this->GetAliveTime() > attacker.GetAliveTime();
	}
}

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
