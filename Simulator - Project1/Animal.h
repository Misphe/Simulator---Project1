#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
	virtual void Action() override;
	virtual void Collision(std::unique_ptr<Organism>& defender) override;
	virtual void Draw() override = 0;
	virtual std::unique_ptr<Animal> Breed() const = 0;

	void RandomMove();
	int FightResult(std::unique_ptr<Organism>& victim);
	virtual int DefenseResult(Organism& attacker) override;

	Animal(World& ref_world) : Organism(ref_world) {}
	Animal(World& ref_world, int set_x, int set_y) : Organism(ref_world, set_x, set_y) {}

	// returns false when no space
	bool SetChildsPosition(const Position& parent1_pos, const Position& parent2_pos);
};

