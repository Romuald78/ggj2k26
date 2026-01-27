//
// Created by cytech on 26/01/2026.
//

#ifndef GGJ2K26_V3_MODULE_H
#define GGJ2K26_V3_MODULE_H

enum {
    MOD_RIGHT,
    MOD_DOWN,
    MOD_LEFT,
    MOD_UP
};

typedef struct _mod Module;

typedef void (*ModuleUpdate)(Module* p);
typedef void (*ModuleDraw)  (Module* p);

struct _mod{
    char         pName[32];   // Module name
    ModuleUpdate pUpdate;
    ModuleDraw   pDraw;
    int          x0;
    int          y0;
    int          size;
    int          orient;    // orient = 0:right / 1:down / 2:left / 3:top
    int          speed;
    int          time;
    int          running;
    struct _mod* pNext;
};

Module* createModule(char* name, ModuleUpdate upd, ModuleDraw draw);

#endif //GGJ2K26_V3_MODULE_H