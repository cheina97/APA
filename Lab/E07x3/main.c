#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************
**       data structure       **
*******************************/

typedef enum {
    list,add,del,addRmEquip,showEquip,stat,end
} cmd_t;

typedef struct {
    int hp,mp,atk,def,mag,spr;
} stat_t;

typedef struct {
    char nome[51];
    char tipo[51];
    stat_t stat;
} inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
} tabInv_t;


typedef struct {
    int inUso;
    inv_t *vettEq[8];
} tabEquip_t;

typedef struct {
    char codice[51];
    char nome[51];
    char classe[51];
    stat_t stat;
    tabEquip_t *equip;

} pg_t;

typedef struct node nodoPg_t, *link;
struct node {
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;



/********************************
**           PG part           **
********************************/

nodoPg_t* addNode2(pg_t pg, nodoPg_t *n, nodoPg_t **head) {
    if(n==NULL) {
        n=malloc(sizeof(nodoPg_t));
        n->pg=pg;
        n->pg.equip=malloc(sizeof(tabEquip_t));
        n->pg.equip->inUso=0;
        n->next=NULL;
        *head=n;
        return n;
    } else {
        n->next=malloc(sizeof(nodoPg_t));
        n->next->next=NULL;
        n->next->pg=pg;
        n->next->pg.equip=malloc(sizeof(tabEquip_t));
        n->next->pg.equip->inUso=0;
        return n->next;
    }
}

void addNode(tabPg_t *t, pg_t pg) {
    t->tailPg=addNode2(pg,t->tailPg,&t->headPg);
}

void loadPg(tabPg_t *tab) {
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
}

void addPg(tabPg_t *tab){
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

void printPgAll(tabPg_t *tab) {
    for(nodoPg_t *i=tab->headPg; i!=NULL ; i=i->next) {
        printPg(i->pg);
    }
}

link* findPg(tabPg_t *tab, char *key) {
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



/*************************
**      Item part       **
*************************/

void loadInv(tabInv_t* tab){
    FILE *fp;
    fp=fopen64("Inventario.txt","r");
    if(fp==NULL) printf("Errore inventario file\n");
    fscanf(fp,"%d",&tab->maxInv); tab->nInv=0;
    tab->vettInv=malloc(sizeof(inv_t)*tab->maxInv);
    int i=0; inv_t* v=tab->vettInv;
    while(fscanf(fp,"%s %s %d %d %d %d %d %d",v[i].nome,v[i].tipo,&v[i].stat.hp,&v[i].stat.mp,&v[i].stat.atk,&v[i].stat.def,&v[i].stat.mag,&v[i].stat.spr)!=EOF){
    	i++;
        tab->nInv++;
    }
}

void printItem(inv_t v){
    printf("%s %s %d %d %d %d %d %d \n",v.nome,v.tipo,v.stat.hp,v.stat.mp,v.stat.atk,v.stat.def,v.stat.mag,v.stat.spr);
}

void printInvAll(tabInv_t *tab){
    int i;
    inv_t *v=tab->vettInv;
    for(i=0; i<tab->nInv; i++){
    	printItem(v[i]);
    }
}

inv_t* findItem(tabInv_t *tab, char *key){
    int i;
    inv_t *v=tab->vettInv;
    for(i=0; i<tab->nInv ; i++){
    	if(strcmp(v[i].nome,key)==0){
            return v+i;
        }
    }
    return NULL;
}



/*******************************************
**        Gestione equipaggiamento        **
*******************************************/

void printPgEquip(char *name, tabPg_t *tabPg);

void addRm_Equip2(tabInv_t *tabInv, tabPg_t *tabPg, char* pgName, char* itemName){
    
    link* tmp = findPg(tabPg,pgName); 
    inv_t* item=findItem(tabInv,itemName);
    if(tmp==NULL || item==NULL){
        printf("Item o PG non trovato\n");
        return;
    }
    pg_t* pg=&(*tmp)->pg;
    int cmd;
    printf("0: add      1: remove\n"); scanf("%d",&cmd);
    if(cmd==0){
        if(pg->equip->inUso==8){
            printf("Spazio terminato\n");
            return;
        }
        pg->equip->vettEq[pg->equip->inUso]=item;
        pg->equip->inUso++;
        return;
    }else if(cmd==1){
        int i;
        for(i=0; i<pg->equip->inUso; i++){
        	if(pg->equip->vettEq[i]==item){
                pg->equip->vettEq[i]=NULL;
                for(; i<pg->equip->inUso-1; i++){
                	pg->equip->vettEq[i]=pg->equip->vettEq[i+1];
                }
                pg->equip->inUso--;
                return;
            }
        }
    }else{
        printf("comando non riconosciuto\n");
    }
}

void addRm_Equip(tabInv_t *tabInv, tabPg_t *tabPg){
    printInvAll(tabInv);
    printf(" \n");
    char item[51],pg[51];
    printf("Inserire nome PG:") ; scanf("%s",pg);
    printf("\n");
    printPgEquip(pg,tabPg);
    printf("Inserire nome ITEM:"); scanf("%s",item);
    addRm_Equip2(tabInv,tabPg,pg,item);
}

void printPgEquip(char *name, tabPg_t *tabPg){
    link* tmp = findPg(tabPg,name); 
    if(tmp==NULL){
        printf("Non trovato\n");
        return;
    }
    pg_t* pg=&(*tmp)->pg;
    int i;
    if(pg->equip->inUso==0){
        printf("VUOTO\n");
        return;
    }
    for(i=0; i<pg->equip->inUso; i++){
    	printItem(*(pg->equip->vettEq[i]));
    }
    
}

void printEquip(tabPg_t *tab){
    char pg[51];
    printf("Inserire nome PG:") ; scanf("%s",pg);
    printPgEquip(pg,tab);
}

void getStat2(tabPg_t *tab, char *key){
    int i;
    link *lTmp = findPg(tab,key);
    if(lTmp==NULL){
        printf("Non trovato\n");
        return;
    }
    pg_t pg=(*lTmp)->pg;
    for(i=0; i<pg.equip->inUso; i++){
    	pg.stat.atk+=pg.equip->vettEq[i]->stat.atk;
    	pg.stat.hp+=pg.equip->vettEq[i]->stat.hp;
    	pg.stat.mp+=pg.equip->vettEq[i]->stat.mp;
    	pg.stat.def+=pg.equip->vettEq[i]->stat.def;
    	pg.stat.spr+=pg.equip->vettEq[i]->stat.spr;
    	pg.stat.mag+=pg.equip->vettEq[i]->stat.mag;
    }
    printPg(pg);
}

void getStat(tabPg_t *tab){
    char s[51];
    printf("Inserire codice PG:\n"); scanf("%s",s);
    getStat2(tab,s);
}


int main(int argc, char **argv) {
    char s[51];
    tabInv_t *tabInv=calloc(sizeof(tabInv_t),1);
    tabPg_t *tabPg=calloc(sizeof(tabPg_t),1);
    loadPg(tabPg);
    loadInv(tabInv);
    cmd_t cmd=list; int n;
    while(cmd!=end) {
        printf("Inserire comando: ");
        scanf("%d",&n);
        cmd=n;
        switch(cmd) {
        case list:
            printPgAll(tabPg);
            break;
        case add:
            addPg(tabPg);
            break;
        case del:
            printf("Inserire codice \n"); scanf("%s",s);
            delPg(findPg(tabPg,s));
            break;
        case addRmEquip:
            addRm_Equip(tabInv,tabPg);
            break;
        case showEquip:
            printEquip(tabPg);
            break;
        case stat:
            getStat(tabPg);
            break;
        case end:
            exit(0);
            break;
        default:
            printf("Comando inesistente\n");
            break;
        }
        printf("\n");
    }
    return 0;
}
