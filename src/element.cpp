#include "element.h"

enum Type {
	empty, sand, water, stone, lava, smoke, cement, acid, oil, fire, gunpowder, endType
};

void Element::Draw(Grid& grid, int y, int x)
{
	for (int type = sand; type < endType; type++)
	{
		if (grid.checkCell(y, x, static_cast<Type>(type)))
		{
			drawCell(grid, y, x);
			break;
		}
	}
}

void Element::Update(Grid& grid, int y, int x)
{
	Type cellType = static_cast<Type>(grid.getValue(x, y));
	switch (cellType)
	{
	case sand: Sand(grid, y, x); break;
	case water: Water(grid, y, x); break;
	case stone: Stone(grid, y, x); break;
	case lava: Lava(grid, y, x); break;
	case cement:Cement(grid, y, x); break;
	case acid: Acid(grid, y, x); break;
	case oil: Oil(grid, y, x); break;
	case gunpowder: GunPowder(grid, y, x); break;
	default: break;
	}
}

void Element::UpdateUp(Grid& grid, int y, int x)
{
	Type cellType = static_cast<Type>(grid.getValue(x, y));
	switch (cellType)
	{
	case smoke: Smoke(grid, y, x); break;
	case fire: Fire(grid, y, x); break;
	default: break;
	}
}

void Element::drawCell(Grid& grid, int y, int x)
{
	DrawRectangle(x * grid.getCellsize(), y * grid.getCellsize(), grid.getCellsize(), grid.getCellsize(), grid.getColor(y, x));
}

bool Element::isReactive(Grid& grid, int y, int x, int type)
{
	return grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, type) || grid.checkCell(y - 1, x, type) || grid.checkCell(y, x + 1, type) || grid.checkCell(y, x - 1, type);
}

void Element::Flammable(Grid& grid, int y, int x, int type)
{
	for (int dy = -1; dy <= 1; ++dy)
	{
		for (int dx = -1; dx <= 1; ++dx)
		{
			if (grid.isWithinBounds(y + dy, x + dx) && grid.checkCell(y + dy, x + dx, type))
			{
				grid.setValue(x + dx, y + dy, fire);
				grid.getColorManager().elementColor(y + dy, x + dx, fire);
			}
		}
	}
}

void Element::TriggerExplosion(Grid& grid, int y, int x)
{
	int explosionRadius = 20; // Adjust the explosion radius as needed
	int radiusSquared = explosionRadius * explosionRadius;

	for (int offsetY = -explosionRadius; offsetY <= explosionRadius; ++offsetY)
	{
		for (int offsetX = -explosionRadius; offsetX <= explosionRadius; ++offsetX)
		{
			int newY = y + offsetY;
			int newX = x + offsetX;
			int distanceSquared = offsetY * offsetY + offsetX * offsetX;

			if (distanceSquared <= radiusSquared && grid.isWithinBounds(newY, newX))
			{
				if (grid.checkCell(newY, newX, empty) || grid.checkCell(newY, newX, gunpowder))
				{
					grid.setValue(newX, newY, fire);
					grid.getColorManager().elementColor(newY, newX, fire);
				}
				else
				{
					grid.setValue(newX, newY, smoke);
					grid.getColorManager().elementColor(newY, newX, smoke);
				}
			}
		}
	}
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
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, water))
		grid.moveCell(y, x, y + 1, x, water, grid.getColor(y + 1, x));

	else if (grid.isWithinBounds(y + 1, x + direction) && grid.checkCell(y + 1, x + direction, water))
		grid.moveCell(y, x, y + 1, x + direction, water, grid.getColor(y + 1, x + direction));

	// sink in oil
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, oil))
		grid.moveCell(y, x, y + 1, x, oil, grid.getColor(y + 1, x));

	else if (grid.isWithinBounds(y + 1, x + direction) && grid.checkCell(y + 1, x + direction, oil))
		grid.moveCell(y, x, y + 1, x + direction, oil, grid.getColor(y + 1, x + direction));

	// interaction with lava
	if (isReactive(grid, y, x, lava))
	{
		if (GetRandomValue(0, 7) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
	// interaction with Acid
	if (isReactive(grid, y, x, acid))
	{
		if (GetRandomValue(0, 1) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
}

void Element::Water(Grid& grid, int y, int x)
{
	int dispersionRate = GetRandomValue(4, 10);
	grid.moveLiquid(y, x, dispersionRate);
	// interaction with lava
	if (isReactive(grid, y, x, lava))
	{
		if (GetRandomValue(0, 5) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
	// adding acid
	if (isReactive(grid, y, x, acid))
	{
		if (GetRandomValue(0, 10) == 1)
		{
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
	// oil
	int direction = GetRandomValue(0, 1) * 2 - 1;
	if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, oil))
		grid.moveCell(y, x, y + 1, x, oil, grid.getColor(y + 1, x));

	else if (grid.isWithinBounds(y + 1, x + direction) && grid.checkCell(y + 1, x + direction, oil))
		grid.moveCell(y, x, y + 1, x + direction, oil, grid.getColor(y + 1, x + direction));
}

void Element::Stone(Grid& grid, int y, int x)
{
	if (grid.isWithinBounds(y, x) && grid.isEmpty(y, x))
		grid.setValue(x, y, stone);

	// interaction with lava
	if (isReactive(grid, y, x, lava))
	{
		if (GetRandomValue(0, 10000) == 1) //slow decay
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
	// interaction with acid
	if (isReactive(grid, y, x, acid))
	{
		if (GetRandomValue(0, 10) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}
}

void Element::Lava(Grid& grid, int y, int x)
{
	grid.moveLiquid(y, x, 1);
	if (GetRandomValue(0, 6000) == 0)
	{
		grid.setValue(x, y, smoke);
		grid.getColorManager().elementColor(y, x, smoke);
	}
	// interaction with water
	if (isReactive(grid, y, x, water))
	{
		if (GetRandomValue(0, 2) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
		}
	}

	Flammable(grid, y, x, oil);
	Flammable(grid, y, x, gunpowder);

}

void Element::Smoke(Grid& grid, int y, int x)
{
	int direction = GetRandomValue(0, 1) * 2 - 1;

	// despawn smoke
	if (GetRandomValue(0, 50) == 50)
		grid.setValue(x, y, empty);

	// up
	if (grid.isEmpty(y - 1, x))
		grid.moveCell(y, x, y - 1, x);

	// left or right
	else if (grid.isEmpty(y - 1, x - direction))
		grid.moveCell(y, x, y - 1, x - direction);

	// if in prescence of liquid
	if (isReactive(grid, y, x, water))
		grid.removeCell(y, x);
	else if (isReactive(grid, y, x, lava))
		grid.removeCell(y, x);
	else if (isReactive(grid, y, x, acid))
		grid.removeCell(y, x);
}

void Element::Cement(Grid& grid, int y, int x)
{
	grid.moveLiquid(y, x, 1);
	if (GetRandomValue(0, 300) == 0)
	{
		// turns to stone
		grid.setValue(x, y, stone);
		grid.getColorManager().elementColor(y, x, stone);
	}
}

void Element::Acid(Grid& grid, int y, int x)
{
	grid.moveLiquid(y, x, 2);
	if (GetRandomValue(0, 100) == 0) //life span
	{
		grid.setValue(x, y, smoke);
		grid.getColorManager().elementColor(y, x, smoke);
	}
	//water + acid
	if (isReactive(grid, y, x, water))
	{
		if (GetRandomValue(0, 1) == 1)
		{
			grid.removeCell(y, x);
			grid.setValue(x, y - 1, fire);
			grid.setValue(x, y, smoke);
			grid.getColorManager().elementColor(y, x, smoke);
			grid.getColorManager().elementColor(y - 1, x, smoke);
		}
	}
}

void Element::Oil(Grid& grid, int y, int x)
{

	grid.moveLiquid(y, x, 1);

	if (isReactive(grid, y, x, fire))
	{
		grid.setValue(x, y, fire);
		grid.getColorManager().elementColor(y, x, fire);
	}
}

void Element::Fire(Grid& grid, int y, int x)
{
	int direction = GetRandomValue(0, 1) * 2 - 1;

	// despawn fire
	if (GetRandomValue(0, 30) == 0)
	{
		grid.setValue(x, y, empty);
		grid.setValue(x, 0, empty);
		grid.setValue(x, y, smoke);
		grid.getColorManager().elementColor(y, x, smoke);
	}

	// up
	if (grid.isEmpty(y - 1, x))
		grid.moveCell(y, x, y - 1, x);

	// left or right
	else if (grid.isEmpty(y - 1, x - direction))
		grid.moveCell(y, x, y - 1, x - direction);

	Flammable(grid, y, x, oil);
}

void Element::GunPowder(Grid& grid, int y, int x)
{
	int direction = GetRandomValue(0, 1) * 2 - 1;

	//down
	if (grid.isEmpty(y + 1, x))
		grid.moveCell(y, x, y + 1, x);

	// left or right
	else if (grid.isEmpty(y + 1, x - direction))
		grid.moveCell(y, x, y + 1, x - direction);


	// sink in oil
	else if (grid.isWithinBounds(y + 1, x) && grid.checkCell(y + 1, x, oil))
		grid.moveCell(y, x, y + 1, x, oil, grid.getColor(y + 1, x));

	else if (grid.isWithinBounds(y + 1, x + direction) && grid.checkCell(y + 1, x + direction, oil))
		grid.moveCell(y, x, y + 1, x + direction, oil, grid.getColor(y + 1, x + direction));

	if (isReactive(grid, y, x, fire))
	{
		TriggerExplosion(grid, y, x);
	}
}
