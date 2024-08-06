#include "handler.h"
#include <string>

static Color sand{ 254, 237, 192, 255 };
static Color water{ 117, 149, 224, 255 };
static Color stone{ 200, 200, 200, 255 };
static Color lava{ 231, 111, 81, 255 };

Handle::Handle(int width, int height, int cellsize) :
	m_grid(width, height, cellsize), m_choice(1), m_scale(2)
{};

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
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, type, m_scale);
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
	DrawText("Sandbox-2D", width + 20, 10, 30, WHITE);

	const char* element = "init";
	Color elementColor = WHITE;

	if (m_choice == 1)
	{
		element = "Sand";
		elementColor = sand;
	}
	else if (m_choice == 2)
	{
		element = "Water";
		elementColor = water;
	}
	else if (m_choice == 3)
	{
		element = "Stone";
		elementColor = stone;
	}
	else if (m_choice == 4)
	{
		element = "Lava";
		elementColor = lava;
	}

	DrawText("Element:", width + 20, 110, 20, WHITE);
	DrawText(element, width + 110, 110, 20, elementColor);
	DrawText("Scale: ", width + 50, 150, 20, WHITE);

	std::string scaleString = std::to_string(m_scale);
	const char* scaleChar = scaleString.c_str();

	DrawText(scaleChar, width + 120, 150, 20, WHITE);

	DrawText("Reset", width + 50, 180, 20, WHITE);
}

void Handle::UIButton(int width)
{
	bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	Vector2 mousePoint = GetMousePosition();

	Rectangle buttonSand{ (float)width + 20,60, 30,30 };
	Rectangle buttonWater{ (float)width + 70, 60, 30,30 };
	Rectangle buttonStone{ (float)width + 120, 60, 30,30 };
	Rectangle buttonLava{ (float)width + 170, 60, 30, 30 };
	Rectangle buttonScale{ (float)width + 20, 152, 15, 15 };
	Rectangle buttonReset{ (float)width + 20, 180, 15, 15 };

	if (isPressed(mousePoint, mousePressed, buttonScale))
	{
		m_scale *= 2;
		if (m_scale > 10)
			m_scale = 1;
	}

	if (isPressed(mousePoint, mousePressed, buttonReset))
		m_grid.ResetGrid();

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
	DrawRectangleRec(buttonScale, RAYWHITE);
	DrawRectangleRec(buttonReset, RAYWHITE);

}

bool Handle::isPressed(Vector2 mousePos, bool mousePress, Rectangle button)
{
	if (CheckCollisionPointRec(mousePos, button) && mousePress)
	{
		return true;
	}
	return false;
}



