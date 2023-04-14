#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Organism.h"
#include "Human.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"

// forward declaration to avoid circular dependencies
class Organism;

class World {
private:
	const int size_x;
	const int size_y;
	std::vector<std::unique_ptr<Organism>> organisms;
	int** map_slots;
	Organism*** organisms_slots;
	Human* player;

	void SortOrganisms();
	Organism* CheckForCollision(std::unique_ptr<Organism>& current);

	void ExecuteTurn();
	void Clear();
	void DrawFrame();

public:
	void DrawWorld();
	void Start();
	static void MoveCursor(int x, int y);

	void AddNewOrganism(std::unique_ptr<Organism>&& organism);
	void DeleteDead();

	const int& GetSizeX() const;
	const int& GetSizeY() const;

	void SetPlayer();
	void AbortPlayer();
	World(int set_size_x, int set_size_y);

	int GetCountOnSlot(const Position& slot) const;
	void IncrementSlot(const Position& position);
	void DecrementSlot(const Position& position);
	bool IsEmpty(Position position) const;
	bool IsOrganismAt(Position position) const;

	void UpdateOneOrganism(std::unique_ptr<Organism>& current);
	void UpdateOneOrganism(std::unique_ptr<Animal>& current);
	void UpdateOneOrganism(Organism& current);
	void UpdateMapSlotsView();

	const Organism* GetOrganismAtPos(Position spot);

	void SetOrganismToSlot(Organism& organism);
	void DeleteOrganismFromSlot(Organism& organism);
	void UpdateOrganismSlot(Organism& organism);
};

