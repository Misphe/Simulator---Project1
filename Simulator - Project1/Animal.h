#pragma once
#include "Organism.h"

class Animal : public Organism {
protected:
	Position prev_position;
public:
	virtual void Action() override;
	virtual void Collision(std::unique_ptr<Organism>& collided) override;
	virtual void Draw() override = 0;
	virtual std::unique_ptr<Animal> Breed() const = 0;

	const Position& GetPrevPosition() const;
	void UpdatePrevPosition();
	void GoBack(); // in position

	void RandomMove();

	Animal(World& ref_world) : Organism(ref_world), prev_position(position) {}
	Animal(World& ref_world, int set_x, int set_y) : Organism(ref_world, set_x, set_y), prev_position(position) {}
};

