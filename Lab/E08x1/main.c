#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start,end,d;
} item;

int *solFinal;
int dMax,l;

int prun(int pos, item *v, int *sol) {
    int j=pos-1;
    for(int i=0; i<pos-1 ; i++) {
        if (((v[sol[i]].end<=v[sol[j]].start && v[sol[i]].start<v[sol[j]].end) ||
        (v[sol[j]].end<=v[sol[i]].start && v[sol[j]].start<v[sol[i]].end))!=1) return 1;
        //if((v[sol[i]].start<v[sol[j]].end) && (v[sol[j]].start<v[sol[i]].start)) return 1;
        //if((v[sol[j]].start<v[sol[i]].end) && (v[sol[i]].start<v[sol[j]].start)) return 1;
    }
    return 0;
}

int getDtot(item *v, int *sol, int k){
    int d=0;
    for(int i=0; i<k ; i++){
    	d+=v[sol[i]].d;
    }
    return d;
}

void fr(item *v, int k, int pos, int *sol, int n, int start) {
    if(prun(pos,v,sol)) return;
    
    if(pos>=k) {
        //for(int i=0; i<k; i++) printf("%d ",sol[i]);
        //printf(" \n");
        int d=getDtot(v,sol,k);
        //printf("%d\n",k);
        if(d>=dMax){
            dMax=d;
            l=k;
            for(int i=0; i<k ; i++) solFinal[i]=sol[i];
        }
        return;
    }
    for(int i=start; i<n ; i++) {
        sol[pos]=i;
        fr(v,k,pos+1,sol,n,i+1);
    }
    return;
}

void  activeSel(int N, item *v) {
    int i;
    solFinal=malloc(sizeof(int)*(N));
    for(i=0; i<N+1; i++) {
        int *sol=malloc(sizeof(int)*i);
        fr(v,i,0,sol,N,0);
        free(sol);
    }
}

int main(int argc, char **argv) {
    int n,i;
    FILE *fp;
    fp=fopen64("input.txt","r");
    if(fp==NULL) printf("Errore file\n");
    fscanf(fp,"%d",&n);
    item *v=malloc(sizeof(item)*n);
    for(i=0; i<n ; i++) {
        fscanf(fp,"%d %d",&v[i].start, &v[i].end);
        printf("start: %d   end: %d\n",v[i].start,v[i].end);
        v[i].d=v[i].end-v[i].start;
    }

    activeSel(n,v);
    
    for(i=0; i<l; i++){
    	printf("(%d,%d) ",v[solFinal[i]].start, v[solFinal[i]].end);
    }
    return 0;
}
