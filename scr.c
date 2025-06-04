#include "scr.h"

void clrscr() {

    printf("\x1b[2J");
 
    fflush(stdout);

}

void hide_cursor() {

    printf("\x1b[?25l");

    fflush(stdout);

}

void show_cursor() {

    printf("\x1b[!25h");

    fflush(stdout);

}
