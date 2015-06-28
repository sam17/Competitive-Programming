/*
	Problem Name = The Real Probability
	Problem Link = http://www.codechef.com/problems/MPROB
	User = soumyadeep9
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <bitset>
#include <time.h>
#include <cmath>
#include <vector>
#include <string>
#include <set>

using namespace std;

#define MOD 1000000007LL
#define LL long long
#define LD long double
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(x) ((x)<0?-(x):(x))

#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define FORR(i,n) for(int i=(n);i>=0;i--)

const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;

#define SIZE 100001

int main()
{
	int t;
	long long a,b,c;
	scanf("%d",&t);
	REP(i,t)
	{
		double p;
		scanf("%lld %lld %lld",&a,&b,&c);
		if (a==0 && b ==0)
			p = 1.0;
		else if (a==0 && b!=0)
		{
			if(b<c)
				p=1.0;
			else p = double(c/b);
		}
		else if (b==0 && a!=0)
		{
			if(a<c)
				p=1.0;
			else p = double(c/a);
		}
		else if(c>b && c>a && c<(a+b))
	   		p = double(1.0 - ((0.5*(a+b-c)*(a+b-c))/((double)(a*b))));
		else if (c<=a && c<=b)
			p = double(c*c/(2.0*a*b));
		else if (b<=c && c<a)
			p = double((c*c)-((c-b)*(c-b)))/(2.0*a*b);
		else if (a<c && c<b)
			p = double((c*c)-((c-a)*(c-a)))/(2.0*a*b);
		else if((a+b)<=c)
			p = 1.0;
		
		printf("%lf\n",p);
	}




	return 0;
}
