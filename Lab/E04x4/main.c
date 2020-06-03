#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sortedData=0;
int sortedCode=0;
int sortedStart=0;
int sortedEnd=0;

void setSorted(int *sortValue) {
    sortedData=0;
    sortedCode=0;
    sortedStart=0;
    sortedEnd=0;
    *sortValue=1;
}

typedef struct {
    char codice_tratta[30], partenza[30], destinazione[30];
    char data[30], ora_partenza[30], ora_arrivo[30], ritardo[30];
} tratta;

int load(tratta *t) {
    FILE *fp;
    int imax,i;
    fp=fopen64("corse.txt","r");
    fscanf(fp,"%d",&imax);
    for(i=0; i<imax; i++) {
        fscanf(fp,"%s %s %s %s %s %s %s",t[i].codice_tratta,t[i].partenza,t[i].destinazione,t[i].data,t[i].ora_partenza,t[i].ora_arrivo,t[i].ritardo);
    }
    return imax;
}

void printLogF(tratta *t, int imax) {
    int i;
    for(i=0; i<imax; i++) {
        printf("%s %s %s %s %s %s %s\n",t[i].codice_tratta,t[i].partenza,t[i].destinazione,t[i].data,t[i].ora_partenza,t[i].ora_arrivo,t[i].ritardo);
    }
    printf("\n");
}

typedef enum {
    printLog, sortData, sortCode, sortStart, sortEnd, findByStart, exitProg, r_err
} comando;

comando getCmd() {
    char s[20];
    char comandi[r_err][20]= {"printLog", "sortData", "sortCode", "sortStart", "sortEnd", "findByStart", "exitProg"};
    printf("Inserire comando: ");
    scanf("%s",s);
    int i=0;
    for(i=0; i<r_err; i++) {
        if(strcmp(comandi[i],s)==0) return i;
    }
    return i;
}

void printItem(tratta t) {
    printf("%s %s %s %s %s %s %s\n",t.codice_tratta,t.partenza,t.destinazione,t.data,t.ora_partenza,t.ora_arrivo,t.ritardo);
    return;
}

void sortDataF(tratta *t, int imax) {
    setSorted(&sortedData);
    int i,j;
    tratta tmp;
    for(i=1; i<imax; i++) {
        tmp=t[i];
        for(j=i-1; j>=0 && (strcmp(t[j].data,tmp.data)>0 || (strcmp(t[j].ora_partenza,tmp.ora_partenza)>0 && strcmp(t[j].data,tmp.data)==0) || (strcmp(t[j].ora_arrivo,tmp.ora_arrivo)>0 && strcmp(t[j].ora_partenza,tmp.ora_partenza)==0 && strcmp(t[j].data,tmp.data)==0)); j--) {
            t[j+1]=t[j];
        }
        t[j+1]=tmp;
    }
    if(sortedData==1) printf("Sorted Succesfully\n");
}

void sortCodeF(tratta *t, int imax) {
    setSorted(&sortedCode);
    int i,j;
    tratta tmp;
    for(i=1; i<imax; i++) {
        tmp=t[i];
        for(j=i-1; j>=0 && strcmp(t[j].codice_tratta,tmp.codice_tratta)>=0; j--) {
            t[j+1]=t[j];
        }
        t[j+1]=tmp;
    }
    if(sortedCode==1) printf("Sorted Succesfully\n");
}

void sortStartF(tratta *t, int imax) {
    setSorted(&sortedStart);
    int i,j;
    tratta tmp;
    for(i=1; i<imax; i++) {
        tmp=t[i];
        for(j=i-1; j>=0 && strcmp(t[j].partenza,tmp.partenza)>=0; j--) {
            t[j+1]=t[j];
        }
        t[j+1]=tmp;
    }
    if(sortedStart==1) printf("Sorted Succesfully\n");
}

void sortEndF(tratta *t, int imax) {
    setSorted(&sortedEnd);
    int i,j;
    tratta tmp;
    for(i=1; i<imax; i++) {
        tmp=t[i];
        for(j=i-1; j>=0 && strcmp(t[j].destinazione,tmp.destinazione)>=0; j--) {
            t[j+1]=t[j];
        }
        t[j+1]=tmp;
    }
    if(sortedEnd==1) printf("Sorted Succesfully\n");
}

int findByStartF(tratta *t, char *key, int imax) {
    if(sortedStart) {
        printf("DICOTOMICA\n");
        int m,l=0,r=imax-1;
        m=((r-l)/2)+l;
        while(l<=r) {
            if(strcmp(t[m].partenza,key)==0) return m;
            if(strcmp(t[m].partenza,key)>0) r=m-1;
            if(strcmp(t[m].partenza,key)<0) l=m+1;
            m=((r-l)/2)+l;
        }
        return -1;
    } else {
        printf("ITERATIVA\n");
        for(int i=0; i<imax ; i++) {
            if(strcmp(t[i].partenza,key)==0) return i;
        }
        return -1;
    }
}

void selezionaDati(tratta *t, int imax, comando cmd) {
    switch(cmd) {
    case printLog:
        printf("printLog\n");
        printLogF(t,imax);
        break;
    case sortData:
        printf("sortData\n");
        sortDataF(t,imax);
        break;
    case sortCode:
        printf("sortCode\n");
        sortCodeF(t,imax);
        break;
    case sortEnd:
        printf("sortEnd\n");
        sortEndF(t,imax);
        break;
    case sortStart:
        printf("sortStart\n");
        sortStartF(t,imax);
        break;
    case findByStart:
        printf("FindByStart\n");
        char key[512];
        printf("Cerca: \n"); scanf("%s",key);
        int r=findByStartF(t,key,imax);
        if(r!=-1) printItem(t[r]);
        else printf("Not found\n");
        break;
    case exitProg:
        exit(0);
        break;
    default:
        printf("Comando non disponibile\n");
    }
}

int main(int argc, char **argv) {
    comando cmd;
    tratta t[1000];
    int imax;
    imax=load(t);

    cmd=printLog;
    while(cmd!=exitProg) {
        cmd=getCmd();
        selezionaDati(t,imax,cmd);
        printf("\n");
    }


    return 0;
}
