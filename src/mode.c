#include "mode.h"

static termios_t cur_tio;
static termios_t og_tio;

static winsize_t ws;

static int ret;

bool raw_mode(void) {

    ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

    if (cur_tio.c_lflag & ICANON)
                return false;
    else
                return true;

}

bool echo_mode(void) {

       ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio
    );

       if (ret == -1) {

           perror("ioctl:term attr failed");

           exit(EXIT_FAILURE);

       }

       if (cur_tio.c_lflag & ECHO)
                    return true;
       else
                    return false;

}


char *term(void) {
    char *store_var;
    store_var = getenv("TERM");

    if (store_var == NULL) {

        perror("getenv: TERM environment variable not set");

        exit(EXIT_FAILURE);

    } else {

        if (strcmp(store_var, "xterm-256color") == 0)
            return "xterm, colors bits: 256";

        else if (strcmp(store_var, "xterm-color") == 0)
            return "xterm, colors bits: 8";

        else if (strcmp(store_var, "xterm") == 0)
            return "xterm, colors bits: 8 (generic)";

        else if (strcmp(store_var, "screen-256color") == 0)
            return "GNU Screen multiplexer, colors bits: 256";

        else if (strcmp(store_var, "screen") == 0)
            return "GNU Screen multiplexer, colors bits: 8";

        else if (strcmp(store_var, "tmux-256color") == 0)
            return "Tmux multiplexer, colors bits: 256";

        else if (strcmp(store_var, "tmux") == 0)
            return "Tmux multiplexer, colors bits: 8";

        else if (strcmp(store_var, "rxvt-unicode-256color") == 0)
            return "urxvt (rxvt-unicode), colors bits: 256";

        else if (strcmp(store_var, "rxvt-unicode") == 0)
            return "urxvt (rxvt-unicode), colors bits: 8";

        else if (strcmp(store_var, "rxvt") == 0)
            return "rxvt, colors bits: 8";

        else if (strcmp(store_var, "alacritty-256color") == 0)
            return "Alacritty, colors bits: 256";

        else if (strcmp(store_var, "alacritty") == 0)
            return "Alacritty, colors bits: 256 (default)";

        else if (strcmp(store_var, "kitty-256color") == 0)
            return "Kitty, colors bits: 256";

        else if (strcmp(store_var, "kitty") == 0)
            return "Kitty, colors bits: 256 (default)";

        else if (strcmp(store_var, "wezterm-256color") == 0)
            return "WezTerm, colors bits: 256";

        else if (strcmp(store_var, "wezterm") == 0)
            return "WezTerm, colors bits: 256 (default)";

        else if (strcmp(store_var, "linux") == 0)
            return "Linux console (TTY), colors bits: 8";

        else if (strcmp(store_var, "st-256color") == 0)
            return "ST (Simple Terminal), colors bits: 256";

        else if (strcmp(store_var, "st") == 0)
            return "ST (Simple Terminal), colors bits: 8";

        else
            return "Unknown/Generic terminal, colors bits: unknown";
    }
}

void set_raw_mode(void) {

        og_tio = cur_tio;

        cur_tio.c_lflag &= ~(ICANON | ECHO);
        cur_tio.c_cc[VMIN] = 1;
        cur_tio.c_cc[VTIME] = 0;

        ret = ioctl(STDIN_FILENO, TCSETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }
}

void reset_mod(void) {

        ret = ioctl(STDIN_FILENO, TCSETS, &og_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);
        }
}

void set_echo_mode(const char *stat) {

    ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

    og_tio = cur_tio;

    if (strcmp(stat, "on") == 0)
            cur_tio.c_lflag |= ECHO;

    else if (strcmp(stat, "off") == 0)
            cur_tio.c_lflag &= ~ECHO;

    else
            fprintf(stderr, "invalid status, pls choose between on or off");

    ret = ioctl(STDOUT_FILENO, TCSETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

}

void set_can_mode() {

        ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }

        og_tio = cur_tio;

        cur_tio.c_lflag |= ICANON;
        cur_tio.c_cc[VMIN] = 0;
        cur_tio.c_cc[VTIME] = 0;

        ret = ioctl(STDIN_FILENO, TCSETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }

}#include "mode.h"

static termios_t cur_tio;
static termios_t og_tio;

static winsize_t ws;

static int ret;

bool raw_mode(void) {

    ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

    if (cur_tio.c_lflag & ICANON)
                return false;
    else
                return true;

}

bool echo_mode(void) {

       ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio
    );

       if (ret == -1) {

           perror("ioctl:term attr failed");

           exit(EXIT_FAILURE);

       }

       if (cur_tio.c_lflag & ECHO)
                    return true;
       else
                    return false;

}


char *term(void) {
    char *store_var;
    store_var = getenv("TERM");

    if (store_var == NULL) {

        perror("getenv: TERM environment variable not set");

        exit(EXIT_FAILURE);

    } else {

        if (strcmp(store_var, "xterm-256color") == 0)
            return "xterm, colors bits: 256";

        else if (strcmp(store_var, "xterm-color") == 0)
            return "xterm, colors bits: 8";

        else if (strcmp(store_var, "xterm") == 0)
            return "xterm, colors bits: 8 (generic)";

        else if (strcmp(store_var, "screen-256color") == 0)
            return "GNU Screen multiplexer, colors bits: 256";

        else if (strcmp(store_var, "screen") == 0)
            return "GNU Screen multiplexer, colors bits: 8";

        else if (strcmp(store_var, "tmux-256color") == 0)
            return "Tmux multiplexer, colors bits: 256";

        else if (strcmp(store_var, "tmux") == 0)
            return "Tmux multiplexer, colors bits: 8";

        else if (strcmp(store_var, "rxvt-unicode-256color") == 0)
            return "urxvt (rxvt-unicode), colors bits: 256";

        else if (strcmp(store_var, "rxvt-unicode") == 0)
            return "urxvt (rxvt-unicode), colors bits: 8";

        else if (strcmp(store_var, "rxvt") == 0)
            return "rxvt, colors bits: 8";

        else if (strcmp(store_var, "alacritty-256color") == 0)
            return "Alacritty, colors bits: 256";

        else if (strcmp(store_var, "alacritty") == 0)
            return "Alacritty, colors bits: 256 (default)";

        else if (strcmp(store_var, "kitty-256color") == 0)
            return "Kitty, colors bits: 256";

        else if (strcmp(store_var, "kitty") == 0)
            return "Kitty, colors bits: 256 (default)";

        else if (strcmp(store_var, "wezterm-256color") == 0)
            return "WezTerm, colors bits: 256";

        else if (strcmp(store_var, "wezterm") == 0)
            return "WezTerm, colors bits: 256 (default)";

        else if (strcmp(store_var, "linux") == 0)
            return "Linux console (TTY), colors bits: 8";

        else if (strcmp(store_var, "st-256color") == 0)
            return "ST (Simple Terminal), colors bits: 256";

        else if (strcmp(store_var, "st") == 0)
            return "ST (Simple Terminal), colors bits: 8";

        else
            return "Unknown/Generic terminal, colors bits: unknown";
    }
}

void set_raw_mode(void) {

        og_tio = cur_tio;

        cur_tio.c_lflag &= ~(ICANON | ECHO);
        cur_tio.c_cc[VMIN] = 1;
        cur_tio.c_cc[VTIME] = 0;

        ret = ioctl(STDIN_FILENO, TCSETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }
}

void reset_mod(void) {

        ret = ioctl(STDIN_FILENO, TCSETS, &og_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);
        }
}

void set_echo_mode(const char *stat) {

    ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

    og_tio = cur_tio;

    if (strcmp(stat, "on") == 0)
            cur_tio.c_lflag |= ECHO;

    else if (strcmp(stat, "off") == 0)
            cur_tio.c_lflag &= ~ECHO;

    else
            fprintf(stderr, "invalid status, pls choose between on or off");

    ret = ioctl(STDOUT_FILENO, TCSETS, &cur_tio);

    if (ret == -1) {

        perror("ioctl:term attr failed");

        exit(EXIT_FAILURE);

    }

}

void set_can_mode() {

        ret = ioctl(STDIN_FILENO, TCGETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }

        og_tio = cur_tio;

        cur_tio.c_lflag |= ICANON;
        cur_tio.c_cc[VMIN] = 0;
        cur_tio.c_cc[VTIME] = 0;

        ret = ioctl(STDIN_FILENO, TCSETS, &cur_tio);

        if (ret == -1) {

                perror("ioctl:term attr failed");

                exit(EXIT_FAILURE);

        }

}
