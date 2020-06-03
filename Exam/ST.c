#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

struct st_s{
	node_t *v;
	int N,M;
};

st_t* st_init(int x){
	st_t* st=malloc(sizeof(st_t));
	st->N=x;
	st->M=0;
	st->v=malloc(sizeof(node_t)*x);
	return st;
}

node_t *n_null=NULL;

node_t itemsetvoid(){
	if(n_null==NULL){
		n_null=malloc(sizeof(node_t));
		n_null->index=-1; 
		strcpy(n_null->nome,"nullo");
	}
	return *n_null;
}

node_t stget(st_t *st, char *key){
	for(int i=0; i<st->M; i++){
		if(strcmp(key,st->v[i].nome)==0) return st->v[i];
	}
	return itemsetvoid();
}

int stput(st_t *st, node_t n){
	n.index=st->M;
	st->v[st->M++]=n;
	return n.index;
}

int stsize(st_t *st){
	return st->M;
}

char *stgetName(st_t *st, int i){
	return st->v[i].nome;
}
