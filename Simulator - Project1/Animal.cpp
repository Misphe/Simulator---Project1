#include "Animal.h"
#include "Libraries.h"
#include "World.h"
#include <memory>

void Animal::Action() {
	//rand() % 2 ? MoveX(rand() % 2 ? 1 : -1) : MoveY(rand() % 2 ? 1 : -1);
	if (rand() % 2) {
		rand() % 2 ? MoveX(1) : MoveX(-1);
	}
	else {
		rand() % 2 ? MoveY(1) : MoveY(-1);
	}
	alive_time++;
}

void Animal::Collision(std::unique_ptr<Organism>& collided) {

	if (typeid(*collided) == typeid(*this)) {
		// breeding case

		// Create a new instance of the same type as the current object
		std::unique_ptr<Organism> new_animal = Breed();

		int x_change = (rand() % 2) ? 1 : -1;
		int y_change = (rand() % 2) ? 1 : -1;
		new_animal->MoveX(x_change);
		new_animal->MoveY(y_change);
		world.AddNewOrganism(std::move(new_animal));
	}

	else {
		// fight case
	}

	// common code
}


