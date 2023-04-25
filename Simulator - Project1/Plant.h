#pragma once
#include "Organism.h"

class Plant : public Organism {
protected:
	virtual std::unique_ptr<Plant> Spread() const = 0;

public:
	virtual void Action() override;
	virtual void Collision() override;
	virtual void Draw() const override = 0;
	virtual std::string GetName() const override = 0;

	virtual char GetSymbol() const = 0;
	virtual int DefenseResult(Organism& attacker) override;

	Plant(World& ref_world, int set_x, int set_y);
	Plant(World& ref_world);
	
};

