#include "Animal.h"
#include "Libraries.h"

void Animal::Action() {
	//rand() % 2 ? MoveX(rand() % 2 ? 1 : -1) : MoveY(rand() % 2 ? 1 : -1);
	if (rand() % 2) {
		rand() % 2 ? MoveX(1) : MoveX(-1);
	}
	else {
		rand() % 2 ? MoveY(1) : MoveY(-1);
	}
}

void Animal::Collision() {
	// at the moment the breeding case
	
	// Animal* new_animal = new Animal(*this);
	// int x_change = (rand()%2) ? 1 : -1;
	// int y_change = (rand()%2) ? 1 : -1;
	// new_animal->MoveX(x_change);
	// new_animal->MoveY(y_change); 
	
	// world.add(*new_animal);
}