#include "stdio.h"
#include "stdlib.h"
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#include "draw.h"
#include "module.h"

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

void printBase(int type) {
    switch (type) {
        case MOD_BASE_1:
            printf("\x1B[48;2;128;128;128m");
            printf("🧻");
            printf("\x1B[0m");
            break;
        case MOD_BASE_2:
            printf("\x1B[48;2;128;128;128m");
            printf("📦");
            printf("\x1B[0m");
            break;
    }
}

void printSquareNumber(int nb) {
    switch (nb) {
        case 0:
            printf("0️⃣ ");
            break;
        case 1:
            printf("1️⃣ ");
            break;
        case 2:
            printf("2️⃣ ");
            break;
        case 3:
            printf("3️⃣ ");
            break;
        case 4:
            printf("4️⃣ ");
            break;
        case 5:
            printf("5️⃣ ");
            break;
        case 6:
            printf("6️⃣ ");
            break;
        case 7:
            printf("7️⃣ ");
            break;
        case 8:
            printf("8️⃣ ");
            break;
        case 9:
            printf("9️⃣ ");
            break;
        default:
            printf("%d", nb);
    }
}
