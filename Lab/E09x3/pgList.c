#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"
#include "pg.h"
#include "equipArray.h"
#include "invArray.h"

struct tabPg{
    link headPg;
    link tailPg;
    int nPg;
};

nodoPg_t* addNode2(pg_t pg, nodoPg_t *n, nodoPg_t **head) {
    if(n==NULL) {
        n=malloc(sizeof(nodoPg_t));
        n->pg=pg;
        n->pg.equip=malloc(sizeof(tabEquip_t));
        setInUso(n->pg.equip,0);
        n->next=NULL;
        *head=n;
        return n;
    } else {
        n->next=malloc(sizeof(nodoPg_t));
        n->next->next=NULL;
        n->next->pg=pg;
        n->next->pg.equip=malloc(sizeof(tabEquip_t));
        setInUso(n->next->pg.equip,0);
        return n->next;
    }
}

void addNode(tabPg_t t, pg_t pg) {
    t->tailPg=addNode2(pg,t->tailPg,&t->headPg);
}

tabPg_t loadPg() {
    tabPg_t tab;
    tab=malloc(sizeof(struct tabPg));
    FILE *fp;
    fp=fopen64("pg.txt","r");
    if(fp==NULL) printf("Errore file pg\n");
    pg_t pg;
    tab->nPg=0; tab->headPg=NULL; tab->tailPg=NULL;
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",pg.codice,pg.nome,pg.classe,&pg.stat.hp,&pg.stat.mp,&pg.stat.atk,&pg.stat.def,&pg.stat.mag,&pg.stat.spr)!=EOF) {
        addNode(tab,pg);
        tab->nPg++;
    }
    fclose(fp);
    return tab;
}

void addPg(tabPg_t tab) {
    printf("Inserire dati\n");
    pg_t pg;
    scanf("%s %s %d %d %d %d %d %d",pg.nome,pg.classe,&pg.stat.hp,&pg.stat.mp,&pg.stat.atk,&pg.stat.def,&pg.stat.mag,&pg.stat.spr);
    tab->nPg++;
    sprintf(pg.codice,"PG%4.4d",tab->nPg);
    addNode(tab,pg);
}

void printPg(pg_t pg) {
    printf("%s %s %s %d %d %d %d %d %d\n",pg.codice,pg.nome,pg.classe,pg.stat.hp,pg.stat.mp,pg.stat.atk,pg.stat.def,pg.stat.mag,pg.stat.spr);
}

void printPgAll(tabPg_t tab) {
    for(nodoPg_t *i=tab->headPg; i!=NULL ; i=i->next) {
        printPg(i->pg);
    }
}

link* findPg(tabPg_t tab, char *key) {
    nodoPg_t **head=&tab->headPg;
    for(nodoPg_t **i=head; *i!=NULL ; i=&(*i)->next) {
        if(strcmp(key,(*i)->pg.codice)==0) {
            return i;
        }
    }
    return NULL;
}

void delPg(link* pg) {
    if(pg==NULL) {
        printf("Non Trovato\n");
        return;
    }
    link d=*pg;
    *pg=d->next;
    printPg(d->pg);
    free(d->pg.equip);
    free(d);
}

void printPgEquip(char *name, tabPg_t tabPg) {
    link* tmp = findPg(tabPg,name);
    if(tmp==NULL) {
        printf("Non trovato\n");
        return;
    }
    pg_t* pg=&(*tmp)->pg;
    int i;
    if(getInUso(pg->equip)==0) {
        printf("VUOTO\n");
        return;
    }
    for(i=0; i<getInUso(pg->equip); i++) {
        inv_t **tmp=getInv(pg->equip);
        printItem(*(tmp[i]));
    }

}

void printEquip(tabPg_t tab) {
    char pg[51];
    printf("Inserire nome PG:") ; scanf("%s",pg);
    printPgEquip(pg,tab);
}

void getStat2(tabPg_t tab, char *key) {
    int i;
    link *lTmp = findPg(tab,key);
    if(lTmp==NULL) {
        printf("Non trovato\n");
        return;
    }
    pg_t pg=(*lTmp)->pg;
    inv_t **tmp=getInv(pg.equip);
    for(i=0; i<getInUso(pg.equip); i++) {
        stat_t s=getStat3(tmp[i]);
        pg.stat.atk+=s.atk;
        pg.stat.hp+=s.hp;
        pg.stat.mp+=s.mp;
        pg.stat.def+=s.def;
        pg.stat.spr+=s.spr;
        pg.stat.mag+=s.mag;
    }
    printPg(pg);
}

void getStat(tabPg_t tab) {
    char s[51];
    printf("Inserire codice PG:\n"); scanf("%s",s);
    getStat2(tab,s);
}

void addRm_Equip2(tabInv_t tabInv, tabPg_t tabPg, char* pgName, char* itemName) {

    link* tmp = findPg(tabPg,pgName);
    inv_t* item=findItem(tabInv,itemName);
    if(tmp==NULL || item==NULL) {
        printf("Item o PG non trovato\n");
        return;
    }
    pg_t* pg=&(*tmp)->pg;
    int cmd;
    printf("0: add      1: remove\n"); scanf("%d",&cmd);
    if(cmd==0) {
        if(getInUso(pg->equip)==8) {
            printf("Spazio terminato\n");
            return;
        }
        inv_t **tmp=getInv(pg->equip);
        tmp[getInUso(pg->equip)]=item;
        setInUso(pg->equip,getInUso(pg->equip)+1);
        return;
    } else if(cmd==1) {
        int i;
        for(i=0; i<getInUso(pg->equip); i++) {
            inv_t **tmp=getInv(pg->equip);
            if(tmp[i]==item) {
                tmp[i]=NULL;
                for(; i<getInUso(pg->equip)-1; i++) {
                    tmp[i]=tmp[i+1];
                }
                setInUso(pg->equip,getInUso(pg->equip)-1);
                return;
            }
        }
    } else {
        printf("comando non riconosciuto\n");
    }
}

void addRm_Equip(tabInv_t tabInv, tabPg_t tabPg) {
    printInvAll(tabInv);
    printf(" \n");
    char item[51],pg[51];
    printf("Inserire nome PG:") ; scanf("%s",pg);
    printf("\n");
    printPgEquip(pg,tabPg);
    printf("Inserire nome ITEM:"); scanf("%s",item);
    addRm_Equip2(tabInv,tabPg,pg,item);
}
