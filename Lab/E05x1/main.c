#include <stdio.h>
#include <stdlib.h>

int count;

typedef struct {
    char **brano;
    int imax;
} amico;

amico* loadData(int *imax) {
    amico *amici; int j=0;
    FILE *fp;
    fp=fopen64("brani.txt","r");
    fscanf(fp,"%d",imax);
    amici = malloc(sizeof(amico)*(*imax));
    while(fscanf(fp,"%d",&amici[j].imax)!=EOF) {
        amici[j].brano=malloc(sizeof(char*)*amici[j].imax);
        for(int i=0; i<amici[j].imax ; i++) {
            amici[j].brano[i]=malloc(256);
            fscanf(fp,"%s",amici[j].brano[i]);
        }
        j++;
    }
    return amici;
}

void printAmici(amico *amici, int imax) {
    printf("%d\n",imax);
    for(int i=0; i<imax ; i++) {
        for(int j=0; j<amici[i].imax ; j++) printf("%s\n",amici[i].brano[j]);
        printf(" \n");
    }
}

void printPlayList(amico *amici, int *sol, int k){
    for(int i=0; i<k ; i++) printf("%s\n",amici[i].brano[sol[i]]);
    printf("\n");
}

void comboR(amico *amici, int *sol, int pos, int k, int n){
    if(n>=k){
        count++;
        printPlayList(amici,sol,k);
        return;
    }
    for(int i=pos; i<amici[n].imax ; i++){
    	sol[n]=i;
        comboR(amici,sol,pos,k,n+1);
    }
    return;
}

void combo(amico *amici, int imax){
    int *sol=malloc(sizeof(int)*imax);
    comboR(amici,sol,0,imax,0);
    free(sol);
}

int main(int argc, char **argv) {
    
    ///*caricamento*///
    int imax;
    amico *amici=loadData(&imax);
    //printAmici(amici,imax);
    
    ///*combinazioni*///
    
    combo(amici,imax);
    printf("COMBINAZIONI: %d\n",count);
    return 0;
}
