#include <stdio.h>
#include <ctype.h>

#define limit 10
 
typedef struct{
    char sol[limit][26];
    int pos[limit];
    char w[6];
    int imax;
}Word;

typedef struct{
    int imax;
    Word word[20];
}sequenze;

void loadSeq(sequenze *s){
    int i;
    FILE *fp;
    fp=fopen64("sequenze.txt","r");
    fscanf(fp,"%d",&s->imax);
    for(i=0; i<s->imax; i++){
    	fscanf(fp,"%s",s->word[i].w);
        s->word[i].imax=0;
    }
    return;
}

void printSeq(sequenze s){
    int i;
    for(i=0; i<s.imax; i++){
    	printf("%s\n",s.word[i].w);
    }
}

void verify(char *buff, int start, int end, sequenze* s, int pos){
    int i,j,k,l,check;
    for(i=0; i<s->imax; i++){
        if(s->word[i].imax==limit) continue;
    	for(j=start; j<=end; j++){
        	if(tolower(buff[j])==tolower(s->word[i].w[0])){
                check=1;
                for(k=0;s->word[i].w[k]!='\0';k++) if(tolower(s->word[i].w[k])!=tolower(buff[j+k])) check=0;
                if(check==1){
                    s->word[i].pos[s->word[i].imax]=pos;
                    for(l=0; l+start<=end; l++)s->word[i].sol[s->word[i].imax][l]=buff[start+l];
                    s->word[i].sol[s->word[i].imax][l]='\0';
                    s->word[i].imax++;
                    j=end;
                }
            }
        }
    }
    return;
}

int trovaParole(char* buff, sequenze* s,int pos){
    int i,start,end;
    for(i=0; buff[i]!='\0'; i++){
    	if((i==0||ispunct(buff[i-1])||isblank(buff[i-1]))&&isalpha(buff[i])){
            start=i;
        }
        if((ispunct(buff[i+1])||isblank(buff[i+1])||buff[i+1]=='\n')&&isalpha(buff[i])){
            end=i;
            //printf("%d %d\n",start,end);
            printf("%d %d | ",start,end);
            verify(buff,start,end,s,++pos);
        }
        
    }
    return pos ;
    
}

void printResult(sequenze *s){
    int i,j;
    for(i=0; i<s->imax; i++){
    	printf("%s: ",s->word[i].w);
        for(j=0; j<s->word[i].imax ; j++){
        	printf("%s (pos %d) | ",s->word[i].sol[j],s->word[i].pos[j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
	sequenze s;
    int pos=0;
    loadSeq(&s);
    printSeq(s);
    printf("\n");
    FILE *fp;
    fp=fopen64("testo.txt","r");
    char buff[210];
    while(fgets(buff,210,fp)){
        pos=trovaParole(buff,&s,pos);
        printf(" pos:%d\n",pos);
    }
    printf("\n\n");
    printResult(&s);
	return 0;
}
