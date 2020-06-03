#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct dizionario {
    char originale[30][201];
    char compresso[30][201];
    int l;
} dizionario;

void encode(int start, int len, char* string, dizionario d) {
    int i,j,k,p=0;
    char mark=219;
    for(i=start; i<len; i++) {
        for(j=0; j<d.l; j++) {
            for(k=0; d.originale[j][k]!='\0' && !isblank(string[i+k]) && string[i+k]!='\0' ; k++) {
                if(d.originale[j][k]!=string[i+k]) break;
            }
            if(k==strlen(d.originale[j])) {
                for(k=0; d.originale[j][k]!='\0' ; k++) {
                    string[i+k]=mark;
                }
                p=0;
                for(k=start; k<len ; k++) {
                    if(string[k]==mark) {
                        if(p==0) {p=1; printf("%s",d.compresso[j]);}
                    } else printf("%c",string[k]);
                }
                printf(" ");
                return;
            }
        }
    }
    for(k=start; k<len; k++) printf("%c",string[k]);
    printf(" ");
}

void initDizionario(dizionario* d) {
    FILE *fp;
    fp=fopen64("dizionario.txt","r");
    int i=0;
    while(fscanf(fp,"%s %s",d->compresso[i],d->originale[i])!=EOF) {
        i++;
    }
    d->l=i;
}

void printd(dizionario d) {
    int i;
    for(i=0; i<d.l ; i++) {
        printf("%s %s\n",d.compresso[i],d.originale[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i,l;

    dizionario d;
    initDizionario(&d);
    printd(d);

    FILE *fp;
    char buffer[201];
    fp=fopen64("sorgente.txt","r");
    while(fgets(buffer,201,fp)!=NULL) {
        //printf("%s",buffer);
        for(i=0; buffer[i]!='\0' && buffer[i]!='\n';) {
            if(i==0) {
                for(l=i; buffer[l]!='\n' && buffer[l]!='\0' && !isblank(buffer[l]) ; l++);
                encode(i,l,buffer,d);
                i=l;
            } else {
                if(isblank(buffer[i])) {
                    for(l=1; buffer[i+l]!='\n' && buffer[i+l]!='\0' && !isblank(buffer[i+l]) ; l++);
                    encode(i+1,l+i,buffer,d);
                    i=i+l;
                }
            }
        }
        printf("\n");

    }
    return 0;
}
