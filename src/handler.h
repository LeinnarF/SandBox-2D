#pragma once
#include <raylib.h>
#include "grid.h"

class Handle
{
public:
	Handle(int width, int height, int cellsize, int offset);

	void DebuggSetValue(int x, int y, int value);
	void Draw();
	void Update();
	void InputMouse(int value, int offset);
	void inputChoice();

private:
	Grid m_grid;
	int m_choice;
	int m_offset;
};