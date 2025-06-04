#ifndef FONTS_H
#define FONTS_H

#include <stdio.h>
#include "colors.h"


#define BOLD             "\x1b[1m"
#define RESET_BOLD       "\x1b[22m"

#define ITALIC           "\x1b[3m"
#define RESET_ITALIC     "\x1b[23m"

#define UNDERLINE        "\x1b[4m"
#define RESET_UNDERLINE  "\x1b[24m

void italic(const char *s);
void bold(const char *s);
void color_italic(const char *color, const char *s);
void color_bold(const char *color, const char *s);
void under_line(const char *s);
void color_under_line(const char *s);

#endif
