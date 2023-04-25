#pragma once
#include "Plant.h"
class PineBorscht : public Plant {
private:
	void Action() override;
	void KillAdjacent();
	int DefenseResult(Organism& attacker) override;

public:
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;
	std::string GetName() const override;

	PineBorscht(World& ref_world);
	PineBorscht(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
	int GetColor() const override;
};

