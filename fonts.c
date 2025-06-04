#include "fonts.h"

void italic(const char *s) {

    printf("%s%s%s", ITALIC, s, RESET_ITALIC);

    fflush(stdout);

}

void bold(const char *s) {

    printf("%s%s%s", BOLD, s, RESET_BOLD);

    fflush(stdout);

}

void color_italic(const char *color, const char *s) {

    printf("%s%s%s%s%s", ITALIC, color, s, RESET, RESET_ITALIC);

    fflush(stdout);

}

void color_bold(const char *color, const char *s) {

    printf("%s%s%s%s%s", BOLD, color, s, RESET, RESET_BOLD);

    fflush(stdout);

}

void under_line(const char *s) {

    printf("%s%s%s",UNDERLINE, s, RESET_UNDERLINE);

    fflush(stdout);

}

void color_under_line(const char *color, const char *s) {

    printf("%s%s%s%s%s",UNDERLINE, color, s, RESET, RESET_UNDERLINE);

    fflush(stdout);

}


