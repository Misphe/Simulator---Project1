#pragma once
#include "Animal.h"
class Antelope : public Animal {
private:
	bool AntelopeEscaped();
	void Action() override;
	void Collision() override;
	int DefenseResult(Organism& attacker) override;

public:
	void Draw() const override;

	Antelope(World& ref_world);
	Antelope(World& ref_world, int set_x, int set_y);
	std::unique_ptr<Animal> Breed() const override;


	char GetSymbol() const override;
	int GetColor() const override;
	std::string GetName() const override;
};

