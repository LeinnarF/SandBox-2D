#pragma once
#include "grid.h"

class Element
{
public:

	void Draw(Grid& grid, int y, int x);
	void Update(Grid& grid, int y, int x);
	void UpdateUp(Grid& grid, int y, int x);
	void drawCell(Grid& grid, int y, int x);
	bool isReactive(Grid& grid, int y, int x, int type);
	void Flammable(Grid& grid, int y, int x, int type);
	void TriggerExplosion(Grid& grid, int y, int x);

	void Sand(Grid& grid, int y, int x);
	void Water(Grid& grid, int y, int x);
	void Stone(Grid& grid, int y, int x);
	void Lava(Grid& grid, int y, int x);
	void Smoke(Grid& grid, int y, int x);
	void Cement(Grid& grid, int y, int x);
	void Acid(Grid& grid, int y, int x);
	void Oil(Grid& grid, int y, int x);
	void Fire(Grid& grid, int y, int x);
	void GunPowder(Grid& grid, int y, int x);
	void Wood(Grid& grid, int y, int x);
};