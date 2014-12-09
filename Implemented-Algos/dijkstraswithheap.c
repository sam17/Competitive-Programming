#include<stdio.h>
#include<limits.h>
#include<assert.h>
#define maxVertices 100
#define  infinity 1000010000
/*Declaring heap globally so that we do not need to pass it as an argument every time*/
/* Heap used here is Min Heap */
typedef struct Node
{
        int vertex,distance;
}Node;
Node heap[1000000];
int seen[maxVertices];
int heapSize;
/*Initialize Heap*/
void Init()
{
        heapSize = 0;
        heap[0].distance = -INT_MAX;
        heap[0].vertex  = -1;
}
/*Insert an element into the heap */
void Insert(Node element)
{
        heapSize++;
        heap[heapSize] = element; /*Insert in the last place*/
        /*Adjust its position*/
        int now = heapSize;
        while(heap[now/2].distance > element.distance) 
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap[now] = element;
}
Node DeleteMin()
{
        /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased. 
           Now heap[1] has to be filled. We put the last element in its place and see if it fits.
           If it does not fit, take minimum element among both its children and replaces parent with it.
           Again See if the last element fits in that place.*/
        Node minElement,lastElement;
        int child,now;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        /* now refers to the index at which we are now */
        for(now = 1; now*2 <= heapSize ;now = child)
        {
                /* child is the index of the element which is minimum among both the children */ 
                /* Indexes of children are i*2 and i*2 + 1*/
                child = now*2;
                /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
                  child */
                if(child != heapSize && heap[child+1].distance < heap[child].distance ) 
                {
                        child++;
                }
                /* To check if the last element fits ot not it suffices to check if the last element
                   is less than the minimum element among both the children*/
                if(lastElement.distance > heap[child].distance)
                {
                        heap[now] = heap[child];
                }
                else /* It fits there */
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}
int main()
{
        int graph[maxVertices][maxVertices],size[maxVertices]={0},distance[maxVertices]={0},cost[maxVertices][maxVertices];
        int vertices,edges,weight;
        int iter;
        /* vertices represent number of vertices and edges represent number of edges in the graph. */
        scanf("%d%d",&vertices,&edges);
        int from,to;
        for(iter=0;iter<edges;iter++)
        {
                scanf("%d%d%d",&from,&to,&weight);
                assert(from>=0 && from<vertices);
                assert(to>=0 && to<vertices);
                graph[from][size[from]] = to;
                cost[from][size[from]] = weight;
                size[from]++;
        }
        int source;
        scanf("%d",&source);
        Node temp;
        for(iter=0;iter<vertices;iter++)
        {
                if(iter==source)
                {
                        temp.distance = 0;
                        distance[0]=0;
                }
                else
                {
                        temp.distance = infinity;
                        distance[iter]= infinity;
                }
                temp.vertex = iter;
                Insert(temp);
        }
        while(heapSize)
        {
                Node min = DeleteMin();
                int presentVertex = min.vertex;
                if(seen[presentVertex])
                {
                        /* This has already been processed */
                        continue;
                }
                seen[presentVertex] = 1;
                for(iter=0;iter<size[presentVertex];iter++)
                {
                        int to = graph[presentVertex][iter];
                        if(distance[to] > distance[presentVertex] + cost[presentVertex][iter])
                        {
                                distance[to] = distance[presentVertex] + cost[presentVertex][iter];
                                /* Instead of updating it in the queue, insert it again. This works because the updated
                                   distance is less than previous distance which makes it to pop out of the queue early */
                                temp.vertex = to;
                                temp.distance = distance[to];
                                Insert(temp);
                        }
                }
        }
        for(iter=0;iter<vertices;iter++)
        {
                printf("vertex is %d, its distance is %d\n",iter,distance[iter]);
        }


        return 0;



}

