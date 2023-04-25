#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Libraries.h"
#include "Organism.h"
#include "Human.h"
#include "Sheep.h"
#include "Wolf.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "WolfBerries.h"
#include "PineBorscht.h"
#include <windows.h>

// forward declaration to avoid circular dependencies
class Organism;

class World {
private:
	int size_x;
	int size_y;
	std::vector<std::unique_ptr<Organism>> organisms;
	int** map_slots;
	Organism*** organisms_slots;
	Human* player;

	std::string logs[LOG_LENGTH];
	HANDLE console;

	void SortOrganisms();

	void ExecuteTurn();
	void DrawFrame();

	void DeleteDead();

	int SetInput();
	void SetPlayer();
	void SetSize(int x, int y);

	void Reset();
	void SaveWorldState();
	void LoadWorld();

public:
	void DrawWorld();
	void DrawLegend();
	void DrawLogs();
	void Start();
	static void MoveCursor(int x, int y);

	void AddNewOrganism(std::unique_ptr<Organism>&& organism);
	void AbortPlayer();

	const int& GetSizeX() const;
	const int& GetSizeY() const;

	World(int set_size_x, int set_size_y);

	int GetCountOnSlot(const Position& slot) const;
	void IncrementSlot(const Position& position);
	void DecrementSlot(const Position& position);
	bool IsEmpty(Position position) const;
	bool IsOrganismAt(Position position) const;
	Organism* CheckForCollision(const Organism& current);

	void UpdateMapSlotsView();

	Organism* GetOrganismAtPos(Position spot);

	void SetOrganismToSlot(Organism& organism);
	void DeleteOrganismFromSlot(Organism& organism);
	void UpdateAnimalSlot(Animal& organism);
	void SetColor(const int& color);

	void PushNewLog(std::string&& new_log);
	std::string CreateLog(Organism& attacker, Organism& defender, int message);
	std::string CreateBreedLog(Organism& new_organism);
	void SetLog(int i, std::string&& set_log);

	std::unique_ptr<Organism> CreateOrganismFromFile(char symbol, int x, int y);

	~World();
};

