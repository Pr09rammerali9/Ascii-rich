#ifndef BG_H
#define BG_H

#include <stdio.h>

#define BG_BLACK            "\x1b[40m"
#define BG_RED              "\x1b[41m"
#define BG_GREEN            "\x1b[42m"
#define BG_YELLOW           "\x1b[43m"
#define BG_BLUE             "\x1b[44m"
#define BG_MAGENTA          "\x1b[45m"
#define BG_CYAN             "\x1b[46m"
#define BG_WHITE            "\x1b[47m"
#define BG_DEFAULT_BACKGROUND "\x1b[49m"

#define BG_BRIGHT_BLACK     "\x1b[100m"
#define BG_BRIGHT_RED       "\x1b[101m"
#define BG_BRIGHT_GREEN     "\x1b[102m"
#define BG_BRIGHT_YELLOW    "\x1b[103m"
#define BG_BRIGHT_BLUE      "\x1b[104m"
#define BG_BRIGHT_MAGENTA   "\x1b[105m"
#define BG_BRIGHT_CYAN      "\x1b[106m"
#define BG_BRIGHT_WHITE     "\x1b[107m"

#define BG_COLOR_256(color_number) "\x1b[48;5;" #color_number "m"

#define BG_COLOR_RGB(r, g, b)     "\x1b[48;2;" #r ";" #g ";" #b "m"


void chbg_color(const char *clr); 
void reset_bg_color();  

#endif
