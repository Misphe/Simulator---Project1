#include "World.h"
#include "Libraries.h"
#include <sstream>

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

void World::SetSize(int x, int y) {
	size_x = x;
	size_y = y;

	map_slots = new int*[size_x];
	organisms_slots = new Organism**[size_x];
	for (int i = 0; i < size_x; i++) {
		map_slots[i] = new int[size_y];
		organisms_slots[i] = new Organism*[size_y];
		for (int j = 0; j < size_y; j++) {
			map_slots[i][j] = 0;
			organisms_slots[i][j] = nullptr;
		}
	}
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

	// length of one row in console
	int row_length = X_SCALING * (GetSizeX() + X_FRAME);

	// length of one column in console
	int col_length = GetSizeY() + 2 * Y_FRAME;

	// creating buffer to store output
	CHAR_INFO* buffer = new CHAR_INFO[col_length * row_length];

	// set first row to blue color
	for (int i = 0; i < row_length; i++) {
		buffer[i].Char.AsciiChar = ' ';
		buffer[i].Attributes = SET_BG_BLUE;
	}

	// create map
	for (int row = 0; row < GetSizeY(); row++) {
		for (int col = 0; col < row_length; col+=2) {
			int index = row_length + row * row_length + col;

			// first column or alst column
			if (col == 0 || col == row_length - X_FRAME) {
				buffer[index].Char.AsciiChar = ' ';
				buffer[index].Attributes = SET_BG_BLUE;
				buffer[index + 1].Char.AsciiChar = ' ';
				buffer[index + 1].Attributes = SET_BG_BLUE;
			}

			else if (organisms_slots[(col - X_FRAME)/X_SCALING][row] != nullptr) {
				buffer[index].Char.AsciiChar = ' ';
				buffer[index].Attributes = organisms_slots[(col - X_FRAME) / X_SCALING][row]->GetColor();
				buffer[index + 1].Char.AsciiChar = ' ';
				buffer[index + 1].Attributes = organisms_slots[(col - X_FRAME) / X_SCALING][row]->GetColor();
			}
			else {
				buffer[index].Char.AsciiChar = ' ';
				buffer[index].Attributes = SET_BG_LIGHTYELLOW;
				buffer[index + 1].Char.AsciiChar = ' ';
				buffer[index + 1].Attributes = SET_BG_LIGHTYELLOW;
			}
		}
	}

	// last row filling with blue
	for (int i = 0; i < row_length; i++){
		int index = (col_length - 1) * row_length + i;
		buffer[index].Char.AsciiChar = ' ';
		buffer[index].Attributes = SET_BG_BLUE;
	}

	// output what we stored
	SMALL_RECT rect = { BOARD_POS_X, BOARD_POS_Y, BOARD_POS_X + (GetSizeX() * 2 + 4) - 1, BOARD_POS_Y + GetSizeY() + 2 - 1};
	WriteConsoleOutputA(console, buffer, { (short)(GetSizeX() * 2 + 4), (short)(GetSizeY() + 2)}, {0, 0}, &rect);

	delete[] buffer;

	if (SLOW_MODE) {
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
	}

	// logs
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

		switch (input) {
		case ESCAPE:
			success = true;
			continue;
			break;
		case SAVE:
			SaveWorldState();
			continue;
			break;
		case LOAD:
			LoadWorld();
			continue;
			break;
		};

		switch (player != nullptr) {
		case true:
			switch (input) {
			case ARROW_CLICK:
				input = _getch();
				player->SetMove(input);
				success = true;
				break;
			case SUPERPOWER:
				if (!player->PowerActivated() && player->GetCooldown() == 0) {
					player->FlickPowerState();
					player->SetCooldown();
				}
				break;
			};
			break;
		case false:
			switch (input) {
			case ARROW_CLICK:
				input = _getch();
				success = true;
				break;
			default:
				success = true;
				break;
			};
			break;
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

void World::SetLog(int i, std::string&& set_log) {
	logs[i] = std::move(set_log);
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

void World::Reset() {

	organisms.clear();

	for (int i = 0; i < size_x; i++) {
		delete[] organisms_slots[i];
		delete[] map_slots[i];

	}
	delete[] map_slots;
	delete[] organisms_slots;

	for (int i = 0; i < LOG_LENGTH; i++) {
		logs[i] = "";
	}

	SetSize(0, 0);
	AbortPlayer();
}

void World::SaveWorldState() {
	std::ofstream file("save.txt"); // create a new file called "output.txt"
	if (!file.is_open()) return;

	file << "size_x: " << GetSizeX() << "\n";
	file << "size_y: " << GetSizeY() << "\n";
	file << "organisms_size: " << organisms.size() << "\n";
	file << "player_alive: " << (player ? 1 : 0) << "\n";
	if (player) {
		file << "cooldown: " << player->GetCooldown() << "\n";
		file << "power: " << (int)player->PowerActivated() << "\n";
	}
	for (int i = 0; i < organisms.size(); i++) {
		file << organisms[i]->GetSymbol() << " ";
		if (dynamic_cast<Animal*>(organisms[i].get())) {
			file << "Animal ";
			file << dynamic_cast<Animal*>(organisms[i].get())->GetPrevPosition().x << " ";
			file << dynamic_cast<Animal*>(organisms[i].get())->GetPrevPosition().y << " ";
		}
		else {
			file << "Plant ";
		}
		file << organisms[i]->GetStrength() << " ";
		file << organisms[i]->GetInitiative() << " ";
		file << organisms[i]->GetAliveTime() << " ";
		file << organisms[i]->GetX() << " ";
		file << organisms[i]->GetY() << "\n";
	}

	for (int i = 0; i < LOG_LENGTH; i++) {
		if (logs[i].empty()) break;
		file << logs[i] << "\n";
	}
	file << '/';

	file.close();
}

void World::LoadWorld() {
	std::ifstream file("save.txt"); // open the file for reading
	if (!file.is_open()) return;

	Reset();

	int size_x, size_y, organisms_size, cooldown, power;
	bool player_alive = false;
	char symbol;
	std::string line, title, organism_type;

	file >> title >> size_x;
	file >> title >> size_y;
	file >> title >> organisms_size;
	file >> title >> player_alive;
	if (player_alive) {
		file >> title >> cooldown;
		file >> title >> power;
	}
	
	SetSize(size_x, size_y);
	organisms.reserve(organisms_size);

	int prev_x, prev_y, strength, initiative, alive_time, x, y;

	for (int i = 0; i < organisms_size; i++) {
		file >> symbol;
		file >> organism_type;
		if (organism_type == "Animal") {
			file >> prev_x >> prev_y;
		}

		file >> strength >> initiative >> alive_time >> x >> y;
		
		std::unique_ptr<Organism> organism = CreateOrganismFromFile(symbol, x, y);
		organism->SetStrength(strength);
		organism->SetAliveTime(alive_time);

		if (Animal* animal = dynamic_cast<Animal*>(organism.get())) {
			animal->SetPrevPosition(prev_x, prev_y);
		}
		
		AddNewOrganism(std::move(organism));
	}

	for (int i = 0; i < LOG_LENGTH; i++) {
		std::getline(file, line);
		if (line.empty()) {
			i--;
			continue;
		}
		if (line != "/") {
			SetLog(i, std::move(line));
		}
	}

	SetPlayer();
	if (player != nullptr) {
		player->SetCooldown(cooldown);
		player->SetPowerState(power);
	}
	DrawWorld();

	file.close();
}

std::unique_ptr<Organism> World::CreateOrganismFromFile(char symbol, int x, int y) {
	switch (symbol) {
	case HUMAN_SYMBOL:
		return std::make_unique<Human>(*this, x, y);
		break;
	case WOLF_SYMBOL:
		return std::make_unique<Wolf>(*this, x, y);
		break;
	case SHEEP_SYMBOL:
		return std::make_unique<Sheep>(*this, x, y);
		break;
	case FOX_SYMBOL:
		return std::make_unique<Fox>(*this, x, y);
		break;
	case ANTELOPE_SYMBOL:
		return std::make_unique<Antelope>(*this, x, y);
		break;
	case TURTLE_SYMBOL:
		return std::make_unique<Turtle>(*this, x, y);
		break;
	case GRASS_SYMBOL:
		return std::make_unique<Grass>(*this, x, y);
		break;
	case DANDELION_SYMBOL:
		return std::make_unique<Dandelion>(*this, x, y);
		break;
	case GUARANA_SYMBOL:
		return std::make_unique<Guarana>(*this, x, y);
		break;
	case WOLFBERRIES_SYMBOL:
		return std::make_unique<WolfBerries>(*this, x, y);
		break;
	case PINEBORSCHT_SYMBOL:
		return std::make_unique<PineBorscht>(*this, x, y);
		break;
	};
}