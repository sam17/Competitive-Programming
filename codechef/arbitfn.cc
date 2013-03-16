long long int nCr(long long int n,long long int r)
{
	if(n==r) return 1;
	else if(r==0) return 1;
	else if (n==1) return 1;
	
	else return nCr(n-1,r) + nCr(n-1,r-1);
}

long long int gcd(long int a,long int b)
{
	long long int temp;
	while(b!=0)
	{
		temp=b;
		b= a%b;
		a = temp;
	}
	return a;
}
int isprime(long long int a)
{
	long long int i=2;
	if(a==1) return 0;
	long long sq = sqrt(a);
	for(;i<=sq;i++)
	{
		if(a%i==0) return 0;
	}
	return 1;
}
double fx(double x)
{
	double prevterm =1;
	double sum =1;
	double prevsum;
	double term, diff;
	int i=1;
	do
	{
		term = prevterm *x /i;
		prevsum=sum;
		sum += term;
		diff = fabs(sum-prevsum);
		prevterm = term;
		i++;
	} while(diff>0.0001);
	return sum;
}
int subseq(long long int n, long long int kk)
{
	int a[10000];
	for(long long int i=1; i<=n;i++)
	{
		a[i-1]=((i*i*i)%23)+1;
		
	}
	long long int i,j,k;
	int sum, count =0, count1=0;
	for(i=0;i<n;i++)
	{
		//printf("%d  ",a[i]);
		for(j=i+1;j<n;j++)
		{	
			sum=0;
			for(k=i;k<=j;k++) sum+=a[k];
			if(sum >kk) break;
			else if(sum==kk)
			{
				//printf("%lld %lld      ",i,j);
				count++;
				break;
			}
		}
	}
	
	return count;
}
int MAX(int a, int b, int c, int d)
{
	if(a>b) 
		{
			//printf("%d  ",c);
			return a;
		}
	//printf("%d  ",d);
	return b;
}
int profit(int a, int step)
{
	if(step>=14) return ((a%11)+1);
	return (((a%11)+1) + MAX(profit(a+1, step+1),profit(a-1, step+1),a+1,a-1));
}
int nofact(long long int n, int p)
{
	return ((n/p )+ (n /(p*p)));
}
void numberof(long long int n, int p)
{
	int count=0, count1=0;
	int nbyp = nofact(n,p);
	for (long long int i=0;i<=n;i++)
	{
		if(nofact(i,p)+nofact(n-i,p) < nbyp) count++;
		if(nofact(i,p)+nofact(n-i,p) == nbyp) count1++;
	}
	printf("%d	%d",count,count1);
}
int fib(int n)
{
	if (n==1||n==2) return 1;
	return fib(n-1)+fib(n-2);
}
