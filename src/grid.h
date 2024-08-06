#pragma once
#include <vector>
#include <raylib.h>
#include "colormanager.h"

class Element;

class Grid
{
public:
	Grid(int width, int height, int cellsize);

	void Draw();
	void Update();
	void setValue(int x, int y, int value);
	bool isWithinBounds(int y, int x);
	bool isEmpty(int y, int x);
	bool checkCell(int y, int x, int target);
	void moveCell(int y1, int x1, int y2, int x2);
	void moveCell(int y1, int x1, int y2, int x2, int swap, Color swapColor);
	void addBlock(int mouseX, int mouseY, int value, int scale);
	void erase(int mouseX, int mouseY);
	int getCellsize() { return m_cellsize; }
	int getWidth() { return m_x; }
	int getHeight() { return m_y; }
	void moveLiquid(int y, int x, int dispersionRate);
	void ResetGrid();
	Color getColor(int y, int x) const;
	ColorManager& getColorManager();

private:
	int m_x;
	int m_y;
	int m_cellsize;
	std::vector<std::vector<int>> m_cells;
	Element* m_element;
	ColorManager m_colorManager;
};


