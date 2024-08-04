#include <raylib.h>
#include "handler.h"

int main()
{
	const int CELL_SIZE = 10;
	const int WIDTH = 1200;
	const int HEIGHT = 800;
	const int OFFSET = 100;
	const char* TITLE = "Sandbox.";

	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(60);

	int gridWidth = (WIDTH - OFFSET);
	int gridHeight = (HEIGHT - OFFSET);

	Handle handle(gridWidth, gridHeight, CELL_SIZE, OFFSET);

	handle.DebuggSetValue(0, 0, 3);

	while (!WindowShouldClose())
	{
		//Event
		handle.inputChoice();

		//Update
		handle.Update();

		//Draw
		BeginDrawing();
		ClearBackground(BLACK);
		handle.Draw();
		EndDrawing();
	}
	CloseWindow();
}