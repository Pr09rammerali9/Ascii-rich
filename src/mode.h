#ifndef MODE_H
#define MODE_H

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int tc_flag;
typedef unsigned char cc;
typedef unsigned int speed;
typedef unsigned short ushort;

#ifndef VMIN                                      
#define VMIN 6

#endif


#ifndef VTIME

#define VTIME 5

#endif

#ifndef NCCS

#define NCCS 32

#endif

typedef struct {
    tc_flag c_iflag;
    tc_flag c_oflag;
    tc_flag c_cflag;
    tc_flag c_lflag;

    cc c_cc[NCCS];

    speed c_ispeed;
    speed c_ospeed;
} termios_t;

#define TCGETS 0x5401
#define TCSETS 0x5402
#define TIOCGWINSZ 0x5413
#define ICANON 0x00000002
#define ECHO 0x00000008

typedef struct {
    ushort ws_row;
    ushort ws_col;
    ushort ws_xpixel;
    ushort ws_ypixel;
} winsize_t;

typedef struct {
    ushort rows;
    ushort cols;
} term_t;

bool raw_mode(void);
bool cano_mode(void);
bool echo_mode(void);

term_t term_sizes(void);

char *term(void);

void set_raw_mode(void);
void set_can_mode(void);
void set_echo_mode(const char *stat);
void reset_mod(void);

#endif
