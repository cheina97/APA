#ifndef PG_H
#define PG_H

#include "stat.h"
#include "equipArray.h"

typedef struct node nodoPg_t, *link;

typedef struct {
    char codice[51];
    char nome[51];
    char classe[51];
    stat_t stat;
    tabEquip_t equip;

} pg_t;

struct node {
    pg_t pg;
    link next;
};



#endif