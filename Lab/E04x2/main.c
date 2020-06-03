#include <stdio.h>
#include <stdlib.h>

int majorityR(int *a, int l, int r, int *max) {
    if(l==r) { // torno indietro
        *max=a[l];
        return 1;
    }
    int m=((r-l)/2)+l, maxL, maxR,maxLcnt, maxRcnt;
    maxLcnt = majorityR(a, l,m,&maxL);
    maxRcnt = majorityR(a, m+1,r, &maxR);
    
    for(int i=l; i<=m ; i++) if(maxR==a[i]) maxRcnt++;
    for(int i=m+1; i<=r ; i++) if(maxL==a[i]) maxLcnt++;
    
    if(maxLcnt>=maxRcnt) {
        *max=maxL;
        return maxLcnt;
    } else {
        *max=maxR;
        return maxRcnt;
    }
    

}

int majority(int *a, int N) {
    int maxCnt,max;
    maxCnt=majorityR(a,0,N-1,&max);
    printf("MAX %d CNT %d ",max,maxCnt);
    if(maxCnt>=N/2) return max;
    else return -1;
}


int main(int argc, char **argv) {
    int *v,l,i=0;
    FILE *fp;
    fp=fopen64("input.txt","r");
    fscanf(fp,"%d",&l);
    v=malloc(sizeof(int)*l);
    while(fscanf(fp,"%d",&v[i++])!=EOF);

    for(i=0; i<l; i++) {
        printf("%d ",v[i]);
    }
    printf("\n");
    
    majority(v,l);


    return 0;
}
