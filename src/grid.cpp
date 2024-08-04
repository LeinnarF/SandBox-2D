#include "grid.h"
#include "element.h"

Grid::Grid(int width, int height, int cellsize) :
	m_x(width / cellsize),
	m_y(height / cellsize),
	m_cellsize(cellsize),
	m_cells(m_y, std::vector<int>(m_x, 0)),
	m_element()
{}

void Grid::Draw(int offsetY, int offsetX)
{
	for (int y = 0; y < m_y; y++)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Draw(*this, y, x, offsetY, offsetX);
		}
	}
}

void Grid::Update()
{
	for (int y = m_y - 2; y >= 0; y--)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Update(*this, y, x);
		}
	}
}

void Grid::setValue(int x, int y, int value)
{
	if (isWithinBounds(y, x))
		m_cells[y][x] = value;
}

bool Grid::isWithinBounds(int y, int x)
{
	return x >= 0 && x < m_x && y >= 0 && y < m_y;
}

bool Grid::isEmpty(int y, int x)
{
	return isWithinBounds(y, x) && m_cells[y][x] == 0;
}

bool Grid::checkCell(int y, int x, int target)
{
	return m_cells[y][x] == target;
}

void Grid::moveCell(int y1, int x1, int y2, int x2)
{
	m_cells[y2][x2] = m_cells[y1][x1];
	m_cells[y1][x1] = 0;
}

void Grid::moveCell(int y1, int x1, int y2, int x2, int swap)
{
	m_cells[y2][x2] = m_cells[y1][x1];
	m_cells[y1][x1] = swap;
}

void Grid::addBlock(int mouseX, int mouseY, int value, int scale, int offset)
{
	int startx = (mouseX - (offset / 2)) / m_cellsize;
	int starty = (mouseY - (offset / 2)) / m_cellsize;

	for (int y = starty; y < starty + scale; y++)
	{
		for (int x = startx; x < startx + scale; x++)
		{
			if (isWithinBounds(y, x) && isEmpty(y, x))
				setValue(x, y, value);
		}
	}
}

void Grid::erase(int mouseX, int mouseY, int offset)
{
	int x = (mouseX - (offset / 2)) / m_cellsize;
	int y = (mouseY - (offset / 2)) / m_cellsize;
	if (isWithinBounds(y, x) && !isEmpty(y, x))
		setValue(x, y, 0);
}


void Grid::moveLiquid(int y, int x, int dispersionRate)
{
	if (isEmpty(y + 1, x))
	{
		moveCell(y, x, y + 1, x);
	}
	else if (isEmpty(y + 1, x + 1))
	{
		moveCell(y, x, y + 1, x + 1);
	}
	else if (isEmpty(y + 1, x - 1))
	{
		moveCell(y, x, y + 1, x - 1);
	}
	else
	{
		for (int i = 1; i <= dispersionRate; ++i)
		{
			int rand = GetRandomValue(0, 2);
			if (rand == 0)
			{
				// Check for intermediate occupied cells to the left
				bool canMoveLeft = true;
				for (int j = 1; j <= i; ++j)
				{
					if (!isEmpty(y, x - j))
					{
						canMoveLeft = false;
						break;
					}
				}
				if (canMoveLeft && isEmpty(y, x - i))
				{
					moveCell(y, x, y, x - i);
					return;
				}
			}
			else
			{
				// Check for intermediate occupied cells to the right
				bool canMoveRight = true;
				for (int j = 1; j <= i; ++j)
				{
					if (!isEmpty(y, x + j))
					{
						canMoveRight = false;
						break;
					}
				}
				if (canMoveRight && isEmpty(y, x + i))
				{
					moveCell(y, x, y, x + i);
					return;
				}
			}
		}
	}
}
