#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Organism.h"
#include "Human.h"
#include "Sheep.h"
#include "Wolf.h"

// forward declaration to avoid circular dependencies
class Organism;

class World {
private:
	const int size;
	std::vector<std::unique_ptr<Organism>> organisms;

	// add later
	void ExecuteTurn();
	void DrawWorld();

public:
	static void MoveCursor(int x, int y);
	static void Clear();

	void Start();

	const int& GetSize();

	World(int set_size);
};

