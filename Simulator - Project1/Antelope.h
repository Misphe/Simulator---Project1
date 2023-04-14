#pragma once
#include "Animal.h"
class Antelope : public Animal {
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Antelope(World& ref_world);
	Antelope(World& ref_world, int set_x, int set_y);

	void Action() override;
	void Collision(Organism* defender) override;
	int DefenseResult(Organism& attacker) override;

	bool AntelopeEscaped();

	char GetSymbol() const override;
};

