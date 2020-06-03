#include <stdio.h>
#include <stdlib.h>

#define L 20

int getMax(int* v) {
    int i, max = 0, count = 0;
    for(i = 0; i <= 20; i++) {
        if(v[i] == 0 ||i==L) {
            if(max < count)
                max = count;
            count = 0;
        } else
            count++;
    }
    return max;
}

void inputFile(int* v) {
    FILE* fp;
    fp = fopen64("input.txt", "r");
    int i = 0;
    while(fscanf(fp, "%d", &v[i]) != EOF) {
        i++;
    }
    fclose(fp);
}

void print(int* v) {
    int i;
    for(i = 0; i < L; i++) {
        printf("%d ", v[i]);
    }
    printf(" \n");
}

void printSol(int* v, int max) {
    int i, j, count = 0;
    for(i = 0; i <= L; i++) {
        if(v[i] == 0 || i == L) {
            if(count == max) {
                for(j = i - max; j < i; j++) {
                    printf("%d ", v[j]);
                }
                printf("  ");
            }
            count = 0;
        } else {
            count++;
        }
    }
}

void inputScan(int* v){
    int i;
    for(i=0; i<L; i++){
    	scanf("%d",&v[i]);
    }
}

int main(int argc, char** argv) {
    int v[L] = { 0 };
    inputFile(v);
    //inputScan(v);
    print(v);
    int max = getMax(v);
    printf("%d\n", max);
    printSol(v, max);
    return 0;
}
