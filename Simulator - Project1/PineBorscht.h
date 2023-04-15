#pragma once
#include "Plant.h"
class PineBorscht : public Plant {
public:
	void Action() override;
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;
	int DefenseResult(Organism& attacker) override;

	PineBorscht(World& ref_world);
	PineBorscht(World& ref_world, int set_x, int set_y);

	void KillAdjacent();
	char GetSymbol() const override;
	char GetSymbol2() const;
};

