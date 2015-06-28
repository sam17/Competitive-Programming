/*
	Problem Name = Chef and Polygons
	Problem Link = http://www.codechef.com/JUNE15/problems/CHPLGNS
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

class Point2D
{
	long long int x,y;

public:

	Point2D(int a,int b)
	{
		x = a;
		y = b;
	}

	Point2D& operator=(const Point2D& p)
	{
		x = p.x;
		y = p.y;
	}
	
};

struct Polygon
{
	vector<Point2D> points;
};

int main()
{
	int n,t,m,x,y;
	Point2D pt;
	scanf("%d",&t);
	REP(i,t)
	{
		scanf("%d",&n);
		vector<Polygon>polygonSet(n);
		REP(j,n)
		{
			scanf("%d",&m);
			REP(k,m)
			{
				scanf("%d %d",&x,&y);
				
			}
		}
	}

	

	return 0;
}
