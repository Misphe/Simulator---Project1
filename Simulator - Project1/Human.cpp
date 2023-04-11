#include "Human.h"
#include "Libraries.h"
#include "World.h"

void Human::Action() {
	bool success = false;
	UpdatePrevPosition();
	world.DrawWorld();

	while (!success) {
		int move = _getch();
		if (move == ARROW_CLICK) {
			move = _getch();
			success = true;
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
		}
	}
	alive_time++;
	world.DecrementSlot(GetPrevPosition());
	world.IncrementSlot(GetPosition());
}

// TODO
void Human::Collision(std::unique_ptr<Organism>& collided) {
	// depends on his power and whether it's activated or not

	if (AttackerWins(collided)) {
		collided->Die();
	}
	else {
		this->Die();
	}
}

void Human::Draw() {
	int x = (GetX() * X_SCALING) + 2;
	int y = GetY() + 1;
	World::MoveCursor(x + BOARD_POS_X, y + BOARD_POS_Y);
	_putch('H');
}

Human::Human(World& ref_world) : Animal(ref_world) {
	SetStrength(5);
	SetInitiative(4);
}

std::unique_ptr<Animal> Human::Breed() const {
	return std::make_unique<Human>(world);
}

