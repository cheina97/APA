#include <stdio.h>

#define nMax 20
#define mMax 20

void input(int m[][mMax], char* fileName, int* imax, int* jmax) {
    FILE *fp;
    fp=fopen64(fileName,"r");
    int i,j;
    fscanf(fp,"%d %d",imax,jmax);
    for(i=0; i<*imax; i++) {
        for(j=0; j<*jmax; j++) {
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    fclose(fp);
}

void printm(int m[][mMax], int imax, int jmax) {
    int i,j;
    for(i=0; i<imax ; i++) {
        for(j=0; j<jmax; j++) {
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf(" \n");
}

int getMaxIndex(int* v, int imax) {
    int i,max=v[0],maxIndex=0;
    for(i=0; i<imax; i++) {
        if(v[i]>max) {
            max=v[i];
            maxIndex=i;
        }
    }
    return maxIndex;
}

int main(int argc, char **argv) {
    int m[nMax][mMax], r[nMax]= {0}, imax, jmax, i, j, sol;
    input(m,"input.txt",&imax,&jmax);
    printm(m, imax, jmax);

    for(j=0; j<jmax ; j++) {
        for(i=0; i<imax; i++) {
            r[i]+=m[i][j];
        }
        sol=getMaxIndex(r,imax);
        printf("Giornata %d\nCapolista: %d, punti: %d\n\n",j+1,sol,r[sol]);
    }

    return 0;
}
