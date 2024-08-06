#pragma once
#include "grid.h"

class Element
{
public:

	void Draw(Grid& grid, int y, int x);
	void Update(Grid& grid, int y, int x);
	void drawCell(Grid& grid, int y, int x);

	void Sand(Grid& grid, int y, int x);
	void Water(Grid& grid, int y, int x);
	void Stone(Grid& grid, int y, int x);
	void Lava(Grid& grid, int y, int x);
	void Smoke(Grid& grid, int y, int x);
};