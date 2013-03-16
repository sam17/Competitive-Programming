#include <stdio.h>
#define SIZE 5000

#define MIN(a,b) (((a)<=(b))?(a):(b))

void merge(long long int a[],int beg,int end,int mid)
{
	long long int ar[SIZE];
	
	int i=beg,j=mid,l=beg;
	for(i=beg;i<mid;i++)
		ar[i]=a[i];
	for(j=mid;j<end;j++)
		ar[j]=a[j];
	
	i=beg;
	j=mid;
	l=beg;
	
	while((i<mid)&&(j<end))
	{
		if(ar[i]<ar[j])
		{
			a[l]=ar[i];
			i++;
			l++;
		}
		else
		{
			a[l]=ar[j];
			j++;
			l++;
		}
	}
	while(i<mid)
	{
			a[l]=ar[i];
			l++;
			i++;
	}
	while(j<end)
	{
			a[l]=ar[j];
			l++;
			j++;
	}
		
}

void mergesort(long long int arr[],int beg,int end)
{
	int mid=(beg+end)/2;
	if(beg==(end-1))
		return;
	mergesort(arr,beg,mid);
	mergesort(arr,mid,end);
	merge(arr,beg,end,mid);
}

int main()
{
	freopen("/home/soumyadeep/codechef/codechef/in.txt","r",stdin);
	freopen("/home/soumyadeep/codechef/codechef/out.txt","w",stdout);
	
	int n,t;
	long long int arr[SIZE];
	scanf("%d",&t);
	for(int j=0;j<t;j++)
	{
		scanf("%d",&n);
		
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&arr[i]);
		}
		mergesort(arr,0,n);
		
		int diff=arr[1]-arr[0];
		int temp;
		
		for(int i=0;i<(n-1);i++)
		{
			temp=arr[i+1]-arr[i];
			diff=MIN(diff,temp);
		}
		
		printf("%d\n",diff);
		
	}
	return 0;
}