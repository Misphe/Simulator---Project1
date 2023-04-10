#include "Libraries.h"
#include "World.h"

int main() {
	srand(time(NULL));
	int size = 10;
	World world(size);
	world.Start();
}