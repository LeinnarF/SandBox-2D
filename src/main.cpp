#include <raylib.h>
#include "handler.h"

int main()
{
	const int CELL_SIZE = 5;
	const int WIDTH = 800;
	const int HEIGHT = 800;
	const char* TITLE = "Sandbox.";

	InitWindow(WIDTH, HEIGHT, TITLE);
	SetTargetFPS(60);

	Handle handle(WIDTH, HEIGHT, CELL_SIZE);

	while (!WindowShouldClose())
	{
		//Event
		handle.inputChoice();

		//Update
		handle.Update();

		//Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		handle.Draw();
		EndDrawing();
	}
	CloseWindow();
}