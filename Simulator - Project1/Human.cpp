#include "Human.h"
#include "Libraries.h"
#include "World.h"

void Human::Action() {
	// unlinking ( see Animal::Action() )
	world.DeleteOrganismFromSlot(*this);
	UpdatePrevPosition();

	switch (move) {
		case UP_ARROW:
			MoveY(-1);
			break;

		case DOWN_ARROW:
			MoveY(1);
			break;

		case LEFT_ARROW:
			MoveX(-1);
			break;

		case RIGHT_ARROW:
			MoveX(1);
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

			// nothing yet
			world.SetOrganismToSlot(*this);
			break;
	}
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
	SetStrength(5);
	SetInitiative(4);
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
