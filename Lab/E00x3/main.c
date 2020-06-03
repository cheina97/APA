#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 30

void initValue(int* N, int* v) {
    int i;
    printf("Inserire N : ");
    scanf("%d", N);
    if(*N>30)
        *N = 30;
    printf("Inserire valori di V (%d) :\n", *N);
    for(i=0; i<*N; i++) {
        scanf("%d", &v[i]);
    }
}

void printV(int* v, int N) {
    int i;
    for(i=0; i<N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void R(int* v, int l) {
    int i, tmp1, tmp2;
    for(i=0; i<l-1; i++) {
        if(i==0) tmp1 = v[i];
        else tmp1 = tmp2;
        tmp2 = v[i+1];
        v[i+1] = tmp1;
    }
    v[0]=tmp2;
}

void L(int* v, int l) {
    int i, tmp1, tmp2;
    for(i=l-1; i>0 ; i--) {
        if(i==l-1) tmp1 = v[i];
        else tmp1 = tmp2;
        tmp2 = v[i-1];
        v[i-1] = tmp1;
    }
    v[l-1]=tmp2;
}

void ruota(int v[maxN], int N, int P, int dir) {
    if(P >= N) {
        printf("P troppo alto\n");
        return;
    }
    if(dir!=-1&&dir!=1){
        printf("dir errato\n");
    }
    int i;
    for(i=0; i<P; i++) {
        if(dir==1) L(v,N);
        if(dir==-1) R(v,N);
    }
}

int main(int argc, char** argv) {
    int v[maxN] = {0}, N;
    initValue(&N, v);
    printV(v, N);
    printf(" \n");

    int dir,p=1;
    while(p!=0) {
        printf("Inserire P : ");
        scanf("%d",&p);
        printf("Inserire dir : ");
        scanf("%d",&dir);
        ruota(v,N,p,dir);
        printV(v,N);
        printf("\n");
    }

    return 0;
}
