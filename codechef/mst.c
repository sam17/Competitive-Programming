/*****************************/
// SOUMYADEEP MUKHEERJEE
// 11CH30022
// MINIMUM SPANNING TREE
/******************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxVertices 1000
#define maxEdges 1000000

int graph[maxVertices][maxVertices];
int parent[maxVertices];

typedef struct Edge
{
        int from,to,weight;
}Edge;
Edge E[maxEdges];
//Choose pivot function for quick sort
int choosepivot(int beg,int end)
{
	return beg+1;
}
//Partition function for quicksort
int partition(Edge arr[],int beg,int end)
{
	int pivot=choosepivot(beg,end);
	int i=beg,j=end;
	Edge temp;
	while(i<j)
	{
		while((i<end)&&(arr[i].weight<=arr[pivot].weight))
			i++;
		while(arr[j].weight>arr[pivot].weight)
			j--;
		if(i<j)
		{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
		
	}
	temp=arr[pivot];
	arr[pivot]=arr[j];
	arr[j]=temp;
	return j;
}
//Quicksort function
void quicksort(Edge arr[],int beg,int end)
{
	if(beg>=end)
		return;
	int t=partition(arr,beg,end);
	quicksort(arr,beg,t-1);
	quicksort(arr,t+1,end);
	
}
//Function to initialize all parents
void init(int vertices)
{
        int iter=0;
        for(iter=0;iter<vertices;iter++)
        {
                parent[iter]=-1;
        }

}
/* Finding its parent as well as updating the parent of all vertices along this path */
int Find(int vertex)
{
        if(parent[vertex]==-1)return vertex;
        return parent[vertex] = Find(parent[vertex]); 
}
//FUnction to unite two nodes
void Union(int parent1,int parent2)
{
        parent[parent1] = parent2;
}
//Function that implements Kruskal
void Kruskal(int vertices,int edges)
{
        memset(graph,-1,sizeof(graph)); 
        /* Sort the edges according to the weight */
        quicksort(E,0,edges-1);
        /* Initialize parents of all vertices to be -1.*/
        init(vertices);
        int totalEdges = 0,edgePos=0,from,to,weight;
        Edge this;
        while(totalEdges<vertices && edgePos<edges)
        {

                this = E[edgePos++];
                from = this.from;
                to = this.to;
                weight=this.weight;
                /* See If vertices from,to are connected. If they are connected do not add this edge. */
                int parent1 = Find(from);
                int parent2 = Find(to);
                if(parent1!=parent2)
                {
                        graph[from][to] = weight;
                        Union(parent1,parent2);
                        totalEdges++;
                }
        }

}

int main()
{
        int vertices,edges,cost=0;
	printf("Enter the number of vertices and edges \n"); 
        scanf("%d%d",&vertices,&edges);
        int iter,jter;
        int from,to,weight;
	printf("Enter the node 1,node 2 adn its corresponding weight in order \n");
        for(iter=0;iter<edges;iter++)
        {
                scanf("%d%d%d",&from,&to,&weight);
                E[iter].from = from; 
                E[iter].to = to; 
                E[iter].weight = weight;
        }
        /* Finding MST */
        Kruskal(vertices,edges);
        /* Printing the MST */
        for(iter=0;iter<=vertices;iter++)
        {
                for(jter=0;jter<=vertices;jter++)
                {
                        if(graph[iter][jter]!=-1)
                        {
                                printf("Vertex %d and %d, Weight %d\n",iter,jter,graph[iter][jter]);
				cost+=graph[iter][jter];
                        }
                }
        }
	printf("Cost= %d\n",cost);
        return 0;
}
