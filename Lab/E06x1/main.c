#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *y;
    int imax;
} V_t;

typedef struct {
    int E_n;
    int N_n;
    int **E;
    int *check;
    V_t *V;
} graph;

graph* load() {
    graph *g=malloc(sizeof(graph));
    FILE *fp=fopen64("grafo.txt","r");
    if(fp==NULL) printf("ERROR FILE\n");
    fscanf(fp,"%d %d",&g->N_n,&g->E_n);
    g->check=calloc(g->E_n,sizeof(int));
    g->E=malloc(sizeof(int*)*g->E_n);
    g->V=malloc(sizeof(V_t)*g->N_n);
    for(int i=0; i<g->N_n ; i++) {
        g->V[i].y=malloc(sizeof(int)*g->E_n);
        g->V[i].imax=0;
    }

    for(int i=0; i<g->E_n ; i++) {
        g->E[i]=malloc(sizeof(int)*2);
        fscanf(fp,"%d %d",&g->E[i][0],&g->E[i][1]);
        g->V[g->E[i][0]].y[g->V[g->E[i][0]].imax++]=g->E[i][1];
        g->V[g->E[i][1]].y[g->V[g->E[i][1]].imax++]=g->E[i][0];
    }
    return g;
}

int verif(int *sol, graph *g, int k) {
    int i,j,l,x;
    for(i=0; i<g->E_n ; i++) g->check[i]=0;
    for(i=0; i<k; i++) {
        x=sol[i];
        for(j=0; j<g->V[x].imax ; j++) {
            for(l=0; l<g->E_n; l++) {
                if(g->E[l][0]==x && g->E[l][1]==g->V[x].y[j]) g->check[l]=1;
                if(g->E[l][1]==x && g->E[l][0]==g->V[x].y[j]) g->check[l]=1;
            }
        }
    }
    for(i=0; i<g->E_n; i++) {
        if(g->check[i]==0) return 0;
    }
    return 1;
}

void frr(int pos, int *sol, int n, int k, int start,graph *g) {
    if(pos>=k) {
        if(verif(sol,g,k)) {
            for(int i=0; i<k ; i++) printf("%d ",sol[i]);
            printf("\n");
        }
        return;
    }
    for(int i=start; i<n ; i++) {
        sol[pos]=i;
        frr(pos+1,sol,n,k,i+1,g);
    }
    return;
}

void fr(graph *g, int k) {
    int *sol=malloc(sizeof(int)*k);
    for(int i=0; i<=k ; i++) {
        frr(0,sol,g->N_n,i,0,g);
    }
    free(sol);
}

int main(int argc, char **argv) {
    graph *g=load();
    fr(g,g->N_n);
    return 0;
}
