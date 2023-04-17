#pragma once
#include <memory>
#include <string>

// forward declaration to avoid circular dependencies
class World;

struct Position {
	int x;
	int y;
	bool operator==(const Position pos2) const {
		return (x == pos2.x && y == pos2.y);
	}
	bool operator!=(const Position pos2) const {
		return !(x == pos2.x && y == pos2.y);
	}
	bool InsideWorld(int size_x, int size_y) const {
		return (x < size_x && x >= 0 && y < size_y && y >= 0);
	}
};


class Organism {
protected:
	int strength;
	int initiative;
	int alive_time;
	bool alive;
	Position position;
	//Position prev_position;
	World& world;

public:
	const int& GetX() const;
	const int& GetY() const;
	const int& GetStrength() const;
	const int& GetInitiative() const;
	const int& GetAliveTime() const;
	const Position& GetPosition() const;
	const bool& IsAlive() const;
	//const Position& GetPrevPosition() const;
	virtual char GetSymbol() const = 0;
	virtual int GetColor() const = 0;
	virtual std::string GetName() const = 0;

	void MoveX(int change);
	void MoveY(int change);
	//void UpdatePrevPosition();

	void SetX(int new_x);
	void SetY(int new_y);
	void SetPosition(Position new_position);
	void SetStrength(int new_strength);
	void SetInitiative(int new_initiative);

	virtual void Action() = 0;
	virtual void Collision() = 0;
	virtual void Draw() const = 0;
	virtual void Die();
	virtual int DefenseResult(Organism& attacker) = 0;

	Organism(World& ref_world);
	Organism(World& ref_world, int set_x, int set_y);

	Position GetEmptyAdjacent();
};

