#include <stdio.h>
#include <stdlib.h>

int combR(int *navi, int n_moli, int n_navi, int l, int *sol, int pos, int *sum_molo) {
	if(pos>=n_navi) {
		return 1;
	}
	for(int i=0; i<n_moli; i++) {
		if(navi[pos]+sum_molo[i]<=l) {
			sum_molo[i]+=navi[pos];
			sol[pos]=i;
			if(combR(navi,n_moli,n_navi,l,sol,pos+1,sum_molo)==1) return 1;
			sum_molo[i]-=navi[pos];
		}
	}
	return 0;
}

int* comb(int *navi, int l, int n_moli, int n_navi, int *l_sol) {
	int sum_moli[n_moli];
	for(int i=0; i<n_moli; i++) sum_moli[i]=0;
	int *sol=malloc(sizeof(int)*n_navi);
	int result=0;
	for(int j=1; j<n_moli && result==0 ; j++){
		*l_sol=j;
		result=combR(navi,j,n_navi,l,sol,0,sum_moli);
	}
	if(result==1) return sol;
	else return NULL;
}



int main(int argc, char **argv) {
	int n_navi,l,n_mol;
	int *navi;
	FILE  *fp=fopen("input.txt","r");
	if(fp==NULL) printf("ERRORE: file not found\n");
	fscanf(fp,"navi %d\n",&n_navi);
	fscanf(fp,"num_moli %d\n",&n_mol);
	fscanf(fp,"lun %d\n",&l);
	navi=malloc(sizeof(int)*n_navi);
	for(int j=0; j<n_navi; j++){
		fscanf(fp,"%d",&navi[j]);
	}
	
	for(int i=0; i<n_navi; i++){
		printf("%d\n",navi[i]);
	}
	printf(" \n");
	
	int l_sol=0;
	int *sol=comb(navi,l,n_mol,n_navi,&l_sol);
	
	for(int i=0; i<n_navi ;i++){
		printf("%d\n",sol[i]);
	}
	return 0;
}
