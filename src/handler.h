#pragma once
#include <raylib.h>
#include "grid.h"

class Handle
{
public:
	Handle(int width, int height, int cellsize) :
		m_grid(width, height, cellsize)
	{};

	void Draw();
	void Update();
	void InputMouse(int value);
	void inputChoice();

private:
	Grid m_grid;
	int m_choice;
};