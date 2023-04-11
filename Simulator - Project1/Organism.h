#pragma once
#include <memory>

// forward declaration to avoid circular dependencies
class World;

struct Position {
	int x;
	int y;
	bool operator==(const Position pos2) const {
		return (x == pos2.x && y == pos2.y);
	}
	bool InsideWorld(int size) {
		return (x < size && x >= 0 && y < size && y >= 0);
	}
};


class Organism {
protected:
	int strength;
	int initiative;
	int alive_time;
	bool alive;
	Position position;
	World& world;

public:
	const int& GetX() const;
	const int& GetY() const;
	const int& GetStrength() const;
	const int& GetInitiative() const;
	const int& GetAliveTime() const;
	const Position& GetPosition() const;
	const bool& IsAlive() const;

	void MoveX(int change);
	void MoveY(int change);

	void SetX(int new_x);
	void SetY(int new_y);
	void SetPosition(Position new_position);
	void SetStrength(int new_strength);
	void SetInitiative(int new_initiative);

	virtual void Action() = 0;
	virtual void Collision(std::unique_ptr<Organism>& collided) = 0;
	virtual void Draw() = 0;
	virtual void Die();

	Organism(World& ref_world);
	Organism(World& ref_world, int set_x, int set_y);
};

