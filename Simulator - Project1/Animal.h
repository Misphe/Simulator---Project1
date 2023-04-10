#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
	virtual void Action() override;
	virtual void Collision(std::unique_ptr<Organism>& collided) override;
	virtual void Draw() override = 0;
	virtual std::unique_ptr<Animal> Breed() const = 0;
	Animal(World& ref_world) : Organism(ref_world) {}
};

