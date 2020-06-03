#ifndef ST_H
#define ST_H

typedef struct st_s st_t;

st_t* st_init(int nmax);
int st_get_int(char* x, st_t* st);
char* st_get_char(int x, st_t* st);
int st_put(char*x, st_t* st);

#endif