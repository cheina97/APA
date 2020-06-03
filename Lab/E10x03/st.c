#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"

struct st_s{
    int N;
    int last;
    char **val;
};

st_t* st_init(int nmax){
    st_t *st=malloc(sizeof(st_t));
    st->N=0;
    st->last=0;
    st->val=malloc(sizeof(char*)*nmax);
    for(int i=0; i<nmax; i++){
    	st->val[i]=malloc(sizeof(char)*64);
    }
    return st;
}

int st_get_int(char* x, st_t* st){
    for(int i=0; i<st->last ; i++){
    	if(strcmp(x,st->val[i])) return i;
    }
    printf("ERRORE: non trovato in ST\n");
    return -1;
}

char* st_get_char(int x, st_t* st){
    if(st->last>x){
        return st->val[x];
    }
    return "non trovato";
    
}

int st_put(char*x, st_t* st){
    int i=st->last;
    st->last++;
    strcpy(st->val[i],x);
    return i;
}