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

	if (typeid(*collided) == typeid(*this)) {
		// breeding case
		//world.DrawWorld();
		GoBack();
		// Create a new instance of the same type as the current object
		std::unique_ptr<Animal> new_animal = Breed();
		while (new_animal->GetPosition() == collided->GetPosition() || new_animal->GetPosition() == this->GetPosition()) {
			new_animal->RandomMove();
		}

		world.AddNewOrganism(std::move(new_animal));
		//world.DrawWorld();
	}

	else {
		// fight case
	}

	// common code
}

const Position& Animal::GetPrevPosition() const {
	return prev_position;
}

void Animal::UpdatePrevPosition() {
	prev_position = position;
}

void Animal::GoBack() {
	SetPosition(GetPrevPosition());
}

void Animal::RandomMove() {
	if (rand() % 2) {
		rand() % 2 ? this->MoveX(1) : this->MoveX(-1);
	}
	else {
		rand() % 2 ? this->MoveY(1) : this->MoveY(-1);
	}
}

