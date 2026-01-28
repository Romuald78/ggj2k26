#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "error.h"
#include "action.h"

Action* addAction(Action* pList, char* actname, Module* pMod){
    // check
    if (actname == NULL || pMod == NULL) {
        RAGE_QUIT(30, "add Action : pointers null");
    }

    Action* pNew = malloc(sizeof(Action));
    if (pNew == NULL) {
        RAGE_QUIT(30, "add Action malloc failed");
    }

    // Copy data
    strcpy(pNew->pName, actname);
    pNew->pMod = pMod;
    // Add action first
    pNew->pNext = pList;;

    return pNew;
}