#include "Libraries.h"
#include "World.h"

int main() {
	srand(time(NULL));
	int size_x = 25;
	int size_y = 25;
	World world(size_x, size_y);
	world.Start();
}