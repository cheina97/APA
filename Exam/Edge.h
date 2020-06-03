#ifndef EDGE_H
#define EDGE_H

typedef struct{
	int v,w,wh;
}edge_t;

edge_t edgecreate(int v, int w, int wh);

#endif