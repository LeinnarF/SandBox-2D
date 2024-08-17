#include "handler.h"
#include "colormanager.h"
#include "elementEnum.h"
#include <string>
#include <vector>



Handle::Handle(int width, int height, int cellsize) :
	m_grid(width, height, cellsize), m_type(sand), m_scale(2), m_shape(1)
{}

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
	Vector2 mousePosition = GetMousePosition();

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		m_grid.addBlock((int)mousePosition.x, (int)mousePosition.y, type, m_scale, m_shape);
	}
	else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
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

	const char* element = getElementName(m_type);
	Color elementColor = ColorManager::getElementColor(m_type);

	DrawText("Element:", width + 20, 60, 20, WHITE);
	DrawText(element, width + 110, 60, 20, elementColor);
	DrawText("Scale:", width + 50, 90, 20, WHITE);

	std::string scaleString = std::to_string(m_scale);
	DrawText(scaleString.c_str(), width + 120, 90, 20, WHITE);

	DrawText("Reset", width + 50, 120, 20, WHITE);

	const char* shape = (m_shape == 1) ? "Noise" : "Circle";
	DrawText("Shape:", width + 50, 150, 20, WHITE);
	DrawText(shape, width + 120, 150, 19, RAYWHITE);
}

void Handle::UIButton(int width)
{
	bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	Vector2 mousePoint = GetMousePosition();

	// Define buttons for elements
	std::vector<Rectangle> elementButtons = createElementButtons(width);

	// Define utility buttons
	Rectangle buttonScale{ (float)width + 20, 90, 15, 15 };
	Rectangle buttonReset{ (float)width + 20, 120, 15, 15 };
	Rectangle buttonShape{ (float)width + 20, 150, 15, 15 };

	// Handle utility buttons
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

	// Handle element buttons
	for (int i = 0; i < endType - 1; i++)
	{
		if (isPressed(mousePoint, mousePressed, elementButtons[i]))
		{
			m_type = i + 1;
		}
		DrawRectangleRec(elementButtons[i], ColorManager::getElementColor(i + 1));
	}

	// Draw utility buttons
	DrawRectangleRec(buttonScale, RAYWHITE);
	DrawRectangleRec(buttonReset, RAYWHITE);
	DrawRectangleRec(buttonShape, RAYWHITE);
}

bool Handle::isPressed(Vector2 mousePos, bool mousePress, Rectangle button)
{
	return CheckCollisionPointRec(mousePos, button) && mousePress;
}

const char* Handle::getElementName(int type)
{
	//TODO: add here
	switch (type)
	{
	case sand: return "Sand";
	case water: return "Water";
	case stone: return "Stone";
	case lava: return "Lava";
	case smoke: return "Smoke";
	case cement: return "Cement";
	case acid: return "Acid";
	case oil: return "Oil";
	case fire: return "Fire";
	case gunpowder: return "Gun Powder";
	case wood: return "Wood";
	default: return "init";
	}
}

std::vector<Rectangle> Handle::createElementButtons(int width)
{
	std::vector<Rectangle> buttons;
	int columns = 5;
	float xPos = 20, yPos = 200;
	float buttonWidth = 30;
	float buttonHeight = 30;
	int padding = 20;

	for (int i = 1; i < endType; i++)
	{
		buttons.push_back(Rectangle{ (float)width + xPos, yPos, buttonWidth, buttonHeight });

		xPos += buttonWidth + padding;
		if (i % columns == 0)
		{
			xPos = 20;
			yPos += buttonHeight + padding;
		}
	}

	return buttons;
}



