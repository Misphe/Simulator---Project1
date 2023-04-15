#include "World.h"
#include "Libraries.h"
#include <algorithm>

World::World(int set_size_x, int set_size_y) : size_x(set_size_x), size_y(set_size_y) {
	for (int i = 0; i < LOG_LENGTH; i++) {
		logs[i] = "";
	}
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	map_slots = new int* [size_x];
	organisms_slots = new Organism**[size_x];
	for (int i = 0; i < size_x; i++) {
		map_slots[i] = new int[size_y];
		organisms_slots[i] = new Organism*[size_y];
		for (int j = 0; j < size_y; j++) {
			map_slots[i][j] = 0;
			organisms_slots[i][j] = nullptr;
		}
	}
	AddNewOrganism(std::make_unique<Human>(*this));
	SetPlayer();
	for (int i = 0; i < WOLF_COUNT; i++) {
		AddNewOrganism(std::make_unique<Wolf>(*this));
	}
	for (int i = 0; i < SHEEP_COUNT; i++) {
		AddNewOrganism(std::make_unique<Sheep>(*this));
	}
	for (int i = 0; i < FOX_COUNT; i++) {
		AddNewOrganism(std::make_unique<Fox>(*this));
	}
	for (int i = 0; i < TURTLE_COUNT; i++) {
		AddNewOrganism(std::make_unique<Turtle>(*this));
	}
	for (int i = 0; i < ANTELOPE_COUNT; i++) {
		AddNewOrganism(std::make_unique<Antelope>(*this));
	}
	for (int i = 0; i < GRASS_COUNT; i++) {
		AddNewOrganism(std::make_unique<Grass>(*this));
	}
	for (int i = 0; i < DANDELION_COUNT; i++) {
		AddNewOrganism(std::make_unique<Dandelion>(*this));
	}
	for (int i = 0; i < GUARANA_COUNT; i++) {
		AddNewOrganism(std::make_unique<Guarana>(*this));
	}
	for (int i = 0; i < WOLFBERRIES_COUNT; i++) {
		AddNewOrganism(std::make_unique<WolfBerries>(*this));
	}
	for (int i = 0; i < PINEBORSCHT_COUNT; i++) {
		AddNewOrganism(std::make_unique<PineBorscht>(*this));
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
	DrawWorld();
	int input;
	while (true) {
		input = SetInput();
		switch (input) {
		case ESCAPE:
			return;
			break;
		}

		ExecuteTurn();
	}
}

void World::ExecuteTurn() {
	int size = organisms.size();
	for (int i = 0; i < size; i++) {
		if (!organisms[i]->IsAlive()) continue;

		organisms[i]->Action();
		organisms[i]->Collision();
		SetOrganismToSlot(*organisms[i].get());

	}

	UpdateMapSlotsView();
	DeleteDead();
	DrawWorld();
	SortOrganisms();
}

void World::DrawWorld() {
	if (!SLOW_MODE) {
		//Clear();
	}



	MoveCursor(BOARD_POS_X, BOARD_POS_Y);
	SetColor(SET_BG_LIGHTBLUE);
	for (int i = 1; i <= size_x + X_FRAME; i++) {
		printf("  ");
	}
	for (int i = 0; i < size_y; i++) {

		MoveCursor(BOARD_POS_X, BOARD_POS_Y + Y_FRAME + i);
		SetColor(SET_BG_LIGHTBLUE);
		printf("  ");
		for (int j = 0; j < size_x; j++) {
			if (organisms_slots[j][i] == nullptr) {
				SetColor(SET_BG_LIGHTYELLOW);
				printf("  ");
			}
			else {
				organisms_slots[j][i]->Draw();
			}
		}
		SetColor(SET_BG_LIGHTBLUE);
		printf("  ");
	}
	MoveCursor(BOARD_POS_X, size_y + Y_FRAME + BOARD_POS_Y);
	for (int i = 1; i <= size_x + X_FRAME; i++) {
		printf("  ");
	}
	//UpdateMapSlotsView();

	SetColor(SET_BG_GREEN);
	for (int i = 0; i < LOG_LENGTH; i++) {
		MoveCursor(LOG_X, LOG_Y + LOG_LENGTH - i);
		std::cout << logs[i];
		for (int j = 0; j < LOG_LINE_LENGTH - logs[i].length(); j++) {
			printf(" ");
		}
	}
	SetColor(SET_BG_LIGHTBLUE);



	// Make cursor invisible
	std::cout << "\033[?25l";
}

// helping tool
void World::UpdateMapSlotsView() {
	return;
	SET_BG_BLACK;
	for (int i = 0; i < size_y; i++) {
		MoveCursor(size_x * 2 + 10, 4 + i);
		for (int j = 0; j < size_x; j++) {
			std::cout << GetCountOnSlot({ j,i });
		}
	}
}

Organism* World::GetOrganismAtPos(Position spot) {
	return organisms_slots[spot.x][spot.y];
}

void World::SetOrganismToSlot(Organism& organism) {
	if (!organism.IsAlive()) {
		return;
	}
	organisms_slots[organism.GetX()][organism.GetY()] = &organism;
}

// PrevPos set to nullptr and updated current position
void World::UpdateAnimalSlot(Animal& organism) {
	organisms_slots[organism.GetPrevPosition().x][organism.GetPrevPosition().y] = nullptr;
	if (organism.IsAlive()) {
		organisms_slots[organism.GetX()][organism.GetY()] = &organism;
	}
}

void World::SetColor(const int& color) {
	SetConsoleTextAttribute(console, color);
}

void World::DeleteOrganismFromSlot(Organism& organism) {
	organisms_slots[organism.GetX()][organism.GetY()] = nullptr;
}

void World::MoveCursor(int x, int y) {
	std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

void World::SortOrganisms() {
	std::sort(organisms.begin(), organisms.end(), 
		[](const std::unique_ptr<Organism>& first, const std::unique_ptr<Organism>& second) -> bool {
			if (first->GetInitiative() != second->GetInitiative()) {
				return first->GetInitiative() > second->GetInitiative();
			}
			else {
				return first->GetAliveTime() > second->GetAliveTime();
			}
		});
}

Organism* World::CheckForCollision(const Organism& current) {
	return organisms_slots[current.GetX()][current.GetY()];
}

void World::AddNewOrganism(std::unique_ptr<Organism>&& organism) {
	IncrementSlot(organism->GetPosition());
	SetOrganismToSlot(*organism.get());
	int x = organisms_slots[organism->GetX()][organism->GetY()]->GetX();
	int y = organisms_slots[organism->GetX()][organism->GetY()]->GetY();
	organisms.emplace_back(std::move(organism));
}

bool World::IsEmpty(Position position) const {
	return !GetCountOnSlot(position);
}

bool World::IsOrganismAt(Position position) const {
	if (organisms_slots[position.x][position.y]) {
		return true;
	}
	return false;
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

int World::SetInput() {
	bool success = false;
	int input;
	while (!success) {
		input = _getch();
		switch (player != nullptr) {
		case true:
			switch (input) {
			case ARROW_CLICK:
				input = _getch();
				player->SetMove(input);
				success = true;
				break;
			case ESCAPE:
				success = true;
				break;
			case SUPERPOWER:
				if (!player->PowerActivated() && player->GetCooldown() == 0) {
					player->FlickPowerState();
					player->SetCooldown();
				}
				break;
			};
		case false:
			switch (input) {
			case ARROW_CLICK:
				input = _getch();
				success = true;
				break;
			case ESCAPE:
				success = true;
				break;
			};
		};
	}
	return input;
}

World::~World() {
	for (int i = 0; i < size_x; i++) {
		delete[] organisms_slots[i];
		delete[] map_slots[i];

	}
	delete[] map_slots;
	delete[] organisms_slots;
}

void World::PushNewLog(std::string&& new_log) {
	for (int i = LOG_LENGTH - 1; i >= 1; i--) {
		logs[i] = logs[i - 1];
	}
	logs[0] = std::move(new_log);
}

std::string World::CreateLog(Organism& attacker, Organism& defender, int message) {
	std::string attacker_info = attacker.GetName() + "(" + std::to_string(attacker.GetX()) + "," + std::to_string(attacker.GetY()) + ")";
	std::string defender_info = defender.GetName() + "(" + std::to_string(defender.GetX()) + "," + std::to_string(defender.GetY()) + ")";
	switch (message) {
	case ATTACKER_WINS:
		return attacker_info + " killed " + defender_info;
	case DEFENDER_WINS:
		return defender_info + " killed " + attacker_info;
	case DEFENDER_RUNS_AWAY:
		return defender_info + " ran away from " + attacker_info;
	case ATTACKER_RETREATS:
		return attacker_info + " stepped back from " + defender_info;
	case BOTH_DIED:
		return attacker_info + " and " + defender_info + "died";
	case ATTACKER_EATS:
		return attacker_info + " eats " + defender_info;
	};
}

std::string World::CreateBreedLog(Organism& new_organism) {
	return new_organism.GetName() + " appeared at (" + std::to_string(new_organism.GetX()) + "," + std::to_string(new_organism.GetY()) + ")";
}
