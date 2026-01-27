#include "stdio.h"
#include "stdlib.h"
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#include "draw.h"

long gettime(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)ts.tv_sec * 1000000L + ts.tv_nsec/1000;
}

struct termios old;

void enable_raw_mode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &old);
    t = old;

//    t.c_lflag &= ~(ICANON | ECHO); // pas de ligne, pas d'écho
    t.c_cc[VMIN]  = 0;             // lecture non bloquante
    t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

void disable_echo() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_echo() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

