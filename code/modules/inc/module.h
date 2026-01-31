//
// Created by cytech on 26/01/2026.
//

#ifndef GGJ2K26_V3_MODULE_H
#define GGJ2K26_V3_MODULE_H

enum {
    MOD_RIGHT,
    MOD_DOWN,
    MOD_LEFT,
    MOD_UP,
    MOD_NB_DIRS
};

enum {
    MOD_BASE_1  = 1,
    MOD_BASE_2
};

typedef struct _mod Module;

typedef void (*ModuleUpdate)(Module* p, void* pData);
typedef void (*ModuleDraw)  (Module* p);
typedef void (*ModuleAction)(Module* p, char* actname);

struct _mod{
    char         pName[32];     // Module name
    ModuleUpdate pUpdate;       // Module UPDATE function (called during update phase)
    ModuleDraw   pDraw;         // Module DRAW   function (called during update phase)
    ModuleAction pAction;       // Module ACTION function (called during event  phase)

    int          x0;            // ref position
    int          y0;
    int          size;          // size of the module (can be a radius, a length, a perimeter, ...)
    int          orient;        // orient = 0:right / 1:down / 2:left / 3:top
    int          powerId;       // powerid in order to connect modules: powerid of power supplies shall be unique

    float        speed;         // speed process
    float        time;          // local time counter
    int          time_step;     // local time step, increased when time is more than speed
    int          running;       // is it running or is it stopped

    int          load_elt;      // 1 means type 1 (1 color) / 2 means 2 colors
    int          load_speed;    // speed of output : speed will be modified according to this integer value
    struct _mod* pNext;
};

Module* createModule(char* name,
                     int x0, int y0, int size, int orient, float speed,
                     ModuleUpdate upd, ModuleDraw draw, ModuleAction action);

#endif //GGJ2K26_V3_MODULE_H