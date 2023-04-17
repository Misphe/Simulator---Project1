#pragma once
#include "Plant.h"

class WolfBerries : public Plant {
public:
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;
	int DefenseResult(Organism& attacker) override;
	std::string GetName() const override;

	WolfBerries(World& ref_world);
	WolfBerries(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
	char GetSymbol2() const;
	int GetColor() const override;
};

