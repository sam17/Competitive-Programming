#include<stdio.h>
#include<assert.h>
/* maxVertices represents maximum number of vertices that can be present in the graph. */
#define maxVertices   100
void Dfs(int graph[][maxVertices], int *size, int presentVertex,int *visited)
{
        printf("Now visiting vertex %d\n",presentVertex);
        visited[presentVertex] = 1;
        /* Iterate through all the vertices connected to the presentVertex and perform dfs on those
           vertices if they are not visited before */
        int iter;
        for(iter=0;iter<size[presentVertex];iter++)
        {
                if(!visited[graph[presentVertex][iter]])
                {
                        Dfs(graph,size,graph[presentVertex][iter],visited);
                }
        }
        return;
        

}
/* Input Format: Graph is directed and unweighted. First two integers must be number of vertces and edges 
   which must be followed by pairs of vertices which has an edge between them. */
int main()
{
        int graph[maxVertices][maxVertices],size[maxVertices]={0},visited[maxVertices]={0};
        int vertices,edges,iter;
        /* vertices represent number of vertices and edges represent number of edges in the graph. */
        scanf("%d%d",&vertices,&edges);
        int vertex1,vertex2;
        for(iter=0;iter<edges;iter++)
        {
                scanf("%d%d",&vertex1,&vertex2);
                assert(vertex1>=0 && vertex1<vertices);
                assert(vertex2>=0 && vertex2<vertices);
                graph[vertex1][size[vertex1]++] = vertex2;
        }
        int presentVertex;
        for(presentVertex=0;presentVertex<vertices;presentVertex++)
        {
                if(!visited[presentVertex])
                {
                        Dfs(graph,size,presentVertex,visited);
                }
        }
        return 0;



}
