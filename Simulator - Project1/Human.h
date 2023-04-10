#pragma once
#include "Animal.h"
class Human : public Animal {
public:
	void Action() override;
	void Collision(std::unique_ptr<Organism>& collided) override;
	void Draw() override;
	std::unique_ptr<Animal> Breed() const override;

	Human(World& ref_world);
};

