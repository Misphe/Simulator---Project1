#pragma once

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
	Position position;
	World& world;

	void MoveX(int change);
	void MoveY(int change);

public:
	const int& GetX() const;
	const int& GetY() const;
	const int& GetStrength() const;
	const int& GetInitiative() const;

	void SetX(int new_x);
	void SetY(int new_y);
	void SetStrength(int new_strength);
	void SetInitiative(int new_initiative);

	virtual void Action() = 0;
	virtual void Collision() = 0;
	virtual void Draw() = 0;

	Organism(World& ref_world);
	Organism(World& ref_world, int set_x, int set_y);

};

