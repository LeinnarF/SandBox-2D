#include "element.h"

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
		int rand = GetRandomValue(1, 2);
		if (rand == 2)
		{
			if (grid.isEmpty(y, x - 1))
				grid.moveCell(y, x, y, x - 1);

			else if (grid.isEmpty(y, x + 1))
				grid.moveCell(y, x, y, x + 1);
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
	if (grid.isEmpty(y + 1, x))
	{
		grid.moveCell(y, x, y + 1, x);
	}
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, 2))
		grid.moveCell(y, x, y + 1, x, 2);
}
