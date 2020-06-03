#include <stdio.h>

#define IMAX 50
#define JMAX 50

typedef struct {
    int i,j,h,w,a;
} result;

typedef struct {
    result A,H,W;
} results;

void loadmatrix(int m[50][50], int* imax, int* jmax) {
    FILE *fp;
    fp=fopen64("input.txt","r");
    fscanf(fp,"%d %d",imax,jmax);
    int i,j;
    for(i=0; i<*imax ; i++) {
        for(j=0; j<*jmax; j++) {
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    fclose(fp);
}

void printMatrix(int m[50][50], int imax, int jmax) {
    int i,j;
    for(i=0; i<imax; i++) {
        for(j=0; j<jmax; j++) {
            if(m[i][j]==1) printf("%c",219);
            else printf(" ");
        }
        printf("\n");
    }
}

void printMatrixNum(int m[50][50], int imax, int jmax) {
    int i,j;
    for(i=0; i<imax; i++) {
        for(j=0; j<jmax; j++) {
            printf("%d",m[i][j]);
        }
        printf("\n");
    }
}

results findR(int imax, int jmax, int m[50][50]) {
    result rA,rH,rW;
    results r;
    int i,j,i2,j2,A,Amax=0,H,Hmax=0,W,Wmax=0;
    for(i=0; i<imax ; i++) {
        for(j=0; j<jmax; j++) {
            if(m[i][j]==1 && (m[i-1][j]==0||i==0) && (m[i][j-1]==0||j==0) ) {
                for(i2=i ;i2<imax && m[i2][j]!=0; i2++) m[i2][j]=-1;
                for(j2=j ;j2<jmax && m[i][j2]!=0; j2++) m[i][j2]=-1;
                H=i2-i; W=j2-j; A=H*W;
                if(Amax<A) {
                    Amax=A;
                    rA.a=A; rA.h=H; rA.w=W;
                    rA.i=i; rA.j=j;
                }
                if(Hmax<H) {
                    Hmax=H ;
                    rH.a=A; rH.h=H; rH.w=W;
                    rH.i=i; rH.j=j;
                }
                if(Wmax<W) {
                    Wmax=W;
                    rW.a=A; rW.h=H; rW.w=W;
                    rW.i=i; rW.j=j;
                }
            }
        }
    }
    r.A=rA; r.H=rH; r.W=rW;
    return r;
}

void printResult(results r) {
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r.W.i,r.W.j,r.W.w,r.W.h,r.W.a);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r.A.i,r.A.j,r.A.w,r.A.h,r.A.a);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r.H.i,r.H.j,r.H.w,r.H.h,r.H.a);
}

int main(int argc, char **argv) {
    results r;
    int m[IMAX][JMAX],imax,jmax;
    loadmatrix(m,&imax,&jmax);
    printMatrixNum(m,imax,jmax);
    r=findR(imax,jmax,m);
    printResult(r);
    return 0;
}
