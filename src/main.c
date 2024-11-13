#include <raylib.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(800, 600, "BIOS 16bit Emulator");

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GetColor(0x14161B));
		EndDrawing();
	}

	CloseWindow();
	return EXIT_SUCCESS;
}
