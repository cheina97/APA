#ifndef EQUIPARR
#define EQUIPARR

#include "inv.h"

typedef struct tab *tabEquip_t;

void setInUso(tabEquip_t t, int v);
int getInUso(tabEquip_t t);
inv_t **getInv(tabEquip_t t);
stat_t getStat3(inv_t *x);

#endif