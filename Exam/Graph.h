#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph_s graph_t;

void load(FILE *fp, graph_t *g);
int verificafile(FILE *fp, graph_t *g);
void kernelMax(graph_t *g, FILE *fp);
graph_t* graph_init();
void pathkernel(graph_t *g);

#endif