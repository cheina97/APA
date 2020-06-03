#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ch,cv;
    int pv,ph;
    int mark,index;
} tessera;

typedef struct {
    int index;
    tessera *t;
    int rot;
    int ph,pv;
    char ch,cv;
} cella;

typedef struct {
    tessera *t;
    int l;
} tab_tessere;

typedef struct {
    cella** m;
    int h,w;
} board;

tab_tessere* loadTessere() {
    char eol;
    tab_tessere *tab=malloc(sizeof(tab_tessere));
    FILE *fp;
    fp=fopen64("tiles.txt","r");
    fscanf(fp,"%d%c",&tab->l,&eol);
    tab->t=malloc(sizeof(tessera)*tab->l);
    for(int i=0; i<tab->l; i++) {
        tab->t[i].index=i;
        fscanf(fp,"%c %d %c %d%c",&tab->t[i].ch,&tab->t[i].ph,&tab->t[i].cv,&tab->t[i].pv,&eol);
        tab->t[i].mark=0;
    }
    fclose(fp);
    return tab;
}

board* load_board(tab_tessere *t) {
    int index,rot;
    tessera *arr_t=t->t;
    board *b=malloc(sizeof(board));
    FILE *fp;
    fp=fopen64("board.txt","r");
    fscanf(fp,"%d %d",&b->h,&b->w);
    b->m=malloc(sizeof(cella*)*b->h);
    for(int i=0; i<b->h ; i++) {
        b->m[i]=malloc(sizeof(cella)*b->w);
        for(int j=0; j<b->w; j++) {
            fscanf(fp,"%d/%d",&index,&rot);
            //printf("%d/%d ",index,rot);
            b->m[i][j].index=index;
            b->m[i][j].rot=rot;
            if(index!=-1&&rot!=-1) {
                b->m[i][j].t=&arr_t[index];
                b->m[i][j].t->mark=2;
            } else b->m[i][j].t=NULL;
        }
        //printf("\n");
    }
    fclose(fp);
    return b;
}

void show_board(board *b) {
    printf("%d %d\n",b->w,b->h);
    for(int i=0; i<b->h; i++) {
        for(int j=0; j<b->w; j++) {
            printf("%+d/%+d ",b->m[i][j].index,b->m[i][j].rot);
        }
        printf("\n");
    }
}

void show_tessere(tab_tessere *t) {
    printf("%d\n",t->l);
    for(int i=0; i<t->l; i++) {
        printf("%d %c %d %c %d Mark:%d\n",t->t[i].index,t->t[i].ch,t->t[i].ph,t->t[i].cv,t->t[i].pv,t->t[i].mark);
    }
}

int contaVal(board *b) {
    int sum=0;
    cella **m=b->m;
    int *sumV=malloc(sizeof(int)*b->h);
    int *sumH=malloc(sizeof(int)*b->w);
    for(int i=0; i<b->h; i++) {
        for(int j=0; j<b->w; j++) {
            if(m[i][j].index==-1 && m[i][j].rot==-1) {
                printf("ERRORE: casella vuota (%d %d)\n",i,j);
                return -1;
            }
            if(m[i][j].rot==0) {
                m[i][j].ph=m[i][j].t->ph;
                m[i][j].ch=m[i][j].t->ch;
                m[i][j].pv=m[i][j].t->pv;
                m[i][j].cv=m[i][j].t->cv;
            } else {
                m[i][j].ph=m[i][j].t->pv;
                m[i][j].ch=m[i][j].t->cv;
                m[i][j].pv=m[i][j].t->ph;
                m[i][j].cv=m[i][j].t->ch;
            }
            if(j==0) sumH[i]=0;
            if(i==0) sumV[j]=0;
            if(j!=0 && m[i][j-1].ch!=m[i][j].ch) sumH[i]=-1;
            if(i!=0 && m[i-1][j].cv!=m[i][j].cv) sumV[j]=-1;
            if(sumV[j]!=-1) sumV[j]+=m[i][j].pv;
            if(sumH[i]!=-1) sumH[i]+=m[i][j].ph;
        }
    }
    //printf("SUM H\n");
    for(int i=0; i<b->h; i++) if(sumH[i]!=-1) {
            //printf("%d ",sumH[i]);
            sum += sumH[i];
        }
    //printf("\nSUM V\n");
    for(int i=0; i<b->w; i++) if(sumV[i]!=-1) {
            //printf("%d ",sumV[i]);
            sum += sumV[i];
        }
    //printf("\n\n");
    free(sumH);
    free(sumV);
    return sum;
}

int cnt=0;

void solR(tab_tessere *tab, board *b,int pos, int k, int start, cella** sol, int *valMax) {
    cnt++;
    //printf("\rRicorsioni %d",cnt);
    //printf("%d %d %d\n",pos,k,start);
    tessera *t=tab->t;
    int i=pos/b->w;
    int j=pos%b->w;
    //printf("%d %d\n",i,j);

    if(pos>=k) {
        int val=contaVal(b);
        //printf("%d\n",val);
        if(val>*valMax) {
            //printf("trovato\n");
            *valMax=val;
            for(int i=0; i<b->h ; i++) for(int j=0; j<b->w ; j++) {
                    sol[i][j]=b->m[i][j];
                    sol[i][j].index=sol[i][j].t->index;
                }
        }
        return;
    }

    if(b->m[i][j].t!=NULL && b->m[i][j].t->mark==2) {
        //printf("B %d\n",b->m[i][j].t->mark);
        solR(tab,b,pos+1,k,start,sol,valMax);
        return;
    }
    for(int x=0; x<tab->l ; x++) {
        //printf("A\n");
        if(t[x].mark==0) {
            //printf("hashsahjashj\n");
            t[x].mark=1;
            b->m[i][j].t=&t[x];
            b->m[i][j].rot=0;
            solR(tab,b,pos+1,k,x+1,sol,valMax);
            b->m[i][j].rot=1;
            solR(tab,b,pos+1,k,x+1,sol,valMax);
            t[x].mark=0;
        }
    }
    return;

}

cella** solF(tab_tessere *t, board *b) {
    cella **sol = malloc(sizeof(cella*)*b->h);
    for(int i=0; i<b->w; i++) sol[i]=malloc(sizeof(cella)*b->w);
    int valMax=0;
    solR(t,b,0,b->w*b->h,0,sol,&valMax);
    return sol;
}

void show_board_point(board *b){
    cella** m=b->m;
    int v=contaVal(b);
    for(int i=0; i<b->h; i++){
    	for(int j=0; j<b->w; j++){
        	printf("V:%d H:%d   ",m[i][j].pv,m[i][j].ph);
        }
        printf("\n");
    }
    printf("\nVALORE: %d\n",v);
}

int main(int argc, char **argv) {
    tab_tessere *tab_t=loadTessere();
    board *b=load_board(tab_t);
    show_board(b);
    printf("\n");
    show_tessere(tab_t);
    printf("\n");
    cella **sol=solF(tab_t,b);
    board *b2=malloc(sizeof(board));
    *b2=*b; b2->m=sol;
    show_board(b2);
    printf("\n");
    show_board_point(b2);
    

}
