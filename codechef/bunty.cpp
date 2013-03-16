#include <stdio.h>
#define MULTI 100000

int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	double prob1,prob2;
	prob1= (double)((double)m/(double)(m+n));
	prob2= (double)((double)n/(double)(m+n));
	int a,b;
	a=prob1*MULTI;
	b=prob2*MULTI;
	printf("%d %d",a,b);
	return 0;


}
