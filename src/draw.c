#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "user_data.h"

void initDraw(Game* pGame){
    // Clear terminal history
    puts("\x1B[H");
    puts("\x1B[3J");
}

void draw(Game* pGame, float delta_sec){
    // check
    checkGame(pGame);
    // Clear screen
    puts("\x1B[0J");
    puts("\x1B[1J");
    printf("\x1B[H");
    // Display FPS on top left corner
    printf("%d FPS      \n", (int)(1.0/delta_sec));
    
    // Display game
    drawUser(pGame);
}
