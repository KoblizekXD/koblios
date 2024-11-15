#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <vmutil.h>
#include <stdint.h>

uint8_t *_text_mode_location;
uint8_t *_video_mode_location;
uint8_t mode = 0x0;

#define TEXT_MODE 0x0
#define VIDEO_MODE 0x1

struct _character {
	char c;
	uint8_t attr;
};

struct _character get_char(uint8_t *location)
{
	return (struct _character){location[0], location[1]};
}

int is_char(uint8_t *location)
{
	return location[0] != 0x0;
}

void draw_callback()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (mode == TEXT_MODE) {
		char *text = NULL;
    	size_t length = 0; 
		uint8_t *location = _text_mode_location;

    	while (is_char(location)) {
	        char *new_text = realloc(text, length + 2);
    	    if (!new_text) {
        	    free(text);
            	return;
	        }

    	    text = new_text;
        	text[length] = get_char(location).c;
	        length++;
	        location += 2;
    	}

	    if (text) {
    	    text[length] = '\0';
			DrawText(text, 1, 1, 18, GRAY);
	        free(text);
	    }
	}

	EndDrawing();
}

void init_disp(uint8_t *text_memory, uint8_t* video_memory)
{
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(800, 600, "BIOS Emulation Service");
	ClearWindowState(FLAG_WINDOW_RESIZABLE);
	_text_mode_location = text_memory;
	_video_mode_location = video_memory;
}

void use_video_mode() { mode = VIDEO_MODE; }
void use_text_mode() { mode = TEXT_MODE; }
