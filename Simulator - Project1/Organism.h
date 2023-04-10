#pragma once
#include <memory>

// forward declaration to avoid circular dependencies
class World;

struct Position {
	int x;
	int y;
};


class Organism {
protected:
	int strength;
	int initiative;
	int alive_time;
	Position position;
	World& world;

public:
	const int& GetX() const;
	const int& GetY() const;
	const int& GetStrength() const;
	const int& GetInitiative() const;
	const int& GetAliveTime() const;

	void MoveX(int change);
	void MoveY(int change);

	void SetX(int new_x);
	void SetY(int new_y);
	void SetStrength(int new_strength);
	void SetInitiative(int new_initiative);

	virtual void Action() = 0;
	virtual void Collision(std::unique_ptr<Organism>& collided) = 0;
	virtual void Draw() = 0;

	Organism(World& ref_world);
	Organism(World& ref_world, int set_x, int set_y);

};

