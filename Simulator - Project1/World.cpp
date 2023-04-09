#include "World.h"
#include <conio.h>
#include <windows.h>

World::World(int set_size) : size(set_size) {}

const int& World::GetSize() {
	return size;
}

void World::Start() {
	organisms.emplace_back(new Human(*this));
	organisms.emplace_back(new Sheep(*this));
	organisms.emplace_back(new Wolf(*this));
	

	while (true) {
		DrawWorld();
		ExecuteTurn();
	}
}

void World::ExecuteTurn() {
	for (auto& organism : organisms) {
		organism->Action();
	}
}

void World::DrawWorld() {
	int size = GetSize();
	Clear();
	MoveCursor(1, 1);

	// Draw top side of the frame 
	for (int i = 1; i <= size + 2; i++) {
		_putch('#');
		_putch(' ');
	}

	// Draw left and right side of the frame
	for (int i = 2; i < size + 2; i++) {
		MoveCursor(0, i);
		_putch('#');
		MoveCursor(size * 2 + 3, i);
		_putch('#');
	}

	// Draw bottom side of the frame
	MoveCursor(1, size + 2);
	for (int i = 1; i <= size + 2; i++) {
		_putch('#');
		_putch(' ');
	}

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


// Clears screen faster than system("cls")
void World::Clear()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD home = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, ' ', dwConSize, home, &dwCharsWritten);
	SetConsoleCursorPosition(hConsole, home);
}