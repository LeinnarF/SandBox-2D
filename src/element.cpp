#include "element.h"

void Element::Draw(Grid& grid, int y, int x, int offsety, int offsetx)
{
	if (grid.checkCell(y, x, 0))
		DrawRectangle(x * grid.getCellsize() + offsetx, y * grid.getCellsize() + offsety, grid.getCellsize(), grid.getCellsize(), WHITE);

	else if (grid.checkCell(y, x, 1))
		DrawRectangle(x * grid.getCellsize() + offsetx, y * grid.getCellsize() + offsety, grid.getCellsize(), grid.getCellsize(), BEIGE);

	else if (grid.checkCell(y, x, 2))
		DrawRectangle(x * grid.getCellsize() + offsetx, y * grid.getCellsize() + offsety, grid.getCellsize(), grid.getCellsize(), BLUE);

	else if (grid.checkCell(y, x, 3))
		DrawRectangle(x * grid.getCellsize() + offsetx, y * grid.getCellsize() + offsety, grid.getCellsize(), grid.getCellsize(), GRAY);

	else if (grid.checkCell(y, x, 4))
		DrawRectangle(x * grid.getCellsize() + offsetx, y * grid.getCellsize() + offsety, grid.getCellsize(), grid.getCellsize(), ORANGE);
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

void Element::Sand(Grid& grid, int y, int x)
{
	//down
	if (grid.isEmpty(y + 1, x))
		grid.moveCell(y, x, y + 1, x);

	// left
	else if (grid.isEmpty(y + 1, x - 1))
		grid.moveCell(y, x, y + 1, x - 1);

	//right
	else if (grid.isEmpty(y + 1, x + 1))
		grid.moveCell(y, x, y + 1, x + 1);

	// interaction with water
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, 2))
		grid.moveCell(y, x, y + 1, x, 2);

	else if (grid.isWithinBounds(y + 1, x - 1) && grid.checkCell(y + 1, x - 1, 2))
		grid.moveCell(y, x, y + 1, x - 1, 2);

	else if (grid.isWithinBounds(y + 1, x + 1) && grid.checkCell(y + 1, x + 1, 2))
		grid.moveCell(y, x, y + 1, x + 1, 2);
}

void Element::Water(Grid& grid, int y, int x)
{
	// down
	if (grid.isEmpty(y + 1, x))
		grid.moveCell(y, x, y + 1, x);

	// left
	else if (grid.isEmpty(y + 1, x - 1))
		grid.moveCell(y, x, y + 1, x - 1);

	// right
	else if (grid.isEmpty(y + 1, x + 1))
		grid.moveCell(y, x, y + 1, x + 1);

	else
	{
		int rand = GetRandomValue(0, 1);
		if (rand == 0)
		{
			if (grid.isEmpty(y, x - 1) && grid.isEmpty(y, x + 1))
			{
				grid.moveCell(y, x, y, x - 1);
				grid.moveCell(y, x, y, x + 1);
			}
		}
		else
		{
			if (grid.isEmpty(y, x + 1))
				grid.moveCell(y, x, y, x + 1);

			else if (grid.isEmpty(y, x - 1))
				grid.moveCell(y, x, y, x - 1);
		}
	}
}

void Element::Stone(Grid& grid, int y, int x)
{
	if (grid.isWithinBounds(y, x) && grid.isEmpty(y, x))
	{
		grid.setValue(x, y, 3);
	}
}

void Element::Lava(Grid& grid, int y, int x)
{
	// down
	if (grid.isEmpty(y + 1, x))
		grid.moveCell(y, x, y + 1, x);

	// left
	else if (grid.isEmpty(y + 1, x - 1))
		grid.moveCell(y, x, y + 1, x - 1);

	// right
	else if (grid.isEmpty(y + 1, x + 1))
		grid.moveCell(y, x, y + 1, x + 1);

	else
	{
		int rand = GetRandomValue(0, 1);
		if (rand == 0)
		{
			if (grid.isEmpty(y, x - 1) && grid.isEmpty(y, x + 1))
			{
				grid.moveCell(y, x, y, x - 1);
				grid.moveCell(y, x, y, x + 1);
			}
		}
		else
		{
			if (grid.isEmpty(y, x + 1))
				grid.moveCell(y, x, y, x + 1);

			else if (grid.isEmpty(y, x - 1))
				grid.moveCell(y, x, y, x - 1);
		}
	}
}