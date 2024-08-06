#pragma once
#include <raylib.h>
#include "grid.h"

class Handle
{
public:
	Handle(int width, int height, int cellsize);

	void Draw();
	void Update();
	void InputMouse(int value);
	void inputChoice();
	void UIPanel(int width, int height, Color color);
	void UIButton(int width);
	bool isPressed(Vector2 mousePos, bool mousePress, Rectangle button);

private:
	Grid m_grid;
	int m_choice;
	int m_scale;
};