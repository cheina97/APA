#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <invArray.h>
#include <inv.h>


struct tabInv {
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

tabInv_t loadInv(){
    tabInv_t tab;
    tab=malloc(sizeof(struct tabInv));
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
    return tab;
}

void printItem(inv_t v){
    printf("%s %s %d %d %d %d %d %d \n",v.nome,v.tipo,v.stat.hp,v.stat.mp,v.stat.atk,v.stat.def,v.stat.mag,v.stat.spr);
}

void printInvAll(tabInv_t tab){
    int i;
    inv_t *v=tab->vettInv;
    for(i=0; i<tab->nInv; i++){
    	printItem(v[i]);
    }
}

inv_t* findItem(tabInv_t tab, char *key){
    int i;
    inv_t *v=tab->vettInv;
    for(i=0; i<tab->nInv ; i++){
    	if(strcmp(v[i].nome,key)==0){
            return v+i;
        }
    }
    return NULL;
}
