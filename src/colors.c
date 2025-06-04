#include "colors.h"

void color_txt(const char *color, const char *txt) {

    printf("%s%s%s", color, txt, RESET);

}
