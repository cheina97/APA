#include <stdio.h>
#include <stdlib.h>
#include "equipArray.h"


struct tab {
    int inUso;
    inv_t *vettEq[8];
};

void setInUso(tabEquip_t t, int v){
    t->inUso=v;
}

int getInUso(tabEquip_t t){
    return t->inUso;
}

inv_t **getInv(tabEquip_t t){
    return t->vettEq;
}

stat_t getStat3(inv_t *x){
    return x->stat;
}






