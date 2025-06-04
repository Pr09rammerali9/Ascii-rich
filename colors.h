#ifndef CLR_H
#define CLR_H

#include <stdio.h> 

#define RESET            "\x1b[0m"

#define BLACK            "\x1b[30m"
#define RED              "\x1b[31m"
#define GREEN            "\x1b[32m"
#define YELLOW           "\x1b[33m"
#define BLUE             "\x1b[34m"
#define MAGENTA          "\x1b[35m"
#define CYAN             "\x1b[36m"
#define WHITE            "\x1b[37m"
#define DEFAULT_FOREGROUND "\x1b[39m"

#define BRIGHT_BLACK     "\x1b[90m"
#define BRIGHT_RED       "\x1b[91m"
#define BRIGHT_GREEN     "\x1b[92m"
#define BRIGHT_YELLOW    "\x1b[93m"
#define BRIGHT_BLUE      "\x1b[94m"
#define BRIGHT_MAGENTA   "\x1b[95m"
#define BRIGHT_CYAN      "\x1b[96m"
#define BRIGHT_WHITE     "\x1b[97m"

#define COLOR_256(color_number) "\x1b[38;5;" #color_number "m"

#define COLOR_RGB(r, g, b)     "\x1b[38;2;" #r ";" #g ";" #b "m"

void color_txt(const char *color, const char *txt);

#endif
