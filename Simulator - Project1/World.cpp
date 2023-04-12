#include "World.h"
#include "Libraries.h"

World::World(int set_size_x, int set_size_y) : size_x(set_size_x), size_y(set_size_y) {
	map_slots = new int* [size_x];
	for (int i = 0; i < size_x; i++) {
		map_slots[i] = new int[size_y];
		for (int j = 0; j < size_y; j++) {
			map_slots[i][j] = 0;
		}
	}
	AddNewOrganism(std::make_unique<Human>(*this));
	SetPlayer();
	for (int i=0; i < 4; i++) {
		AddNewOrganism(std::make_unique<Wolf>(*this));
	}
	for (int i = 0; i < 4; i++) {
		AddNewOrganism(std::make_unique<Sheep>(*this));
	}
}

void World::IncrementSlot(const Position& position) {
	map_slots[position.x][position.y]++;
}

void World::DecrementSlot(const Position& position) {
	map_slots[position.x][position.y]--;
}

const int& World::GetSizeX() const {
	return size_x;
}

const int& World::GetSizeY() const {
	return size_y;
}

void World::Start() {

	SortOrganisms();
	DrawFrame();
	DrawWorld();
	while (true) {
		if (player != nullptr) {
			player->TakeInput();
		}
		else {
			// confirm turn
			_getch();
		}
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

		if (!(GetAsyncKeyState(VK_SPACE) & 0x8000) && SLOW_MODE) {
			Sleep(250);
		}
		UpdateOneOrganism(organisms[i]);
	}

	DeleteDead();
	if (size != organisms.size()) {
		SortOrganisms();
	}
	UpdateMapSlotsView();
}

void World::DrawWorld() {
	if (!SLOW_MODE) {
		Clear();
	}

	// Draw Organisms
	for (auto& organism : organisms) {
		if (!organism->IsAlive()) continue;
		organism->Draw();
	}
	UpdateMapSlotsView();

	// Make cursor invisible
	std::cout << "\033[?25l";
}

// helping tool
void World::UpdateMapSlotsView() {
	for (int i = 0; i < size_y; i++) {
		MoveCursor(size_x * 2 + 10, 4 + i);
		for (int j = 0; j < size_x; j++) {
			std::cout << GetCountOnSlot({ j,i });
		}
	}
}

void World::MoveCursor(int x, int y) {
	std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

void World::Clear()
{
	// Draw top side of the frame 
	for (std::unique_ptr<Organism>& organism : organisms) {
		MoveCursor(organism->GetPrevPosition().x * X_SCALING + BOARD_POS_X + X_FRAME, organism->GetPrevPosition().y + BOARD_POS_Y + Y_FRAME);
		_putch(' ');
	}
}

void World::DrawFrame() {
	int size_x = GetSizeX();
	int size_y = GetSizeY();
	Clear();
	MoveCursor(BOARD_POS_X, BOARD_POS_Y);

	// Draw top side of the frame 
	for (int i = 1; i <= size_x + X_FRAME; i++) {
		_putch('#');
		_putch(' ');
	}

	// Draw left and right side of the frame
	for (int i = 1; i < size_y + 2 * Y_FRAME; i++) {
		MoveCursor(BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
		MoveCursor(size_x * X_SCALING + X_FRAME + BOARD_POS_X, i + BOARD_POS_Y);
		_putch('#');
	}

	// Draw bottom side of the frame
	MoveCursor(BOARD_POS_X, size_y + Y_FRAME + BOARD_POS_Y);
	for (int i = 1; i <= size_x + X_FRAME; i++) {
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
		if (current->GetPosition() == organism->GetPosition() && &(*current) != &(*organism) && organism->IsAlive()) {
			return organism;
		}
	}
	std::unique_ptr<Organism> null(nullptr);
	return null;
}

void World::AddNewOrganism(std::unique_ptr<Organism>&& organism) {
	IncrementSlot(organism->GetPosition());
	organisms.emplace_back(std::move(organism));
}

bool World::IsEmpty(Position position) const {
	return !GetCountOnSlot(position);
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

int World::GetCountOnSlot(const Position& slot) const {
	return map_slots[slot.x][slot.y];
}

void World::UpdateOneOrganism(std::unique_ptr<Organism>& organism) {
	if (organism->GetPosition() == organism->GetPrevPosition()) {
		return;
	}
	MoveCursor(organism->GetPrevPosition().x * X_SCALING + BOARD_POS_X + X_FRAME, organism->GetPrevPosition().y + BOARD_POS_Y + Y_FRAME);
	_putch(' ');
	if (!organism->IsAlive()) {
		return;
	}
	organism->Draw();
	std::cout << "\033[?25l";
}

void World::UpdateOneOrganism(std::unique_ptr<Animal>& organism) {
	if (organism->GetPosition() == organism->GetPrevPosition() || !organism->IsAlive()) {
		return;
	}
	MoveCursor(organism->GetPrevPosition().x * X_SCALING + BOARD_POS_X + X_FRAME, organism->GetPrevPosition().y + BOARD_POS_Y + Y_FRAME);
	_putch(' ');
	organism->Draw();
	std::cout << "\033[?25l";
}

void World::SetPlayer() {
	for (auto& organism : organisms) {
		if (dynamic_cast<Human*>(organism.get())) {
			player = dynamic_cast<Human*>(organism.get());
			return;
		}
	}
	player = nullptr;
}

void World::AbortPlayer() {
	player = nullptr;
}