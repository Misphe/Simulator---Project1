#include "Libraries.h"
#include "World.h"

int main() {

	srand(time(NULL));

	int size_x = 20;
	int size_y = 20;
	do {
		std::cout << "Enter width and height: ";
		std::cin >> size_x >> size_y;
		system("cls");
	} while (size_x < 5 || size_y < 5);

	World world(size_x, size_y);
	world.Start();
}