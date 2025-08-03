#include "term.h"

void termout(const char *fmt, ...) {

    va_list args;

    va_start(args, fmt);

    vprintf(fmt, args);

    fflush(stdout);

    va_end(args);

}

void termerr(const char *fmt, ...) {

    va_list args;

    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    fflush(stderr);

    va_end(args);

}