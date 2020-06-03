#include <stdio.h>
#include <stdlib.h>

int nr=0;

typedef enum {
    zaff, smer, rubi, topa,
} pietre;

typedef struct {
    int z,r,s,t;
    int val_z,val_r,val_s,val_t;
    int mark[4];
    int insert[4];
    int max;
    int max_rip;
    int *sol;
    int val;
    int find;
} data_t;

data_t* load() {
    data_t *d=malloc(sizeof(data_t));
    FILE *fp;
    fp=fopen64("input.txt","r");
    if(fp==NULL) {printf("error file\n"); return NULL;}
    fscanf(fp,"%d %d %d %d",&d->z, &d->s, &d->r, &d->t);
    fscanf(fp,"%d %d %d %d",&d->val_z, &d->val_s, &d->val_r, &d->val_t);
    fscanf(fp,"%d",&d->max_rip);
    printf("Z:%d V:%d\nS:%d V:%d\nR:%d V:%d\nT:%d V:%d\n\n",d->z, d->val_z, d->s, d->val_s, d->r, d->val_r, d->t, d->val_t);
    d->mark[0]=d->z; d->mark[1]=d->s; d->mark[2]=d->r; d->mark[3]=d->t;
    d->insert[0]=0; d->insert[1]=0; d->insert[2]=0; d->insert[3]=0;
    d->max=d->mark[0]+d->mark[1]+d->mark[2]+d->mark[3];
    d->val=0;
    d->sol=malloc(sizeof(int)*d->max);
    d->find=0;
    printf("Max_rip: %d\n\n",d->max_rip);
    return d;;
}

void printCollana(int *sol, int imax){
    for(int i=0; i<imax ; i++){
    	if(sol[i]==zaff) printf("Z ");
    	if(sol[i]==topa) printf("T ");
    	if(sol[i]==smer) printf("S ");
    	if(sol[i]==rubi) printf("R ");
    }
    printf("\n");
}

int getVal(data_t *d){
    return  d->insert[topa]*d->val_t + d->insert[rubi]*d->val_r +
            d->insert[smer]*d->val_s + d->insert[zaff]*d->val_z;
}

void fr(int *sol, data_t *d, int k, int pos, int last_n, int last_val) {
    nr++;
    printf("\rRicorsioni: %d",nr);
    if(last_n>d->max_rip){
        return;
    }
    
    if(d->insert[smer]+(k-pos)<d->insert[zaff]) return;
    
    if(pos>=2) {
        int prev=sol[pos-2],next=sol[pos-1];
        if(prev==zaff && (next!=zaff && next!=rubi)) return;
        if(prev==smer && (next!=smer && next!=topa)) return;
        if(prev==rubi && (next!=smer && next!=topa)) return;
        if(prev==topa && (next!=zaff && next!=rubi)) return;
    }
    if(pos==k) {
        int prev=sol[k-1],next=sol[0];
        if(prev==zaff && (next!=zaff && next!=rubi)) return;
        if(prev==smer && (next!=smer && next!=topa)) return;
        if(prev==rubi && (next!=smer && next!=topa)) return;
        if(prev==topa && (next!=zaff && next!=rubi)) return;
    }

    if(pos>=k) {
        if(getVal(d)>d->val){
            d->val=getVal(d);
            for(int i=0; i<k ; i++) d->sol[i]=sol[i];
            d->find=1;
        } 
        return;
    }
    for(int i=0; i<4 ; i++) {
        if(d->mark[i]<=0) continue;
        d->mark[i]--;
        d->insert[i]++;
        sol[pos]=i;
        if(last_val!=i) fr(sol,d,k,pos+1,1,i);
        else fr(sol,d,k,pos+1,last_n+1,i);
        d->mark[i]++;
        d->insert[i]--;
    }
    return;
}

void creaCollana(data_t *d) {
    int k=d->max;
    int *sol=malloc(sizeof(int)*d->max);
    while(k>0) {
        fr(sol,d,k,0,0,-1);
        if(d->find==1){
            printf("\n\nSoluzione:\n");
            printCollana(d->sol,k);
            printf("Val: %d\n",d->val);
            return;
        }
        k--;
    }
}

int main(int argc, char **argv) {
    data_t *d=load();
    creaCollana(d);
    
    return 0;
}
