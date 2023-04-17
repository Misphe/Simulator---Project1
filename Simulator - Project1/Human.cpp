#include "Human.h"
#include "Libraries.h"
#include "World.h"

void Human::Action() {
	// unlinking ( see Animal::Action() )
	world.DeleteOrganismFromSlot(*this);
	UpdatePrevPosition();
	int boost = CurrentBoost();

	switch (move) {
		case UP_ARROW:
			MoveY(-1 - boost);
			break;

		case DOWN_ARROW:
			MoveY(1 + boost);
			break;

		case LEFT_ARROW:
			MoveX(-1 - boost);
			break;

		case RIGHT_ARROW:
			MoveX(1 + boost);
			break;
	};

	alive_time++;
	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
}

void Human::Collision() {

	// depends on his power and whether it's activated or not
	switch (power_activated) {
		case false:

			Animal::Collision();
			break;
		case true:

			Animal::Collision();
			break;
	}
	DecrementCooldown();
}

void Human::Draw() const {
	world.SetColor(SET_BG_GREEN);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

Human::Human(World& ref_world) : Animal(ref_world), power_activated(false) {
	SetStrength(HUMAN_STRENGTH);
	SetInitiative(HUMAN_INITIATIVE);
	cooldown = 0;
	move = '\0';
}

std::unique_ptr<Animal> Human::Breed() const {
	return std::make_unique<Human>(world);
}

int Human::DefenseResult(Organism& attacker) {
	return Animal::DefenseResult(attacker);
}

void Human::SetMove(int& input) {
	move = input;
}

void Human::FlickPowerState() {
	power_activated = !power_activated;
}

const char& Human::GetInput() const {
	return move;
}

const bool& Human::PowerActivated() const
{
	return power_activated;
}

const int& Human::GetCooldown() {
	return cooldown;
}

void Human::SetCooldown() {
	cooldown = MAX_COOLDOWN;
}

void Human::DecrementCooldown() {
	if (cooldown > 0) {
		cooldown--;
	}
	if (cooldown == END_OF_POWER) {
		FlickPowerState();
	}
}

const int Human::CurrentBoost() {
	if (!PowerActivated()) return 0;

	if (GetCooldown() > POWER_WORSE_STATE) {
		return 1;
	}
	else if (GetCooldown() > END_OF_POWER) return rand() % 2;
	else return 0;
}

void Human::TakeInput() {
	bool success = false;
	while (!success) {
		int input = _getch();
		switch (input) {
			case ARROW_CLICK:
				input = _getch();
				SetMove(input);
				success = true;
				break;
			case SUPERPOWER:
				if (!PowerActivated()) {
					FlickPowerState();
				}
				break;
		};
		
	}
}

void Human::Die() {
	world.AbortPlayer();
	Animal::Die();
}

char Human::GetSymbol() const {
	return HUMAN_SYMBOL;
}

std::string Human::GetName() const {
	return "Human";
}

int Human::GetColor() const {
	return SET_BG_GREEN;
}
