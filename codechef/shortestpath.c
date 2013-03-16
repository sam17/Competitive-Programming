
#include<stdio.h>
#define INFINITY 999999

int cost[10][10],dist[20],i,j,n,k,m,S[20],v,totcost,path[20],p;
 
int shortest(int v,int n)
{
        int min;
        for(i=1;i<=n;i++)
        {
                S[i]=0;
                dist[i]=cost[v][i];
        }
        path[++p]=v;
        S[v]=1;
        dist[v]=0;
        for(i=1;i<=n;i++)
        {
                k=-1;
                min=INFINITY;
                for(j=1;j<=n;j++)
                {
                        if(dist[j]<min && S[j]!=1)
                        {
                                min=dist[j];
                                k=j;
                        }
                }
                if(cost[v][k]<=dist[k])
                        p=1;
                path[++p]=k;

                S[k]=1;
                for(j=1;j<=n;j++)
                {
			printf(" %d ",dist[j]);
			if(cost[k][j]!=INFINITY && dist[j]>=dist[k]+cost[k][j] && S[j]!=1)
                                dist[j]=dist[k]+cost[k][j];	
		}
		printf("\n");
        }	
        return v;
}
 
int main()
{
        int c;
        printf("Vertices = \n");
        scanf("%d",&n);
        printf("Edges = \n");
        scanf("%d",&m);
        printf("EDGE Costs: \n");
 
        for(k=1;k<=m;k++)
        {
                scanf("%d %d %d",&i,&j,&c);
                cost[i][j]=c;
        }
 
        for(i=1;i<=n;i++)
                for(j=1;j<=n;j++)
                        if(cost[i][j]==0)
                                cost[i][j]=INFINITY;

        printf("Initial Vertex:\n");
        scanf("%d",&v);
        shortest(v,n);
        return 0;
}
