#include "Libraries.h"
#include "World.h"

int main() {
	srand(time(NULL));
	int size_x = 10;
	int size_y = 10;
	World world(size_x,size_y);
	world.Start();
}