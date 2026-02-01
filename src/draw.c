#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "draw.h"
#include "user_data.h"

void _clear() {
    // Clear terminal history
    puts("\x1B[H");
    puts("\x1B[3J");

    // Clear screen
    puts("\x1B[0J");
    puts("\x1B[1J");

    // Set cursor top
    printf("\x1B[H");
}

void initDraw(Game* pGame){
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);

    printf("\x1B[0m");
    _clear();

    // Draw borders
    for (int i=0; i<p->h; i++) {
        for (int j=0; j<p->w; j++) {
            if (i<=1 || i>=p->h-2 || j<=1 || j>=p->w-2) {
                printf("🧱");
            }
            else {
                printf("  ");
            }
        }
        puts("");
    }
    for (int i=0; i<=6; i++) {
        printf("\x1B[%d;%dH", p->h-14+i, 1);
        printf("                          ");
        if (i==0 || i ==6) {
            printf("🚧🚧");
        }
        else {
            printf("    🏽🏽");
        }
    }
    printf("\x1B[%d;%dH", p->h-15, 1);
    printf("🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱");
    printf("\x1B[%d;%dH", p->h-7, 1);
    printf("🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱🧱");
}

void draw(Game* pGame, float delta_sec){
    // check
    checkGame(pGame);

    // Display FPS on top left corner
    printf("\x1B[H");
    printf("%d FPS      \n", (int)(1.0/delta_sec));
    
    // Display game
    drawUser(pGame);
}

void displayAscii(char* filename, char* msg, int time, int offset, int mode) {
    FILE* fp = fopen(filename, "r");
    char buffer[256] = {0};
    if (fp) {
        puts("\x1B[48;2;0;0;0m");
        _clear();
        for (int v=0; v<=511; v++) {
            usleep(time);
            int v2 = v>=256 ? 511-v : v;
            if (mode == 3) {
                printf("\x1B[38;2;%d;%d;%dm", (v2*228)/255, (v2*121)/255, (v2*17)/255);
            }
            else {
                printf("\x1B[38;2;%d;%d;%dm", v2/4, v2/4, v2);
            }
            int i= 0;
            while ( fgets(buffer, 256, fp) == buffer ) {
                printf("\x1B[%d;%dH", i+2, offset);
                printf("%s", buffer);
                i++;
            }
            rewind(fp);
            printf("\x1B[%d;60H", i+2);
            printf("\x1B[38;2;%d;%d;%dm", v2, v2, 0);
            printf("%s\n", msg);
        }
        fclose(fp);
    }
}
