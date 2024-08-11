#include "grid.h"
#include "element.h"

Grid::Grid(int width, int height, int cellsize) :
	m_x(width / cellsize),
	m_y(height / cellsize),
	m_cellsize(cellsize),
	m_cells(m_y, std::vector<int>(m_x, 0)),
	m_colorManager(m_x, m_y),
	m_element()
{}

void Grid::Draw()
{
	for (int y = 0; y < m_y; y++)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Draw(*this, y, x);
		}
	}
}

void Grid::Update(int type)
{
	for (int y = m_y - 1; y >= 0; y--)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Update(*this, y, x);
		}
	}
	UpdateUp();
}

void Grid::UpdateUp()
{
	for (int y = 0; y < m_y; y++)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->UpdateUp(*this, y, x);
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
	if (!isWithinBounds(y, x)) return false;
	return m_cells[y][x] == target;
}

void Grid::moveCell(int y1, int x1, int y2, int x2)
{
	m_cells[y2][x2] = m_cells[y1][x1];
	m_cells[y1][x1] = 0;
	m_colorManager.setColor(y2, x2, m_colorManager.getColor(y1, x1));
	m_colorManager.setColor(y1, x1, BLANK);
}

void Grid::moveCell(int y1, int x1, int y2, int x2, int swap, Color swapColor)
{
	m_cells[y2][x2] = m_cells[y1][x1];
	m_cells[y1][x1] = swap;
	m_colorManager.setColor(y2, x2, m_colorManager.getColor(y1, x1));
	m_colorManager.setColor(y1, x1, swapColor);
}

void Grid::removeCell(int y, int x)
{
	if (isWithinBounds(y, x) && !checkCell(y, x, 0))
	{
		m_cells[y][x] = 0;
		m_colorManager.setColor(y, x, RED);
	}
}

void Grid::addBlock(int mouseX, int mouseY, int value, int scale, int state)
{
	int startx = mouseX / m_cellsize;
	int starty = mouseY / m_cellsize;
	int radius = scale / 2;
	int radiusSquared = radius * radius;

	if (state == 1)
	{
		for (int y = starty; y < starty + scale; y++)
		{
			for (int x = startx; x < startx + scale; x++)
			{
				if (isWithinBounds(y, x) && isEmpty(y, x))
				{
					int noise = GetRandomValue(0, 4);
					if (value == 3)
						noise = 0;
					setValue(x + noise, y + noise, value);
					m_colorManager.elementColor(y + noise, x + noise, value);
				}
			}
		}
	}
	else
	{
		for (int y = starty - radius; y <= starty + radius; y++)
		{
			for (int x = startx - radius; x <= startx + radius; x++)
			{
				int dx = x - startx;
				int dy = y - starty;
				int distanceSquared = dx * dx + dy * dy;

				if (distanceSquared <= radiusSquared && isWithinBounds(y, x) && isEmpty(y, x))
				{
					setValue(x, y, value);
					m_colorManager.elementColor(y, x, value);
				}
			}
		}
	}
}


void Grid::erase(int mouseX, int mouseY)
{
	int x = mouseX / m_cellsize;
	int y = mouseY / m_cellsize;
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

void Grid::ResetGrid()
{
	m_colorManager.resetColors();

	for (int y = 0; y < m_y; y++)
	{
		for (int x = 0; x < m_x; x++)
		{
			setValue(x, y, 0);
		}
	}
}

Color Grid::getColor(int y, int x) const
{
	return m_colorManager.getColor(y, x);
}

