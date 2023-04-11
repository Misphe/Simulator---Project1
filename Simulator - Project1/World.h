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
	int** map_slots;

public:
	static void MoveCursor(int x, int y);
	void Clear();
	void DrawFrame();
	void ExecuteTurn();
	void DrawWorld();

	void SortOrganisms();

	void Start();
	std::unique_ptr<Organism>& CheckForCollision(std::unique_ptr<Organism>& current);

	void AddNewOrganism(std::unique_ptr<Organism>&& organism);
	void DeleteDead();

	const int& GetSize();

	World(int set_size);

	void IncrementSlot(const Position& position);
	void DecrementSlot(const Position& position);
	bool IsEmpty(Position position);


};

