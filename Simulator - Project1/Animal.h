#pragma once
#include "Organism.h"

class Animal : public Organism {
protected:
	Position prev_position;
public:
	virtual void Action() override;
	virtual void Collision() override;
	virtual void Draw() const override = 0;
	virtual std::unique_ptr<Animal> Breed() const = 0;

	virtual char GetSymbol() const = 0;
	const Position& GetPrevPosition() const;
	void UpdatePrevPosition();

	void GoBack(); // in position

	void RandomMove();
	int FightResult(Organism*& victim);
	virtual int DefenseResult(Organism& attacker) override;

	Animal(World& ref_world);
	Animal(World& ref_world, int set_x, int set_y);

	// returns false when no space
	bool SetChildsPosition(const Position& parent1_pos, const Position& parent2_pos);
};

