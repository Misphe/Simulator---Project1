#include "Libraries.h"
#include "World.h"

int main() {
	SetConsoleTitleW(L"Adrian Belczak 193362 \U0001F600");

	srand(time(NULL));

	int size_x;
	int size_y;
	bool wrong_input = false;
	do {
		if (wrong_input) std::cout << "Map is too small." << std::endl;
		std::cout << "Enter width and height: ";
		std::cin >> size_x >> size_y;
		system("cls");
	} while (wrong_input = (size_y * size_x < ORGANISMS_COUNT || size_y * size_x < MIN_MAP_SIZE));

	World world(size_x, size_y);
	world.Start();
}