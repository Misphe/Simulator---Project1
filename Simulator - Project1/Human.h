#pragma once
#include "Animal.h"
class Human : public Animal {
private:
	char move;
	bool power_activated;
public:
	void Action() override;
	void Collision() override;
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;

	int DefenseResult(Organism& attacker) override;

	Human(World& ref_world);
	void TakeInput();

	void SetMove(int& input);
	void FlickPowerState();

	const char& GetInput() const;
	const bool& PowerActivated() const;

	void Die() override;

	char GetSymbol() const override;
};

