#ifndef TERM_H
#define TERM_H

#include <stdio.h>
#include <stdarg.h>

void termout(const char *fmt, ...);
void termerr(const char *fmt, ...);

#endif