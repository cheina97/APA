#ifndef ST_H
#define ST_H

typedef struct {
	char nome[21];
	int index;
}node_t;

typedef struct st_s st_t;

st_t* st_init(int x);
node_t stget(st_t *st, char *key);
int stput(st_t *st, node_t n);
node_t itemsetvoid();
int stsize(st_t *st);
char *stgetName(st_t *st, int i);

#endif