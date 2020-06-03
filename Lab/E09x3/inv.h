#ifndef INV_H
#define INV_H

#include "stat.h"

typedef struct {
    char nome[51];
    char tipo[51];
    stat_t stat;
} inv_t;


#endif