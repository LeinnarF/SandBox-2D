#include "handler.h"

int SCALE = 1;

Handle::Handle(int width, int height, int cellsize, int offset) :
	m_grid(width, height, cellsize), m_choice(1), m_offset(offset)
{};

void Handle::DebuggSetValue(int x, int y, int value)
{
	m_grid.setValue(x, y, value);
}

void Handle::Draw()
{
	int gridWidth = m_grid.getWidth() * m_grid.getCellsize();
	int gridHeight = m_grid.getHeight() * m_grid.getCellsize();

	int offsetX = (GetScreenWidth() - gridWidth) / 2;
	int offsetY = (GetScreenHeight() - gridHeight) / 2;

	m_grid.Draw(offsetY, offsetX);
}

void Handle::Update()
{
	m_grid.Update();
}

void Handle::InputMouse(int type, int offset)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int monitor = GetMonitorCount();
		Vector2 mousePosition = GetMousePosition();
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, type, SCALE, m_offset);
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		int monitor = GetMonitorCount();
		Vector2 mousePosition = GetMousePosition();
		m_grid.erase((int)mousePosition.x, (int)mousePosition.y, m_offset);
	}
}

void Handle::inputChoice()
{
	if (IsKeyPressed(KEY_ONE))
		m_choice = 1;

	else if (IsKeyPressed(KEY_TWO))
		m_choice = 2;

	else if (IsKeyPressed(KEY_THREE))
		m_choice = 3;

	else if (IsKeyPressed(KEY_FOUR))
		m_choice = 4;
	else if (IsKeyPressed(KEY_FIVE))
		m_choice = 5;

	InputMouse(m_choice, m_offset);

}

