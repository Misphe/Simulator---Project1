#include "World.h"
#include "Libraries.h"

World::World(int set_size) : size(set_size) {}

const int& World::GetSize() {
	return size;
}

void World::Start() {
	organisms.emplace_back(new Human(*this));
	organisms.emplace_back(new Wolf(*this));
	organisms.emplace_back(new Wolf(*this));
	organisms.emplace_back(new Wolf(*this));
	organisms.emplace_back(new Wolf(*this));

	SortOrganisms();

	DrawFrame();
	while (true) {
		if (organisms.size() >= GetSize() * GetSize()) {
			//exit(0);
		}
		ExecuteTurn();
	}
}

void World::ExecuteTurn() {
	int size = organisms.size();
	for (int i = 0; i < size; i++) {
		organisms[i]->Action();
		std::unique_ptr<Organism>& collided_organism = CheckForCollision(organisms[i]);
		if (collided_organism.get() != nullptr) {
			organisms[i]->Collision(collided_organism);
		}
	}
	SortOrganisms();
}

void World::DrawWorld() {
	Clear();

	// Draw Organisms
	for (auto& organism : organisms) {
		organism->Draw();
	}

	// Make cursor invisible
	std::cout << "\033[?25l";
}

void World::MoveCursor(int x, int y) {
	std::cout << "\033[" << y << ";" << x << "H";
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
	for (int i = 1; i <= size + 2; i++) {
		_putch('#');
		_putch(' ');
	}

	// Draw left and right side of the frame
	for (int i = 1; i < size + 2; i++) {
		MoveCursor(BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
		MoveCursor(size * X_SCALING + 2 + BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
	}

	// Draw bottom side of the frame
	MoveCursor(BOARD_POS_X, size + 1 + BOARD_POS_Y);
	for (int i = 1; i <= size + 2; i++) {
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
	organisms.emplace_back(std::move(organism));
}