#pragma once
#include "Animal.h"
class Human : public Animal {
private:
	char move;
	bool power_activated;
public:
	void Action() override;
	void Collision(std::unique_ptr<Organism>& collided) override;
	void Draw() override;
	std::unique_ptr<Animal> Breed() const override;

	bool Defended(Organism& attacker) override;

	Human(World& ref_world);
	void TakeInput();

	void SetMove(int& input);
	void FlickPowerState();

	const char& GetInput() const;
	const bool& PowerActivated() const;

	void Die() override;
};

