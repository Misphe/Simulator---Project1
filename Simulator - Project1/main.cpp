#include "Libraries.h"
#include "World.h"

int main() {
	srand(time(NULL));
	int size = 20;
	World world(size);
	world.Start();
}