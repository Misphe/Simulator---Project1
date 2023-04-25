#pragma once
#include "Animal.h"
class Human : public Animal {
private:
	char move;
	bool power_activated;
	int cooldown;
	
	void Action() override;
	void Collision() override;
	int DefenseResult(Organism& attacker) override;

	void TakeInput();
	void Die() override;
public:
	void Draw() const override;
	std::unique_ptr<Animal> Breed() const override;


	Human(World& ref_world);
	Human(World& ref_world, int x, int y);

	void SetMove(int& input);
	void FlickPowerState();

	const char& GetInput() const;
	const bool& PowerActivated() const;
	const int& GetCooldown();
	void SetCooldown();
	void SetCooldown(int set_cooldown);
	void SetPowerState(bool state);
	void DecrementCooldown();

	const int CurrentBoost();


	char GetSymbol() const override;
	std::string GetName() const override;
	int GetColor() const override;
};

