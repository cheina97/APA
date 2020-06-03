#include "Edge.h"
#include <stdio.h>

edge_t edgecreate(int v, int w, int wh){
	edge_t e; e.v=v; e.w=w; e.wh=wh;
	return e;
}