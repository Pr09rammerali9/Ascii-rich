#include "win.h"                                  #include "colors.h"                               #include "bg.h"

#ifndef WIN_ASSERT
#define WIN_ASSERT assert
#endif

static void set_console_colors(int fg, int bg) {
    printf("%s%s", (char*)fg, (char*)bg);
}

static Cell** alloc_cell_buffer(Arena* arena, int width, int height) {
    if (!arena || width <= 0 || height <= 0) return NULL;
    Cell** rows = (Cell**)arena_alloc(arena, height * sizeof(Cell*));
    if (!rows) return NULL;
    Cell* all_cells = (Cell*)arena_alloc(arena, (size_t)width * height * sizeof(Cell));
    if (!all_cells) return NULL;
    for (int i = 0; i < height; ++i) {
        rows[i] = &all_cells[i * width];
    }
    return rows;
}

Window* window_create(int x, int y, int width, int height, Arena *arena) {
    if (width <= 0 || height <= 0 || !arena) {
        WIN_ASSERT(0 && "window_create: Invalid window dimensions or arena provided.");
        return NULL;
    }
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) return NULL;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;
    window->cursor_x = 0;
    window->cursor_y = 0;
    window->needs_redraw = true;
    window->next_z = NULL;
    window->prev_z = NULL;
    window->title = NULL;
    window->has_border = true;
    window->is_focused = false;
    window->arena = arena;
    window->buffer = alloc_cell_buffer(arena, width, height);
    window->shadow_buffer = alloc_cell_buffer(arena, width, height);
    if (!window->buffer || !window->shadow_buffer) {
        window_destroy(window);
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            window->buffer[i][j] = (Cell){' ', (int)WIN_DEFAULT_FG_COLOR_CODE, (int)WIN_DEFAULT_BG_COLOR_CODE};
            window->shadow_buffer[i][j] = (Cell){' ', (int)WIN_DEFAULT_FG_COLOR_CODE, (int)WIN_DEFAULT_BG_COLOR_CODE};
        }
    }
    static int next_window_id = 0;
    window->id = next_window_id++;
    return window;
}

void window_destroy(Window* window) {
    if (!window) return;
    free(window);
}

void window_put_char(Window* window, int wx, int wy, char c, int fg, int bg) {
    if (!window || wx < 0 || wx >= window->width || wy < 0 || wy >= window->height) {
        return;
    }
    Cell *target_cell = &window->buffer[wy][wx];
    if (target_cell->character != c ||
        target_cell->fg_color != fg ||
        target_cell->bg_color != bg)
    {
        target_cell->character = c;
        target_cell->fg_color = fg;
        target_cell->bg_color = bg;
        window->needs_redraw = true;
    }
}

void window_print_string(Window* window, int wx, int wy, const char* str, int fg, int bg) {
    if (!window || !str || wy < 0 || wy >= window->height) return;
    int current_x = wx;
    const char* ptr = str;
    while (*ptr != '\0' && current_x < window->width) {
        window_put_char(window, current_x, wy, *ptr, fg, bg);
        current_x++;
        ptr++;
    }
}

void window_clear(Window* window) {
    if (!window) return;
    for (int i = 0; i < window->height; ++i) {
        for (int j = 0; j < window->width; ++j) {
            window_put_char(window, j, i, ' ', (int)WIN_DEFAULT_FG_COLOR_CODE, (int)WIN_DEFAULT_BG_COLOR_CODE);
        }
    }
    window->needs_redraw = true;
}

void window_draw_border(Window* window) {
    if (!window || !window->has_border) return;
    char h_line = '-';
    char v_line = '|';
    char corner = '+';
    int fg = (int)WIN_COLOR_GRAY_CODE;
    int bg = (int)WIN_COLOR_BLACK_CODE;

    for (int j = 1; j < window->width - 1; ++j) {
        window_put_char(window, j, 0, h_line, fg, bg);
        window_put_char(window, j, window->height - 1, h_line, fg, bg);
    }
    for (int i = 1; i < window->height - 1; ++i) {
        window_put_char(window, 0, i, v_line, fg, bg);
        window_put_char(window, window->width - 1, i, v_line, fg, bg);
    }
    window_put_char(window, 0, 0, corner, fg, bg);
    window_put_char(window, window->width - 1, 0, corner, fg, bg);
    window_put_char(window, 0, window->height - 1, corner, fg, bg);
    window_put_char(window, window->width - 1, window->height - 1, corner, fg, bg);

    if (window->title) {
        int title_len = (int)strlen(window->title);
        int title_start_x = 2;
        if (title_start_x + title_len < window->width - 1) {
             window_print_string(window, title_start_x, 0, window->title, (int)WIN_COLOR_WHITE_CODE, (int)WIN_COLOR_BLUE_CODE);
        }
    }
}

void window_refresh(Window* window) {
    if (!window || !window->needs_redraw) return;
    if (window->has_border) {
        window_draw_border(window);
    }
    int last_fg = -1, last_bg = -1;
    for (int i = 0; i < window->height; ++i) {
        for (int j = 0; j < window->width; ++j) {
            Cell *current_cell = &window->buffer[i][j];
            Cell *shadow_cell = &window->shadow_buffer[i][j];
            int abs_y = window->y + i;
            int abs_x = window->x + j;

            bool changed = (current_cell->character != shadow_cell->character ||
                            current_cell->fg_color != shadow_cell->fg_color ||
                            current_cell->bg_color != shadow_cell->bg_color);

            if (changed) {
                mv_cursor_abs_pos(abs_y, abs_x);
                if (current_cell->fg_color != last_fg || current_cell->bg_color != last_bg) {
                    set_console_colors(current_cell->fg_color, current_cell->bg_color);
                    last_fg = current_cell->fg_color;
                    last_bg = current_cell->bg_color;
                }
                putchar(current_cell->character);
                *shadow_cell = *current_cell;
            }
        }
    }

    set_console_colors((int)WIN_DEFAULT_FG_COLOR_CODE, (int)WIN_DEFAULT_BG_COLOR_CODE);

    fflush(stdout);

    window->needs_redraw = false;
}

Cell window_get_cell(Window* window, int wx, int wy) {

    if (!window || wx < 0 || wx >= window->width || wy < 0 || wy >= window->height)
        return (Cell){' ', (int)WIN_DEFAULT_FG_COLOR_CODE, (int)WIN_DEFAULT_BG_COLOR_CODE};

    return window->buffer[wy][wx];
}

void window_set_cursor(Window* window, int wx, int wy) {

    if (!window || wx < 0 || wx > window->width || wy < 0 || wy > window->height)
        return;

    window->cursor_x = wx;
    window->cursor_y = wy;
}
