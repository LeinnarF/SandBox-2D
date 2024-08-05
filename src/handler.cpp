#include "handler.h"

int SCALE = 1;

Handle::Handle(int width, int height, int cellsize) :
	m_grid(width, height, cellsize), m_choice(1)
{};

void Handle::DebuggSetValue(int x, int y, int value)
{
	m_grid.setValue(x, y, value);
}

void Handle::Draw()
{
	m_grid.Draw();
}

void Handle::Update()
{
	m_grid.Update();
}

void Handle::InputMouse(int type)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePosition = GetMousePosition();
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, type, SCALE);
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 mousePosition = GetMousePosition();
		m_grid.erase((int)mousePosition.x, (int)mousePosition.y);
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

	InputMouse(m_choice);

}

