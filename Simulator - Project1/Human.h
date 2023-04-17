#pragma once
#include "Animal.h"
class Human : public Animal {
private:
	char move;
	bool power_activated;
	int cooldown;
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
	const int& GetCooldown();
	void SetCooldown();
	void DecrementCooldown();

	const int CurrentBoost();

	void Die() override;

	char GetSymbol() const override;
	std::string GetName() const override;
	int GetColor() const override;
};

