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
            if(m[i][j]==1 && (m[i-1][j]==0||i==0) && (m[i][j-1]==0||j==0)) {
                for(i2=i ; i2<imax && m[i2][j]!=0; i2++) m[i2][j]=-1;
                for(j2=j ; j2<jmax && m[i][j2]!=0; j2++) m[i][j2]=-1;
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

int riconosciRegione(int imax, int jmax, int m[50][50], int i, int j, int* h, int* w) {
    int i2,j2;
    if(m[i][j]==1 && (i==0||m[i-1][j]==0) && (j==0||m[i][j-1]==0)) {
        for(i2=i ; i2<imax && m[i2][j]!=0; i2++); //m[i2][j]=-1;
        for(j2=j ; j2<jmax && m[i][j2]!=0; j2++);//m[i][j2]=-1;
        printf("%d-%d\n",i2,i);
        *h=i2-i; *w=j2-j; //A=H*W;
        //if(Amax<A) {
        //    Amax=A;
        //    rA.a=A; rA.h=H; rA.w=W;
        //    rA.i=i; rA.j=j;
        //}
        //if(Hmax<H) {
        //    Hmax=H ;
        //    rH.a=A; rH.h=H; rH.w=W;
        //    rH.i=i; rH.j=j;
        //}
        //if(Wmax<W) {
        //    Wmax=W;
        //    rW.a=A; rW.h=H; rW.w=W;
        //    rW.i=i; rW.j=j;
        //}
        return 1;
    }
    //r.A=rA; r.H=rH; r.W=rW;
    return 0;
}

void printResult(result r) {
    printf("estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r.i,r.j,r.w,r.h,r.a);
}

int main(int argc, char **argv) {
    result r;
    int m[IMAX][JMAX],imax,jmax,i,j;
    loadmatrix(m,&imax,&jmax);
    printMatrixNum(m,imax,jmax);
    for(i=0; i<imax; i++) {
        for(j=0; j<jmax; j++) {
            if(riconosciRegione(imax, jmax, m,  i,  j,  &r.h,  &r.w)){
                r.a=(r.h)*(r.w); r.i=i; r.j=j; 
                printResult(r);
            }
        }
    }
    return 0;
}
