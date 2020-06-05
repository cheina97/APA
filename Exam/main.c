#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char **argv) {
	//punto 1
	FILE* fp1=fopen(argv[1],"r");
	FILE* fp2=fopen(argv[2],"r");
	FILE* fp3=fopen(argv[3],"w");
	if(fp1==NULL || fp2==NULL || fp3==NULL) {
		printf("Errore acquisizione\n");
		return 0;
	}
	
    
	//punto 2
	graph_t *g=graph_init();
	load(fp1,g);
	
    
	//punto 3
	if(verificafile(fp2,g)){
		printf("E' un kernel\n");
	}else{
		printf("Non e' un kernel\n");
	}
	
	//punto 3
	kernelMax(g,fp3);
	
	//punto 4
	pathkernel(g);
	
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}
