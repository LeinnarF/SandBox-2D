#include "handler.h"
#include "colormanager.h"
#include <string>

Handle::Handle(int width, int height, int cellsize) :
	m_grid(width, height, cellsize), m_type(1), m_scale(2), m_shape(1)
{};

void Handle::Draw()
{
	m_grid.Draw();
}

void Handle::Update()
{
	m_grid.Update(m_type);
}

void Handle::InputMouse(int type)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePosition = GetMousePosition();
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, type, m_scale, m_shape);
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 mousePosition = GetMousePosition();
		m_grid.erase((int)mousePosition.x, (int)mousePosition.y);
	}
}

void Handle::inputChoice()
{
	if (IsKeyPressed(KEY_S))
	{
		m_scale *= 2;
		if (m_scale > 17)
			m_scale = 1;
	}

	InputMouse(m_type);
}

void Handle::UIPanel(int width, int height, Color color)
{
	DrawRectangle(width, 0, GetScreenWidth(), height, color);
	DrawText("Sandbox-2D", width + 20, 10, 30, WHITE);

	const char* element = "init";
	Color elementColor = WHITE;

	elementColor = ColorManager::getElementColor(m_type);

	switch (m_type)
	{
	case 1: element = "Sand"; break;
	case 2: element = "Water"; break;
	case 3: element = "Stone"; break;
	case 4: element = "Lava"; break;
	case 5: element = "Smoke"; break;
	case 6: element = "Cement"; break;
	case 7: element = "Acid"; break;
	case 8: element = "Oil"; break;
	case 9: element = "Fire"; break;
	case 10: element = "Gun Powder"; break;
	default: element = "init"; break;
	}

	DrawText("Element:", width + 20, 60, 20, WHITE);
	DrawText(element, width + 110, 60, 20, elementColor);
	DrawText("Scale: ", width + 50, 90, 20, WHITE);

	std::string scaleString = std::to_string(m_scale);
	const char* scaleChar = scaleString.c_str();

	DrawText(scaleChar, width + 120, 90, 20, WHITE);

	DrawText("Reset", width + 50, 120, 20, WHITE);

	const char* shape = "";
	if (m_shape == 1)
		shape = "Square";
	else
		shape = "Circle";

	DrawText("Shape: ", width + 50, 150, 20, WHITE);
	DrawText(shape, width + 120, 150, 19, RAYWHITE);

}

void Handle::UIButton(int width)
{
	bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	Vector2 mousePoint = GetMousePosition();

	//element buttons
	Rectangle buttonSand{ (float)width + 20,200, 30,30 };
	Rectangle buttonWater{ (float)width + 70, 200, 30,30 };
	Rectangle buttonStone{ (float)width + 120, 200, 30,30 };
	Rectangle buttonLava{ (float)width + 170, 200, 30, 30 };
	Rectangle buttonSmoke{ (float)width + 220, 200, 30,30 };
	Rectangle buttonCement{ (float)width + 270, 200,30,30 };
	Rectangle buttonAcid{ (float)width + 320, 200,30,30 };
	Rectangle buttonOil{ (float)width + 20, 250, 30,30 };
	Rectangle buttonFire{ (float)width + 70, 250,30,30 };
	Rectangle buttonGunPowder{ (float)width + 120, 250,30,30 };
	//util buttons
	Rectangle buttonScale{ (float)width + 20, 90, 15, 15 };
	Rectangle buttonReset{ (float)width + 20, 120, 15, 15 };
	Rectangle buttonShape{ (float)width + 20, 150, 15,15 };

	if (isPressed(mousePoint, mousePressed, buttonScale))
	{
		m_scale *= 2;
		if (m_scale > 17)
			m_scale = 1;
	}
	if (isPressed(mousePoint, mousePressed, buttonReset))
		m_grid.ResetGrid();

	if (isPressed(mousePoint, mousePressed, buttonShape))
	{
		m_shape = (m_shape + 1) % 2;
	}

	if (isPressed(mousePoint, mousePressed, buttonSand))
		m_type = 1;
	else if (isPressed(mousePoint, mousePressed, buttonWater))
		m_type = 2;
	else if (isPressed(mousePoint, mousePressed, buttonStone))
		m_type = 3;
	else if (isPressed(mousePoint, mousePressed, buttonLava))
		m_type = 4;
	else if (isPressed(mousePoint, mousePressed, buttonSmoke))
		m_type = 5;
	else if (isPressed(mousePoint, mousePressed, buttonCement))
		m_type = 6;
	else if (isPressed(mousePoint, mousePressed, buttonAcid))
		m_type = 7;
	else if (isPressed(mousePoint, mousePressed, buttonOil))
		m_type = 8;
	else if (isPressed(mousePoint, mousePressed, buttonFire))
		m_type = 9;
	else if (isPressed(mousePoint, mousePressed, buttonGunPowder))
		m_type = 10;

	DrawRectangleRec(buttonSand, ColorManager::getElementColor(1));
	DrawRectangleRec(buttonWater, ColorManager::getElementColor(2));
	DrawRectangleRec(buttonStone, ColorManager::getElementColor(3));
	DrawRectangleRec(buttonLava, ColorManager::getElementColor(4));
	DrawRectangleRec(buttonSmoke, ColorManager::getElementColor(5));
	DrawRectangleRec(buttonCement, ColorManager::getElementColor(6));
	DrawRectangleRec(buttonAcid, ColorManager::getElementColor(7));
	DrawRectangleRec(buttonOil, ColorManager::getElementColor(8));
	DrawRectangleRec(buttonFire, ColorManager::getElementColor(9));
	DrawRectangleRec(buttonGunPowder, ColorManager::getElementColor(10));

	DrawRectangleRec(buttonScale, RAYWHITE);
	DrawRectangleRec(buttonReset, RAYWHITE);
	DrawRectangleRec(buttonShape, RAYWHITE);
}

bool Handle::isPressed(Vector2 mousePos, bool mousePress, Rectangle button)
{
	if (CheckCollisionPointRec(mousePos, button) && mousePress)
	{
		return true;
	}
	return false;
}



