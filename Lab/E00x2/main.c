#include <ctype.h>
#include <stdio.h>

int conta(char* string, int len) {
    int i, j, k, count,sol;
    printf("%s\n", string);
    for(i = 0; string[i] != '\0'; i++) {
        for(j = 0; string[j] != '\0'; j++) {
            count = 0;
            for(k = i; k < j + 1; k++) {
                if(tolower(string[k]) == 'a' || tolower(string[k]) == 'e' || tolower(string[k]) == 'i' || tolower(string[k]) == 'o' || tolower(string[k]) == 'u') {
                    count++;
                }
            }
            if(count == 2 && j - i + 1 == len) {
                for(k = i; k < j + 1; k++) {
                    printf("%c", string[k]);
                }
                printf("\n");
                sol++;
            }
        }
    }
    return sol;
}

int main(int argc, char** argv) {

    FILE* fp;
    char string[21], nome_file[21];
    int len,sol = 0;

    printf("Inserire nome file: ");
    scanf("%s", nome_file);
    printf("\nInserire lunghezza: ");
    scanf("%d", &len);
    printf("\n");

    fp = fopen64(nome_file, "r");
    while(fscanf(fp, "%s", string) != EOF) {
        sol=sol+conta(string,len);
    }
    printf("\nSoluzione: %d\n", sol);
    return 0;
}
