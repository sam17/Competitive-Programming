#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <iostream>

struct num
{
	int freq;
	int numb;
};

#define SIZE 100000
using namespace std;


void merge(num a[],int beg,int end,int mid)
{
	num ar[SIZE];
	
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
		if(ar[i].freq<ar[j].freq)
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

void mergesort(num arr[],int beg,int end)
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
	int n,k;
	num a[SIZE];
	for(int i=0;i<SIZE;i++)
		a[i].freq=0;
	freopen("/home/dementor/codechef/codechef/in.txt","r",stdin);
	freopen("/home/dementor/codechef/codechef/out.txt","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i].numb);
		a[i].freq ++;
	}
	mergesort(a,0,n);
	for(int i=0;i<n;i++)
	{
		printf("%d %d\n",a[i].numb,a[i].freq);
	}
	
	
	return 0;
}
	