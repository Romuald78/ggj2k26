//
// Created by cytech on 29/01/2026.
//
#include <stdio.h>
#include "product.h"

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "module.h"

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

    pProd = calloc(1, sizeof(Product));
    if (pProd == NULL) {
        RAGE_QUIT(55, "Product malloc failed");
    }

    pProd->type  = type;
    pProd->x     = 2 * x0;
    pProd->y     = y0;
    pProd->pNext = pList;

    return pProd;
}


int collisionProduct(Product* pList, int x0, int y0) {
    if (pList == NULL) {
        return 0;
    }
    Product* pProd = pList;
    while (pProd != NULL) {
        if (pProd->x == x0 && pProd->y == y0) {
            // found already a product
            return 1;
        }
        pProd = pProd->pNext;
    }
    return 0;
}