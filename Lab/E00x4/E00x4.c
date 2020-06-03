#include <stdio.h>
#include <stdlib.h>

void printm(int m[][20], int iend, int jen, int istart, int jstart) {
    int i,j;
    for(i=istart; i<iend ; i++) {
        for(j=jstart; j<jen; j++) {
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }

}

int main(int argc, char **argv) {
    char file[21];
    int m[20][20],i,j,imax,jmax,min,n;

    printf("Inserire nome file : ");
    scanf("%s",file);
    FILE *fp;
    fp=fopen64(file,"r");
    fscanf(fp,"%d %d",&imax,&jmax);

    for(i=0; i<imax ; i++) {
        for(j=0; j<jmax; j++) {
            fscanf(fp,"%d",&m[i][j]);
        }
    }

    printm(m,imax,jmax,0,0);

    if(imax<jmax) min=imax;
    else min=jmax;

    printf("%d %d %d\n",imax,jmax,min);

    printf("Inserire numero tra 1 e %d : ",min);
    scanf("%d",&n);
    while(n>0 && n<=min) {
        for(i=0; i<imax-n+1 ; i++) {
            for(j=0; j<jmax-n+1 ; j++) {
                printm(m,i+n,j+n,i,j);
                printf("\n");
            }
        }
        printf("Inserire numero tra 1 e %d : ",min);
        scanf("%d",&n);
    }
}
