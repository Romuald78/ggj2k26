#ifndef DRAW_H
#define DRAW_H

#include "game.h"

void initDraw(Game* pGame);
void draw(Game* p, float delta_sec);

void displayAscii(char* filename, char* msg, int time, int offset, int mode);

#endif

