#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invArray.h"
#include "pgList.h"

typedef enum {
    list,add,del,addRmEquip,showEquip,stat,end
} cmd_t;

int main(int argc, char **argv) {
    char s[51];
    tabInv_t tabInv=loadInv();
    tabPg_t tabPg=loadPg();
    cmd_t cmd=list; int n;
    while(cmd!=end) {
        printf("Inserire comando: ");
        scanf("%d",&n);
        cmd=n;
        switch(cmd) {
        case list:
            printPgAll(tabPg);
            break;
        case add:
            addPg(tabPg);
            break;
        case del:
            printf("Inserire codice \n"); scanf("%s",s);
            delPg(findPg(tabPg,s));
            break;
        case addRmEquip:
            addRm_Equip(tabInv,tabPg);
            break;
        case showEquip:
            printEquip(tabPg);
            break;
        case stat:
            getStat(tabPg);
            break;
        case end:
            exit(0);
            break;
        default:
            printf("Comando inesistente\n");
            break;
        }
        printf("\n");
    }
    return 0;
}
