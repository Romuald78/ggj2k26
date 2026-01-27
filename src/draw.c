#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "user_data.h"

void initDraw(Game* pGame){
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);


    // Clear terminal history
    puts("\x1B[H");
    puts("\x1B[3J");

    // Clear screen
    puts("\x1B[0J");
    puts("\x1B[1J");
    printf("\x1B[H");

    // Draw border
    for (int j=0; j<p->w; j++) {
        printf("🧱");
    }
    puts("");
    for (int i=1; i<p->h-1; i++) {
        printf("🧱");
        for (int j=1; j<p->w-1; j++)   {
            printf("  ");
        }
        /*
        for (int j=1; j<p->w-1 - 11; j+=11)   {
            printf("  🧭▶️ 🔌⚙️ 📦⏱️ 🚨🛠️ 📊💡");
        }
        //*/
        puts("🧱");
    }
    for (int j=0; j<p->w; j++) {
        printf("🧱");
    }
    puts("");


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
