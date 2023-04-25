#pragma once
#include "Animal.h"
class Fox : public Animal {
private:
	void Action() override;
	void FoxMove();
	bool FoxSafeAtSpot(Position spot);

public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	Fox(World& ref_world);
	Fox(World& ref_world, int set_x, int set_y);


	char GetSymbol() const override;
	std::string GetName() const override;
	int GetColor() const override;
};

