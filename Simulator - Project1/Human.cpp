#include "Human.h"
#include "Libraries.h"
#include "World.h"

void Human::Action() {
	UpdatePrevPosition();
	world.UpdateMapSlotsView();
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

void Human::Collision(std::unique_ptr<Organism>& collided) {
	// depends on his power and whether it's activated or not
	switch (power_activated) {
		case false:
			Animal::Collision(collided);
			break;
		case true:
			break;
	}
}

void Human::Draw() {
	if (!IsAlive()) {
		return;
	}
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch(HUMAN_SYMBOL);
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