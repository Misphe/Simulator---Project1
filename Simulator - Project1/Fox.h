#pragma once
#include "Animal.h"
class Fox : public Animal {
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;
	void Action() override;

	Fox(World& ref_world);
	Fox(World& ref_world, int set_x, int set_y);

	void FoxMove();
	bool FoxSafeAtSpot(Position spot);

	char GetSymbol() const override;
	std::string GetName() const override;
};

