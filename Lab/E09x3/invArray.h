#ifndef INVARR_H
#define INVARR_H

#include <inv.h>

typedef struct tabInv *tabInv_t;

tabInv_t loadInv();
void printItem(inv_t v);
void setStat(int pv,int atk, int def, int mp, int spr, int mag, inv_t *x);
inv_t* findItem(tabInv_t tab, char *key);
void printInvAll(tabInv_t tab);

#endif