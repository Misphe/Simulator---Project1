#pragma once
#include "Plant.h"
class Dandelion : public Plant {
private:
	void Action() override;
public:
	void Draw() const override;
	std::unique_ptr<Plant> Spread() const override;
	std::string GetName() const override;

	Dandelion(World& ref_world);
	Dandelion(World& ref_world, int set_x, int set_y);

	char GetSymbol() const override;
	int GetColor() const override;
};

