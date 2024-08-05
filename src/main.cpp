#include <raylib.h>
#include "handler.h"

int main()
{
	const int CELL_SIZE = 10;
	const int WIDTH = 1500;
	const int HEIGHT = 800;
	const int OFFSET = 0;
	const char* TITLE = "Sandbox.";

	Color background{ 245, 237, 237, 255 };

	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(60);

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
		ClearBackground(background);
		handle.Draw();
		EndDrawing();
	}
	CloseWindow();
}