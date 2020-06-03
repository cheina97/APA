#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 51

typedef struct {
    char codice[DIM];
    char nome[DIM];
    char cognome[DIM];
    char data[DIM];
    char via[DIM];
    char citta[DIM];
    int cap;

} Item;

typedef struct node_s node;
struct node_s {
    Item i;
    node *next;
};

void printItem(Item x) {
    printf("%s %s %s %s %s %s %d\n",x.codice,x.nome,x.cognome,x.data,x.via,x.citta,x.cap);
}

node *addNode(node *list, Item i) {
    printf("1\n");
    if(list==NULL) {
        list=malloc(sizeof(node));
        list->i=i;
        list->next=NULL;
        return list;

    }
    node *p,*tmp;
    if(strcmp(i.data,list->i.data)>0) {
        tmp=malloc(sizeof(node));
        tmp->i=i;
        tmp->next=list;
        return tmp;
    }
    printf("2\n");
    for(p=list; p->next!=NULL && p->next->next!=NULL && strcmp(i.data,p->next->i.data)<0 ; p=p->next) ;
    if(p->next!=NULL && p->next->next==NULL && strcmp(i.data,p->next->i.data)<0) {
        printf("4\n");
        tmp=malloc(sizeof(node));
        tmp->i=i;
        tmp->next=NULL;
        p->next->next=tmp;
        return list;
    }
    tmp=malloc(sizeof(node));
    tmp->i=i;
    tmp->next=p->next;
    p->next=tmp;
    return list;
}

node* loadList() {
    int i=0;
    node *list=NULL;
    Item x;
    FILE *fp;
    fp=fopen64("input.txt","r");
    if(fp==NULL) printf("File Error\n");
    char tmp[11];
    while(fscanf(fp,"%s %s %s %s %s %s %d",x.codice,x.nome,x.cognome,x.data,x.via,x.citta,&x.cap)!=EOF) {
        tmp[0]=x.data[6]; tmp[1]=x.data[7]; tmp[2]=x.data[8]; tmp[3]=x.data[9];
        tmp[4]='/'; tmp[5]=x.data[3];  tmp[6]=x.data[4];
        tmp[7]='/'; tmp[8]=x.data[0];  tmp[9]=x.data[1]; tmp[10]='\0';
        strcpy(x.data,tmp);
        list=addNode(list,x);
        i++;
    }
    fclose(fp);
    return list;
}

void printList(node *start) {
    for(node *i=start; i!=NULL ; i=i->next) {
        printItem(i->i);
    }
}

node *findByCode(node *p, char *key) {
    for(node *i=p; i!=NULL ; i=i->next) {
        if(strcmp(i->i.codice,key)==0) return i;
    }
    return NULL;
}

void addTast(node *p) {
    char tmp[11]; Item x;
    printf("Inserire:\n");
    scanf("%s %s %s %s %s %s %d",x.codice,x.nome,x.cognome,x.data,x.via,x.citta,&x.cap);
    tmp[0]=x.data[6]; tmp[1]=x.data[7]; tmp[2]=x.data[8]; tmp[3]=x.data[9];
    tmp[4]='/'; tmp[5]=x.data[3];  tmp[6]=x.data[4];
    tmp[7]='/'; tmp[8]=x.data[0];  tmp[9]=x.data[1]; tmp[10]='\0';
    strcpy(x.data,tmp);
    addNode(p,x);
}

void printFile(node *list) {
    FILE *fp; Item x;
    fp=fopen64("input.txt","w");
    for(node *i=list; i!=NULL; i=i->next) {
        x=i->i;
        fprintf(fp,"%s %s %s %s %s %s %d\n",x.codice,x.nome,x.cognome,x.data,x.via,x.citta,x.cap);
    }
    fclose(fp);
}

node* rmCode(node *list, char *key) {
    node *tmp;
    if(strcmp(list->i.codice,key)==0) {
        tmp=list->next;
        free(list);
        list=tmp;
        return list;
    }
    for(node *i=list; i->next!=NULL ; i=i->next) {
        if(strcmp(i->next->i.codice,key)==0) {
            tmp=i->next->next;
            free(i->next);
            i->next=tmp;
            return list;
        }
    }
    printf("non trovato\n");
    return list;
}



typedef enum {
    stampa, cancElem, cancInterv, aggTast, aggFile, stampFile, cerca, fine,
} Cmd;

int main(int argc, char **argv) {
    node *list=loadList();
    Cmd cmd=0;
    char s[51];
    while(cmd!=fine) {
        printf("Inserire comando: "); scanf("%d",(int *)&cmd);
        switch(cmd) {
        case stampa:
            printf("Stampa\n");
            printList(list);
            break;
        case cerca:
            printf("Ricerca codice\n");
            printf("Inserire chiave:"); scanf("%s",s);
            node *tmp=findByCode(list,s);
            printItem(tmp->i);
            break;
        case cancElem:
            printf("Inserire chiave:"); scanf("%s",s);
            list=rmCode(list,s);
            break;
        case cancInterv:
            break;
        case aggTast:
            addTast(list);
            break;
        case aggFile:

            break;
        case stampFile:
            printFile(list);
            break;
        case fine:

            break;
        default:
            printf("Comando non valido\n");
            break;
        }
        printf("\n\n");
    }

    return 0;
}
