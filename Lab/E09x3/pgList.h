#ifndef PGLIST_H
#define PGLIST_H

#include "pg.h"
#include "invArray.h"


typedef struct tabPg *tabPg_t;

tabPg_t loadPg();
void printPg(pg_t pg);
void addPg(tabPg_t tab);
void delPg(link* pg);
void addRm_Equip(tabInv_t tabInv, tabPg_t tabPg);
void printEquip(tabPg_t tab);
void getStat(tabPg_t tab);
link* findPg(tabPg_t tab, char *key);
void printPgAll(tabPg_t tab);


#endif