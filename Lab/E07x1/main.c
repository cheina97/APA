#include <stdio.h>
#include <stdlib.h>

typedef enum {
    zaff, smer, rubi, topa,
} pietre;

typedef struct {
    int z,r,s,t;
    int match[4];
    int max;
} data_t;

data_t* load() {
    data_t *d=malloc(sizeof(data_t));
    FILE *fp;
    fp=fopen64("input.txt","r");
    if(fp==NULL) {printf("error file\n"); return NULL;}
    fscanf(fp,"%d %d %d %d",&d->z, &d->s, &d->r, &d->t);
    printf("Z:%d S:%d R:%d T:%d\n",d->z, d->s, d->r, d->t);
    d->match[0]=d->z; d->match[1]=d->s; d->match[2]=d->r; d->match[3]=d->t;
    d->max=d->z+d->r+d->s+d->t;

    return d;
}

void printCollana(int *sol, int imax){
    for(int i=0; i<imax ; i++){
    	if(sol[i]==zaff) printf("Z ");
    	if(sol[i]==topa) printf("T ");
    	if(sol[i]==smer) printf("S ");
    	if(sol[i]==rubi) printf("R ");
    }
    printf("\n");
}

void fr(int *sol, data_t *d, int k, int pos) {

    if(pos>=2) {
        int prev=sol[pos-2],next=sol[pos-1];
        if(prev==zaff && (next!=zaff && next!=rubi)) return;
        if(prev==smer && (next!=smer && next!=topa)) return;
        if(prev==rubi && (next!=smer && next!=topa)) return;
        if(prev==topa && (next!=zaff && next!=rubi)) return;
    }
    if(pos==k) {
        int prev=sol[k-1],next=sol[0];
        if(prev==zaff && (next!=zaff && next!=rubi)) return;
        if(prev==smer && (next!=smer && next!=topa)) return;
        if(prev==rubi && (next!=smer && next!=topa)) return;
        if(prev==topa && (next!=zaff && next!=rubi)) return;
    }

    if(pos>=k) {
        printCollana(sol,k);
        system("pause");
        return;
    }
    for(int i=0; i<4 ; i++) {
        if(d->match[i]<=0) continue;
        d->match[i]--;
        sol[pos]=i;
        fr(sol,d,k,pos+1);
        d->match[i]++;
    }
    return;
}

void creaCollana(data_t *d) {
    int k=d->max;
    int *sol=malloc(sizeof(int)*d->max);
    while(k>0) {
        fr(sol,d,k,0);
        k--;
    }
}

int main(int argc, char **argv) {
    data_t *d=load();
    creaCollana(d);
    return 0;
}
