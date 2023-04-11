#include "World.h"
#include "Libraries.h"

World::World(int set_size) : size(set_size) {
	map_slots = new int* [size];
	for (int i = 0; i < size; i++) {
		map_slots[i] = new int[size];
		for (int j = 0; j < size; j++) {
			map_slots[i][j] = 0;
		}
	}
}

void World::IncrementSlot(const Position& position) {
	map_slots[position.y][position.x]++;
}

void World::DecrementSlot(const Position& position) {
	map_slots[position.y][position.x]--;
}

const int& World::GetSize() {
	return size;
}

void World::Start() {
	AddNewOrganism(std::make_unique<Human>(*this));
	AddNewOrganism(std::make_unique<Sheep>(*this));
	AddNewOrganism(std::make_unique<Sheep>(*this));
	AddNewOrganism(std::make_unique<Sheep>(*this));
	AddNewOrganism(std::make_unique<Sheep>(*this));

	SortOrganisms();

	DrawFrame();
	while (true) {
		ExecuteTurn();
	}
}

void World::ExecuteTurn() {

	int size = organisms.size();
	for (int i = 0; i < size; i++) {
		if (!organisms[i]->IsAlive()) continue;

		organisms[i]->Action();
		std::unique_ptr<Organism>& collided_organism = CheckForCollision(organisms[i]);
		if (collided_organism.get() != nullptr) {
			organisms[i]->Collision(collided_organism);
		}
	}

	DeleteDead();
	SortOrganisms();
	DrawWorld();
}

void World::DrawWorld() {
	Clear();

	// Draw Organisms
	for (auto& organism : organisms) {
		if (!organism->IsAlive()) continue;
		organism->Draw();
	}

	// helping tool
	for (int i = 0; i < size; i++) {
		MoveCursor(40, 4 + i);
		for (int j = 0; j < size; j++) {
			std::cout << map_slots[i][j];
		}
	}

	// Make cursor invisible
	std::cout << "\033[?25l";
}

void World::MoveCursor(int x, int y) {
	std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

void World::Clear()
{
	int size = GetSize();

	// Draw top side of the frame 
	for (int i = 0; i < size; i++) {
		MoveCursor(BOARD_POS_X + 1, i + BOARD_POS_Y + 1);
		for (int j = 0; j < size; j++) {
			_putch(' ');
			_putch(' ');
		}
	}
}

void World::DrawFrame() {
	int size = GetSize();
	Clear();
	MoveCursor(BOARD_POS_X, BOARD_POS_Y);

	// Draw top side of the frame 
	for (int i = 1; i <= size + X_FRAME; i++) {
		_putch('#');
		_putch(' ');
	}

	// Draw left and right side of the frame
	for (int i = 1; i < size + 2 * Y_FRAME; i++) {
		MoveCursor(BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
		MoveCursor(size * X_SCALING + X_FRAME + BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
	}

	// Draw bottom side of the frame
	MoveCursor(BOARD_POS_X, size + Y_FRAME + BOARD_POS_Y);
	for (int i = 1; i <= size + X_FRAME; i++) {
		_putch('#');
		_putch(' ');
	}
}

void World::SortOrganisms() {
	std::sort(organisms.begin(), organisms.end(), 
		[](const auto& first, const auto& second) {
			if (first->GetInitiative() != second->GetInitiative()) {
				return first->GetInitiative() > second->GetInitiative();
			}
			else {
				return first->GetAliveTime() > second->GetAliveTime();
			}
		});
}

std::unique_ptr<Organism>& World::CheckForCollision(std::unique_ptr<Organism>& current) {
	for (auto& organism : organisms) {
		if (current->GetX() == organism->GetX() && current->GetY() == organism->GetY() && &(*current) != &(*organism)) {
			return organism;
		}
	}
	static std::unique_ptr<Organism> null(nullptr);
	return null;
}

void World::AddNewOrganism(std::unique_ptr<Organism>&& organism) {
	IncrementSlot(organism->GetPosition());
	organisms.emplace_back(std::move(organism));
}

bool World::IsEmpty(Position position) {
	return !map_slots[position.y][position.x];
}
	
void World::DeleteDead() {
	for (auto organism = organisms.begin(); organism != organisms.end(); ) {
		if (!(*organism)->IsAlive()) {
			organism = organisms.erase(organism);
		}
		else {
			organism++;
		}
	}
}