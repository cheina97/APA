#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isBigEndian(char* mostSig, char* lessSig) {
    if(mostSig<lessSig) return 1;
    else return 0;
}

int main(int argc, char **argv) {
    char v[2];
    //unsigned char n[17] ;
    int bigEndian=isBigEndian(&v[0],&v[1]);
    //float x;
    printf("Most sig: %p\nLess sig: %p\n",&v[0],&v[1]);
    printf("Big Endian = %d\n\n",bigEndian);

    float af;
    double ad;
    long double ald;
    int byteFloat=(int)sizeof(af);
    int byteDouble=(int)sizeof(ad);
    int byteLongDouble=(int)sizeof(ald);
    printf("Dimensione float: %d\n",byteFloat);
    printf("Dimensione double: %d\n",byteDouble);
    printf("Dimensione long double: %d\n",byteLongDouble);

    unsigned char floatBit[4],doubleBit[8],*longDoubleBit;
    longDoubleBit=malloc(byteLongDouble);
    
    float n;

    printf("Inserire un valore numerico: ");
    scanf("%f",&n);
    int g=0;
    while((n*pow(10,g)-(int)(n*pow(10,g)))!=0){
        printf("%f-%d=%f\n",n*pow(10,g), (int)(n*pow(10,g)),n*pow(10,g)-(int)(n*pow(10,g)));
        system("pause");
        g++;
    }
    printf("%d\n",g);
    
    exit(0);
    
    
    //int i;

    /*while((int)x/g!=0) {
        //printf("%d \n",(int)x/g);
        g=g*2;
    }
    g=g/2; printf("Grado max: %d\n",g);


    x=abs(x);
    for(i=0; i<16 && g!=0 ; i++) {
        if((int)x/g!=0) {
            n[i]='1';
            x=x-(float)g;
        } else {
            n[i]='0';
        }
        g=g/2;
    }
    n[i]='\0';

    //for(i=0; i<16; i++) {
    //    printf("%c ",n[i]);
    //}
    printf("Numero in binario: %s",n);
    printf("\n");*/



}
