#include "Sheep.h"
#include "World.h"
#include "Libraries.h"


void Sheep::Draw() const  {
	world.SetColor(SET_BG_WHITE);
	if (DEBUG_MODE) {
		printf("%c", GetSymbol());
		printf(" ");
	}
	else {
		printf("  ");
	}
	RESET_COLOR;
}

Sheep::Sheep(World& ref_world) : Animal(ref_world) {
	SetStrength(SHEEP_STRENGTH);
	SetInitiative(SHEEP_INITIATIVE);
}

Sheep::Sheep(World& ref_world, int set_x, int set_y) : Animal(ref_world, set_x, set_y) {
	SetStrength(SHEEP_STRENGTH);
	SetInitiative(SHEEP_INITIATIVE);
}

char Sheep::GetSymbol() const {
	return SHEEP_SYMBOL;
}

std::string Sheep::GetName() const {
	return "Sheep";
}

int Sheep::GetColor() const {
	return SET_BG_WHITE;
}

std::unique_ptr<Animal> Sheep::Breed() const {
	return std::make_unique<Sheep>(world, GetX(), GetY());
}