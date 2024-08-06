#include "element.h"

Color sand{ 254, 237, 192, 255 };
Color water{ 117, 149, 224, 255 };
Color stone{ 200, 200, 200, 255 };
Color lava{ 231, 111, 81, 255 };

void Element::Draw(Grid& grid, int y, int x)
{
	if (grid.checkCell(y, x, 1))
		DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), sand);

	else if (grid.checkCell(y, x, 2))
		DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), water);

	else if (grid.checkCell(y, x, 3))
		DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), stone);

	else if (grid.checkCell(y, x, 4))
		DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), lava);
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
	grid.moveLiquid(y, x, 4);
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
