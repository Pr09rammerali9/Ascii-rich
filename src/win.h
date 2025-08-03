#ifndef WIN_H
#define WIN_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "../lib/arena.h"
#include "scr.h"
#include "colors.h" // Assuming this contains your ANSI color definitions
#include "bg.h"     // For BG_DEFAULT_BACKGROUND

typedef struct {
    char character;
    int fg_color; // These will now hold an index or a custom enum
    int bg_color; // that maps to your ANSI color macros
} Cell;

typedef struct Window {
    int id;
    int x, y;
    int width, height;
    Cell **buffer;
    Cell **shadow_buffer;
    int cursor_x, cursor_y;
    bool needs_redraw;
    struct Window *next_z;
    struct Window *prev_z;
    char *title;
    bool has_border;
    bool is_focused;
    Arena *arena;
} Window;

#define WIN_DEFAULT_FG_COLOR_CODE DEFAULT_FOREGROUND
#define WIN_DEFAULT_BG_COLOR_CODE BG_DEFAULT_BACKGROUND
#define WIN_COLOR_GRAY_CODE "\x1b[90m"
#define WIN_COLOR_BLACK_CODE "\x1b[40m"
#define WIN_COLOR_WHITE_CODE "\x1b[97m"
#define WIN_COLOR_BLUE_CODE "\x1b[44m"


Window* window_create(int x, int y, int width, int height, Arena *arena);
void window_destroy(Window* window);
void window_put_char(Window* window, int wx, int wy, char c, int fg, int bg);
void window_print_string(Window* window, int wx, int wy, const char* str, int fg, int bg);
void window_clear(Window* window);
void window_refresh(Window* window);
void window_draw_border(Window* window);
void window_set_cursor(Window* window, int wx, int wy);
Cell window_get_cell(Window* window, int wx, int wy);

#endif // WIN_H
