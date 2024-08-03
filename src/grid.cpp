#include "grid.h"
#include "element.h"

Grid::Grid(int width, int height, int cellsize) :
	m_x(width / cellsize),
	m_y(height / cellsize),
	m_cellsize(cellsize),
	m_cells(m_y, std::vector<int>(m_x, 0)),
	m_element()
{}

void Grid::Draw(int type)
{
	for (int y = 0; y < m_y; y++)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Draw(*this, y, x, type);
		}
	}
}

void Grid::Update(int value)
{
	for (int y = m_y - 2; y >= 0; y--)
	{
		for (int x = 0; x < m_x; x++)
		{
			m_element->Update(*this, y, x, value);
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

void Grid::addBlock(int mouseX, int mouseY, int value)
{
	int x = mouseX / m_cellsize;
	int y = mouseY / m_cellsize;
	if (isWithinBounds(y, x) && isEmpty(y, x))
		setValue(x, y, value);
}

void Grid::erase(int mouseX, int mouseY)
{
	int x = mouseX / m_cellsize;
	int y = mouseY / m_cellsize;
	if (isWithinBounds(y, x) && !isEmpty(y, x))
		setValue(x, y, 0);
}
