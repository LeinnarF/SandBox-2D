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
	void Update(int type);
	void UpdateUp();
	void setValue(int x, int y, int value);
	bool isWithinBounds(int y, int x);
	bool isEmpty(int y, int x);
	bool checkCell(int y, int x, int target);
	void moveCell(int y1, int x1, int y2, int x2);
	void moveCell(int y1, int x1, int y2, int x2, int swap, Color swapColor);
	void removeCell(int y, int x);
	void addBlock(int mouseX, int mouseY, int value, int scale, int shape);
	void erase(int mouseX, int mouseY);
	void moveLiquid(int y, int x, int dispersionRate);
	void ResetGrid();
	Color getColor(int y, int x) const;
	ColorManager& getColorManager() { return m_colorManager; }
	int getCellsize() const { return m_cellsize; }
	int getWidth() const { return m_x; }
	int getHeight() const { return m_y; }
	int getValue(int x, int y) const { return m_cells[y][x]; }

private:
	int m_x;
	int m_y;
	int m_cellsize;
	std::vector<std::vector<int>> m_cells;
	Element* m_element;
	ColorManager m_colorManager;
};


