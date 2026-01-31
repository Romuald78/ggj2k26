//
// Created by cytech on 29/01/2026.
//

#ifndef GGJ2K26_V3_REFACTOR_H
#define GGJ2K26_V3_REFACTOR_H

typedef struct _prod{
    int           type;
    int           x;
    int           y;
    struct _prod* pNext;
    int           toDestroy;
} Product;

void     moveProduct    (Product* p, int dx, int dy) ;
void     teleportProduct(Product* p, int x0, int y0) ;
Product* addProduct     (Product* pList, int type, int x0, int y0);
int collisionProduct(Product* pList, int x0, int y0) ;

#endif //GGJ2K26_V3_REFACTOR_H