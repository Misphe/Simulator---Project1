#pragma once
#include "Plant.h"
class Dandelion : public Plant {
public:
	void Action() override;
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;

	Dandelion(World& ref_world);
	Dandelion(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
};

