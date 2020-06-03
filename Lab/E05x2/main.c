#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int N; int B;
}ritorno;

ritorno separa(int **mat, int nr, int nc, int **vB, int **vN) {
    int i=0, j=0, kB=0, kN=0, B=((nc-(nc/2))*(nr-(nr/2)))+((nr/2)*(nc/2)), N=(nc*nr)-B;
    *vB=malloc(sizeof(int)*B); *vN=malloc(sizeof(int)*N);
    for(i=0; i<nr ; i++){
    	for(j=0; j<nc; j++){
        	if((i%2==0 && j%2==0)||(i%2!=0 && j%2!=0)) (*vB)[kB++]=mat[i][j];
            else (*vN)[kN++]=mat[i][j];
        }
    }
    ritorno r; r.B=B; r.N=N;
    return r;
}

int **malloc2dr(int *imax, int *jmax) {
    int **m;
    FILE *fp;
    fp=fopen64("input.txt","r");
    fscanf(fp,"%d %d",imax,jmax);
    m=malloc(sizeof(int*)*(*imax));
    for(int i=0; i<*imax ; i++) {
        m[i]=malloc(sizeof(int)*(*jmax));
        for(int j=0; j<*jmax ; j++) {
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    fclose(fp);
    return m;
}

void malloc2dp(int*** m, int *imax, int *jmax) {
    FILE *fp;
    fp=fopen64("input.txt","r");
    fscanf(fp,"%d %d",imax,jmax);
    *m=malloc(sizeof(int*)*(*imax));
    for(int i=0; i<*imax ; i++) {
        (*m)[i]=malloc(sizeof(int)*(*jmax));
        for(int j=0; j<*jmax ; j++) {
            fscanf(fp,"%d",&(*m)[i][j]);
        }
    }
    fclose(fp);
}

void printm(int **m, int imax, int jmax) {
    for(int i=0; i<imax ; i++) {
        for(int j=0; j<jmax ; j++) {
            printf("%d ",m[i][j]);
        }
        printf(" \n");
    }
}

int main(int argc, char **argv) {
    int imax,jmax,imax2,jmax2;
    int **m2=NULL, **m;
    m=malloc2dr(&imax,&jmax);
    malloc2dp(&m2,&imax2,&jmax2);
    printm(m,imax,jmax);
    printf("\n");
    printm(m2,imax2,jmax2);
    int *vB=NULL, *vN=NULL;
    ritorno r=separa(m,imax,jmax,&vB,&vN);
    
    printf("\nBIANCO:\n");
    for(int i=0; i<r.B ; i++){
    	printf("%d ",vB[i]);
    }
    printf("\n\n");
    
    printf("BIANCO:\n");
    for(int i=0; i<r.N ; i++){
    	printf("%d ",vN[i]);
    }
    printf("\n\n");

    
    return 0;
}
