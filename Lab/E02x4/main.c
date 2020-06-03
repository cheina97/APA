#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int* v;
}line;

void insertionSort(int *v, int imax) {
    int tmp,i,j;
    for(i=1; i<imax; i++) {
        tmp=v[i];
        for(j=i-1; j>=0 && v[j]>tmp ; j--) {
            v[j+1]=v[j];
        }
        v[j+1]=tmp;
    }
}

void selectionSort(int *v, int imax){
    int i,j,tmp,min;
    for(i=0; i<imax ; i++){
    	min=i;
        for(j=i+1; j<imax ; j++){
        	if(v[j]<v[min]) min=j;
        }
        tmp=v[min];
        v[min]=v[i];
        v[i]=tmp;
    }
}

void shellSort(int *v, int l){
    int h=1,i,j,tmp;
    while(h<l/3) h=h*3+1;
    while(h>=1){
        for(i=h; i<l ; i++){
        	tmp=v[i];
            for(j=i-h; j>=0 && v[j]>tmp ; j--){
            	v[j+h]=v[j];
            }
            v[j+h]=tmp;
        }
        h=h/3;
    }
}

line readLine(FILE* fp){
    line riga;
    int i,x;
    x=fscanf(fp,"%d",&riga.l);
    if(x==EOF){
        riga.l=-1;
        return riga;
    }
    riga.v=malloc(sizeof(int)*riga.l);
    for(i=0; i<riga.l; i++){
    	fscanf(fp,"%d",&riga.v[i]);
    }
    return riga;
}

void printV(line riga){
    int i;
    for(i=0; i<riga.l; i++){
    	printf("%d ",riga.v[i]);
    }
    printf("\n\n");
}

int main(int argc, char **argv) {
    FILE *fp;
    int junk;
    line riga;
    fp=fopen64("sort.txt","r");
    if(fp==NULL) printf("Errore apertura file\n");
    fscanf(fp,"%d",&junk);
    while(1){
        riga=readLine(fp);
        if(riga.l==-1) break;
        shellSort(riga.v,riga.l);
        printV(riga);
    }
    fclose(fp);
    
    return 0;
}
