#include <stdio.h>

int gcdR(int a, int b){
    
    if(a%b==0) return b;
    if(b%a==0) return a;
    
    if(a%2==0 && b%2==0) return 2*gcdR(a/2,b/2);
    if(a%2!=0 && b%2==0) return gcdR(a,b/2);   
    if(a%2==0 && b%2!=0) return gcdR(a/2,b);   
    if(a%2!=0 && b%2!=0) return gcdR((a-b)/2,b);
    
    return -1;
}

int main(int argc, char **argv)
{
	printf("%d",gcdR(56,16));
	return 0;
}
