//
// Created by cytech on 29/01/2026.
//
#include <stdio.h>
#include "product.h"

#include <stdlib.h>
#include <string.h>

#include "error.h"

void teleportProduct(Product* p, int x0, int y0) {
    if (p != NULL) {
        p->x = x0;
        p->y = y0;
    }
}

void moveProduct(Product* p, int dx, int dy) {
    if (p != NULL) {
        p->x += dx;
        p->y += dy;
    }
}

Product* addProduct(Product* pList, char* type, int x0, int y0) {
    Product* pProd = NULL;

    pProd = malloc(sizeof(Product));
    if (pProd == NULL) {
        RAGE_QUIT(55, "Product malloc failed");
    }

    strcpy(pProd->type, type);
    pProd->x     = 2 * x0;
    pProd->y     = y0;
    pProd->pNext = pList;

    return pProd;
}
