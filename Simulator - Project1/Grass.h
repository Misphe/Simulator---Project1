#pragma once
#include "Plant.h"
class Grass : public Plant {
public:
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;

	Grass(World& ref_world);
	Grass(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
};

