#pragma once
#include <vector>
#include <raylib.h>

class Element;

class Grid
{
public:
	Grid(int width, int height, int cellsize);

	void Draw(int type);
	void Update(int value);
	void setValue(int x, int y, int value);
	bool isWithinBounds(int y, int x);
	bool isEmpty(int y, int x);
	bool checkCell(int y, int x, int target);
	void moveCell(int y1, int x1, int y2, int x2);
	void moveCell(int y1, int x1, int y2, int x2, int swap);
	void addBlock(int mouseX, int mouseY, int value);
	void erase(int mouseX, int mouseY);
	int getCellsize() { return m_cellsize; }

private:
	int m_x;
	int m_y;
	int m_cellsize;
	std::vector<std::vector<int>> m_cells;
	Element* m_element;
};
