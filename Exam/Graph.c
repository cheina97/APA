#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Edge.h"
#include "ST.h"

struct graph_s {
	int V;
	int ** adj;
	int ** adj_inv;
	st_t *st;
};

graph_t* graph_init(){
	 graph_t *g=malloc(sizeof(graph_t));
	 return g;
}

int** malloc2d(int h) {
	int **mat;
	mat=malloc(sizeof(int*)*h);
	for(int i=0; i<h; i++) {
		mat[i]=malloc(sizeof(int)*h);
		for(int j=0; j<h; j++) {
			mat[i][j]=0;
		}
	}
	return mat;
}

void graphinsert(int **adj, edge_t e) {
	adj[e.v][e.w]=e.wh;
}

void load(FILE *fp, graph_t *g) {
	int tmp=0;
	char id1[21],id2[21];
	while(fscanf(fp,"%s %s",id1,id2)!= EOF) tmp++;
	rewind(fp);
	g->adj=malloc2d(tmp*2);
	g->adj_inv=malloc2d(tmp*2);
	g->st=st_init(tmp*2);
	for(int i=0; i<tmp; i++) {
		fscanf(fp,"%s %s",id1,id2);
		node_t n1,n2;
		n1=stget(g->st,id1);
		n2=stget(g->st,id2);
		if(n1.index==itemsetvoid().index) {
			strcpy(n1.nome,id1);
			n1.index=stput(g->st,n1);
		}
		if(n2.index==itemsetvoid().index) {
			strcpy(n2.nome,id2);
			n2.index=stput(g->st,n2);
		}
		g->V=stsize(g->st);
		graphinsert(g->adj,edgecreate(n1.index,n2.index,1));
		graphinsert(g->adj_inv,edgecreate(n2.index,n1.index,1));
	}
}

int iskernel(int *v, graph_t* g) {
	for(int i=0; i<g->V; i++) {
		if(v[i]==1) {
			for(int j=0; j<g->V; j++) {
				if(g->adj[i][j]!=0) {
					if(v[j]==1) return 0;
				}
			}
		}
		if(v[i]==0) {
			int conta=0;
			for(int j=0; j<g->V; j++) {
				if(g->adj_inv[i][j]!=0) {
					if(v[j]==1) conta++;
				}
			}
			if(conta<1) return 0;
		}
	}
	return 1;
}

int conta1(int* v, int l) {
	int count =0;
	for(int i=0; i<l; i++) {
		if(v[i]==1)count++;
	}
	return count;
}

int MAX=0, *solmax;

void combR(graph_t *g, int *sol, int pos) {
	if(pos>=g->V) {
		if(iskernel(sol,g)) {
			int n=conta1(sol,g->V);
			if(n>MAX) {
				MAX=n;
				for(int i=0; i<g->V; i++) solmax[i]=sol[i];
			}
		}
		return;
	}
	sol[pos]=1;
	combR(g,sol,pos+1);
	sol[pos]=0;
	combR(g,sol,pos+1);
}

void kernelMax(graph_t *g, FILE *fp){
	int sol[g->V];
	for(int i=0; i<g->V; i++) sol[i]=0;
	solmax=malloc(sizeof(int)*g->V);
	combR(g,sol,0);
	for(int i=0; i<g->V; i++){
		if(solmax[i]==1) fprintf(fp,"%s\n",stgetName(g->st,i));
	}
	
}

int max3=0, lmax;

void pathkernelR(int *kernel, graph_t *g, int max2, int V, int *d, int l){
	for(int W=0; W<g->V; W++){
		if(g->adj[V][W]!=0 && d[W]==0){
			d[W]=1;
			l+=g->adj[V][W];
			if(kernel[W]==1) max2++;
			pathkernelR(kernel,g,max2,W,d,l);
			d[W]=0;
			l-=g->adj[V][W];
			if(kernel[W]==1) max2--;
		}
	}
	if(max2>max3){
		max3=max2;
		lmax=l;
	}
}

void pathkernel(graph_t *g){
	if (solmax==NULL) kernelMax(g,NULL);
	int d[g->V]; 
	for(int i=0; i<g->V; i++) d[i]=0;
	int max2;
	for(int i=0; i<g->V; i++){
		if(solmax[i]==1) max2=1;
		else max2=0;
		d[i]=1;
		pathkernelR(solmax,g,max2,i,d,0);
	}
	printf("LUNGHEZZA: %d\n",lmax);
	printf("NUMERO KERNEL: %d\n",max3);
}

int verificafile(FILE *fp, graph_t *g){
	char tmp[21];
	int d[g->V];
	for(int i=0; i<g->V; i++) d[i]=0;
	while(fscanf(fp,"%s",tmp)!=EOF){
		node_t n=stget(g->st,tmp);
		d[n.index]=1;
	}
	return iskernel(d,g);
}
