#include "Human.h"
#include "Libraries.h"
#include "World.h"

void Human::Action() {
	bool success = false;
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
}

// TODO
void Human::Collision() {
	// depends on his power and whether it's activated or not
}

void Human::Draw() {
	int x = (GetX() * 2) + 1;
	int y = GetY() + 1;
	World::MoveCursor(x, y);
	_putch('H');
}

Human::Human(World& ref_world) : Animal(ref_world) {
	SetStrength(5);
	SetInitiative(4);
}

