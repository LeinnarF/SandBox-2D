#include <raylib.h>
#include "handler.h"

int main()
{
	const int CELL_SIZE = 4;
	const int WIDTH = 1300;
	const int HEIGHT = 800;
	const char* TITLE = "Sandbox.";

	Color background{ 77, 76, 99, 255 };
	Color rightPanel{ 123, 121, 148, 255 };

	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(120);

	int gridWidth = (WIDTH - 300);
	int gridHeight = (HEIGHT);

	Handle handle(gridWidth, gridHeight, CELL_SIZE);

	while (!WindowShouldClose())
	{
		//Event
		handle.inputChoice();

		//Update
		handle.Update();

		//Draw
		BeginDrawing();
		handle.UIPanel(gridWidth, gridHeight, rightPanel);
		handle.UIButton(gridWidth);
		DrawText("Created by LeinnarF", gridWidth + 250, gridHeight - 30, 13, LIGHTGRAY);
		ClearBackground(background);
		handle.Draw();

		EndDrawing();
	}
	CloseWindow();
}