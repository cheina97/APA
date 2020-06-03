#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "st.h"

//LIST

typedef struct node_s node_t, *link;
struct node_s {
	link next;
	int index;
};

typedef struct {
	link z,head,tail;
} list_t;

list_t* list_init() {
	list_t *list=malloc(sizeof(list_t));
	list->z=malloc(sizeof(node_t));
	list->head=list->z; list->tail=list->z;
	return list;
}

node_t* node_new(int i, link next) {
	node_t *node=malloc(sizeof(node_t));
	node->next=next; node->index=i;
	return node;
}

void list_add(list_t* list, int i) {
	if(list->head==list->z) {
		list->head=node_new(i,list->z);
		list->tail=list->head;
		return;
	}
	list->tail->next=node_new(i,list->z);
	list->tail=list->tail->next;
}

void list_print(list_t *list) {
	for(link i=list->head; i!=list->z ; i=i->next) {
		printf("%d ",i->index);
	}
	printf("\n");
}

void list_prova() {
	list_t* list=list_init();
	list_add(list,1);
	list_add(list,2);
	list_add(list,3);
	list_add(list,4);
	list_print(list);
	list_prova();
}

//EDGE

typedef struct {
	int v,w,wt;
} edge_t;

//GRAPH

struct graph_s {
	int V;
	int E;
	edge_t edge;
	st_t *st;
	list_t *adj_list;
	int **adj_mat;
};

graph_t* graph_init(char *f) {
	FILE *fp; char trash[64]; int v=0;
	fp=fopen64(f,"r");
	while(fscanf(fp,"%s %s %s %s %s",trash,trash,trash,trash,trash)!=EOF) v++;
	v++;
	graph_t* graph=malloc(sizeof(graph_t));
	graph->adj_list=list_init();
	graph->st=st_init(v);
	fclose(fp);
	fp=fopen64(f,"r");
	while(fscanf(fp,"%s %s %s %s %s",)!=EOF) {

	}
	return graph;
}

//MATRIX

void matrix_init(int n, graph_t *g) {
	g->adj_mat=malloc(sizeof(int*)*n);
	for(int i=0; i<n ; i++) {
		g->adj_mat[i]=malloc(sizeof(int)*n);
		for(int j=0; j<n; j++) {
			g->adj_mat[i][j]=0;
		}
	}
	return;
}
