#include "handler.h"


void Handle::Draw()
{
	m_grid.Draw();
}

void Handle::Update()
{
	m_grid.Update(m_choice);
}

void Handle::InputMouse(int value)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		int monitor = GetMonitorCount();
		Vector2 mousePosition = GetMousePosition();
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, value);
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		int monitor = GetMonitorCount();
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

	else if (IsKeyPressed(KEY_ZERO))
		m_choice = 0;

	InputMouse(m_choice);

}
