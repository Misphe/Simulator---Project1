#pragma once
#include "Plant.h"
class Guarana : public Plant {
public:
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;
	int DefenseResult(Organism& attacker) override;
	std::string GetName() const override;

	Guarana(World& ref_world);
	Guarana(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
	int GetColor() const override;
};

