#include "element.h"

void Element::Draw(Grid& grid, int y, int x)
{
	if (grid.checkCell(y, x, 1))
		drawCell(grid, y, x);
	else if (grid.checkCell(y, x, 2))
		drawCell(grid, y, x);
	else if (grid.checkCell(y, x, 3))
		drawCell(grid, y, x);
	else if (grid.checkCell(y, x, 4))
		drawCell(grid, y, x);
	else if (grid.checkCell(y, x, 5))
		drawCell(grid, y, x);
}

void Element::Update(Grid& grid, int y, int x)
{
	if (grid.checkCell(y, x, 1))
		Sand(grid, y, x);
	else if (grid.checkCell(y, x, 2))
		Water(grid, y, x);
	else if (grid.checkCell(y, x, 3))
		Stone(grid, y, x);
	else if (grid.checkCell(y, x, 4))
		Lava(grid, y, x);
}

void Element::UpdateUp(Grid& grid, int y, int x)
{
	if (grid.checkCell(y, x, 5))
		Smoke(grid, y, x);
}

void Element::drawCell(Grid& grid, int y, int x)
{
	DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), grid.getColor(y, x));
}

void Element::Sand(Grid& grid, int y, int x)
{
	int direction = GetRandomValue(0, 1) * 2 - 1;

	//down
	if (grid.isEmpty(y + 1, x))
		grid.moveCell(y, x, y + 1, x);

	// left or right
	else if (grid.isEmpty(y + 1, x - direction))
		grid.moveCell(y, x, y + 1, x - direction);

	// interaction with water
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, 2))
		grid.moveCell(y, x, y + 1, x, 2, grid.getColor(y + 1, x));

	else if (grid.isWithinBounds(y + 1, x + direction) && grid.checkCell(y + 1, x + direction, 2))
		grid.moveCell(y, x, y + 1, x + direction, 2, grid.getColor(y + 1, x + direction));
}

void Element::Water(Grid& grid, int y, int x)
{
	int dispersionRate = GetRandomValue(4, 10);
	grid.moveLiquid(y, x, dispersionRate);
}

void Element::Stone(Grid& grid, int y, int x)
{
	if (grid.isWithinBounds(y, x) && grid.isEmpty(y, x))
		grid.setValue(x, y, 3);
}

void Element::Lava(Grid& grid, int y, int x)
{
	grid.moveLiquid(y, x, 1);
}

void Element::Smoke(Grid& grid, int y, int x)
{
	int direction = GetRandomValue(0, 1) * 2 - 1;

	// despawn smoke
	if (GetRandomValue(0, 100) == 50)
		grid.setValue(x, y, 0);

	// up
	if (grid.isEmpty(y - 1, x))
		grid.moveCell(y, x, y - 1, x);

	// left or right
	else if (grid.isEmpty(y - 1, x - direction))
		grid.moveCell(y, x, y - 1, x - direction);
}
