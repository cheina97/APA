#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char codice_tratta[30], partenza[30], destinazione[30];
    char data[30], ora_partenza[30], ora_arrivo[30], ritardo[30];
} tratta;
int loadTratta(tratta *t) {
    FILE *fp;
    int imax,i;
    fp=fopen64("corse.txt","r");
    fscanf(fp,"%d",&imax);
    for(i=0; i<imax; i++) {
        fscanf(fp,"%s %s %s %s %s %s %s",t[i].codice_tratta,t[i].partenza,t[i].destinazione,t[i].data,t[i].ora_partenza,t[i].ora_arrivo,t[i].ritardo);
    }
    return imax;
}
void printTratte(tratta *t, int imax) {
    int i;
    for(i=0; i<imax; i++) {
        printf("%s %s %s %s %s %s %s\n",t[i].codice_tratta,t[i].partenza,t[i].destinazione,t[i].data,t[i].ora_partenza,t[i].ora_arrivo,t[i].ritardo);
    }
    printf("\n");
}
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_fine, r_err,
} comando;
comando getCmd() {
    char s[20];
    char comandi[r_err][20]= {"r_date", "r_partenza", "r_capolinea", "r_ritardo", "r_fine"};
    printf("Inserire comando: ");
    scanf("%s",s);
    int i=0;
    for(i=0; i<r_err; i++) {
        if(strcmp(comandi[i],s)==0) return i;
    }
    return i;
}

void printtratta(tratta t) {
    printf("%s %s %s %s %s %s %s\n",t.codice_tratta,t.partenza,t.destinazione,t.data,t.ora_partenza,t.ora_arrivo,t.ritardo);
    return;
}

void orderDate(tratta *t, int imax) {
    int i,j;
    tratta tmp;
    for(i=1; i<imax; i++) {
        tmp=t[i];
        for(j=i-1; j>=0 && strcmp(t[j].data,tmp.data)>0; j--) {
            t[j+1]=t[j];
        }

        t[j+1]=tmp;
    }
}

void get_tCode(tratta* t, tratta* tCode, int imax, int *imaxCode) {
    char code[31];
    printf("Inserire codice:");
    scanf("%s",code);
    int i;
    *imaxCode=0;
    for(i=0; i<imax; i++) {
        if(strcmp(code,t[i].codice_tratta)==0) tCode[(*imaxCode)++]=t[i];
    }
    return;
}

void r_dateF(tratta *t, int imax, int* imaxDate, tratta* tDate) {
    int i,interv;
    char data1[12], data2[12],datatmp[12];
    printf("Inserire intervallo date:\n");
    printf("Data 1: "); scanf("%s",data1);
    printf("Data 2: "); scanf("%s",data2);
    printf("\n");
    if(strcmp(data1,data2)>0) {
        strcpy(datatmp,data1);
        strcpy(data1,data2);
        strcpy(data2,datatmp);
    }
    interv=0; *imaxDate =0;
    for(i=0; i<imax; i++) {
        if(strcmp(data1,t[i].data)==0) {
            interv=1;
        }
        if(strcmp(data2,t[i].data)<0) {
            interv=0;
        }
        if(interv==1) tDate[(*imaxDate)++]=t[i];
    }
    return;
}
void r_partenzaF(tratta *t, int imax) {
    char fermata[31];
    printf("Inserire fermata: ");
    scanf("%s",fermata);
    int i;
    for(i=0; i<imax; i++) if(strcmp(fermata,t[i].partenza)==0) printtratta(t[i]);
}
void r_capolineaF(tratta *t, int imax) {
    char fermata[31];
    printf("Inserire fermata: ");
    scanf("%s",fermata);
    int i;
    for(i=0; i<imax; i++) if(strcmp(fermata,t[i].destinazione)==0) printtratta(t[i]);
}
void r_ritardoF(tratta *t, int imax) {
    int i;
    tratta tDate[1000];
    int imaxDate;
    r_dateF(t,imax,&imaxDate,tDate);
    for(i=0; i<imaxDate; i++) {
        if(strcmp(tDate[i].ritardo,"0")!=0) printtratta(tDate[i]);
    }
}
int r_fineF(tratta *t, int imax) {
    int i,sum=0;
    tratta tCode[1000];
    int imaxCode;
    get_tCode(t,tCode,imax,&imaxCode);
    for(i=0; i<imaxCode; i++) {
        sum+=atoi(tCode[i].ritardo);
    }
    return sum;
}

void selezionaDati(tratta *t, int imax, comando cmd) {
    int imaxData;
    tratta tDate[1000];
    switch(cmd) {
    case r_date:
        printf("r_date\n");
        orderDate(t,imax);
        printTratte(t,imax);
        r_dateF(t,imax,&imaxData,tDate);
        printTratte(tDate,imaxData);
        break;
    case r_partenza:
        printf("r_partenza\n");
        printTratte(t,imax);    
        r_partenzaF(t,imax);
        break;
    case r_capolinea:
        printf("r_capolinea\n");
        printTratte(t,imax);
        r_capolineaF(t,imax);
        break;
    case r_ritardo:
        printf("r_ritardo\n");
        orderDate(t,imax);
        printTratte(t,imax);
        r_ritardoF(t,imax);
        break;
    case r_fine:
        printf("r_fine\n");
        printTratte(t,imax);
        printf("somma ritardi: %d",r_fineF(t,imax));
        break;
    default:
        printf("Comando non disponibile\n");
    }
}

int main(int argc, char **argv) {
    comando cmd;
    tratta t[1000];
    int imax;
    imax=loadTratta(t);
    //printTratte(t,imax);

    cmd=r_date;
    while(cmd!=r_err) {
        cmd=getCmd();
        selezionaDati(t,imax,cmd);
        printf("\n");
    }


    return 0;
}
