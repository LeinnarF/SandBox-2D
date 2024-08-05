#include "handler.h"

int SCALE = 2;

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

void Handle::UIPanel(int width, int height, Color color)
{
	DrawRectangle(width, 0, GetScreenWidth(), height, color);
	DrawText("Sandbox", width + 20, 10, 30, WHITE);

	const char* element = "init";

	if (m_choice == 1)
		element = "Sand";
	else if (m_choice == 2)
		element = "Water";
	else if (m_choice == 3)
		element = "Stone";
	else if (m_choice == 4)
		element = "Lava";

	DrawText("Element:", width + 20, 110, 20, WHITE);
	DrawText(element, width + 110, 110, 20, LIGHTGRAY);
}

void Handle::UIButton(int width)
{
	bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	Vector2 mousePoint = GetMousePosition();

	Rectangle buttonSand{ (float)width + 20,50, 30,30 };
	Rectangle buttonWater{ (float)width + 70, 50, 30,30 };
	Rectangle buttonStone{ (float)width + 120, 50, 30,30 };
	Rectangle buttonLava{ (float)width + 170, 50, 30, 30 };

	Color sand{ 254, 237, 192, 255 };
	Color water{ 90, 127, 255, 255 };
	Color stone{ 200, 200, 200, 255 };
	Color lava{ 231, 111, 81, 255 };

	if (isPressed(mousePoint, mousePressed, buttonSand))
		m_choice = 1;
	else if (isPressed(mousePoint, mousePressed, buttonWater))
		m_choice = 2;
	else if (isPressed(mousePoint, mousePressed, buttonStone))
		m_choice = 3;
	else if (isPressed(mousePoint, mousePressed, buttonLava))
		m_choice = 4;

	DrawRectangleRec(buttonSand, sand);
	DrawRectangleRec(buttonWater, water);
	DrawRectangleRec(buttonStone, stone);
	DrawRectangleRec(buttonLava, lava);
}

bool Handle::isPressed(Vector2 mousePos, bool mousePress, Rectangle button)
{
	if (CheckCollisionPointRec(mousePos, button) && mousePress)
	{
		return true;
	}
	return false;
}


