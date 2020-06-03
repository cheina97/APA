#include <stdio.h>
#include <string.h>

typedef struct matrice {
    int imax;
    int jmax;
    int m[30][30];
} matrice;

matrice inpuFile(matrice m) {
    FILE *fp;
    int i,j;
    char file[21];
    printf("Inserire nome file: ");
    scanf("%s",file);
    fp=fopen64(file,"r");
    fscanf(fp,"%d %d",&m.imax,&m.jmax);

    for(i=0; i<m.imax; i++) {
        for(j=0; j<m.jmax; j++) {
            fscanf(fp,"%d",&m.m[i][j]);
        }
    }

    return m;
}

void printm(matrice m) {
    int i,j;
    for(i=0; i<m.imax ; i++) {
        for(j=0; j<m.jmax; j++) {
            printf("%d ",m.m[i][j]);
        }
        printf("\n");
    }
}

int control(char* sel, int index, char* dir, int pos, matrice m) {
    if(strcmp(sel,"fine")!=0 && strcmp(sel,"colonna")!=0 && strcmp(sel,"riga")!=0) return 1;
    if(strcmp(sel,"colonna")==0 && strcmp(dir,"su")!=0 && strcmp(dir,"giu")!=0) return 1;
    if(strcmp(sel,"riga")==0  && strcmp(dir,"destra")!=0 && strcmp(dir,"sinistra")!=0) return 1;
    if(strcmp(sel,"colonna")==0 && index>=m.jmax) return 1;
    if(strcmp(sel,"riga")==0  && index>=m.imax) return 1;
    return 0;
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

void D(matrice *m, int index) {
    int i, l=m->imax,tmp1, tmp2;
    for(i=0; i<l-1; i++) {
        if(i==0) tmp1 = m->m[i][index];
        else tmp1 = tmp2;
        tmp2 = m->m[i+1][index];
        m->m[i+1][index] = tmp1;
    }
    m->m[0][index]=tmp2;
}

void U(matrice *m, int index) {
    int i,l=m->imax,tmp1, tmp2;
    for(i=l-1; i>0 ; i--) {
        if(i==l-1) tmp1 = m->m[i][index];
        else tmp1 = tmp2;
        tmp2 = m->m[i-1][index];
        m->m[i-1][index] = tmp1;
    }
    m->m[l-1][index]=tmp2;
}

void ruota(matrice *m, char* sel, int index, char* dir, int pos) {
    int i,j;
    if(strcmp(sel,"riga")==0) {
        if(strcmp(dir,"destra")==0) {
            for(i=0; i<pos ; i++) R(m->m[index], m->jmax);
        }
        if(strcmp(dir,"sinistra")==0) {
            for(i=0; i<pos ; i++) L(m->m[index], m->jmax);
        }
    }
    if(strcmp(sel,"colonna")==0) {
        if(strcmp(dir,"su")==0) {
            for(i=0; i<pos ; i++){
                U(m, index);
            }

        }
        if(strcmp(dir,"giu")==0) {
            for(i=0; i<pos ; i++){
                D(m, index);
            }
        }
    }
}

int main(int argc, char **argv) {
    char sel[101],dir[101];
    int index,pos;

    matrice m;
    m=inpuFile(m);
    printm(m);

    printf("\nInserire <selettore> <indice> <direzione> <posizioni> :\n");
    scanf("%s %d %s %d",sel,&index,dir,&pos);
    while(stricmp(sel,"fine")!=0) {
        if(control(sel,index,dir,pos,m)==0) {
            ruota(&m,sel,index,dir,pos);
            printm(m);
        } else printf("Input errato\n");
        printf("\n\n");
        printf("Inserire <selettore> <indice> <direzione> <posizioni> :\n");
        scanf("%s %d %s %d",sel,&index,dir,&pos);
    }
    return 0;
}
