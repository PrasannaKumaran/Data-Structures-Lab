#include<stdio.h>
#define INFINITY 9999
#define MAX 10
int no_of_vertices;
 int minDistance(int dist[no_of_vertices], int Set[no_of_vertices])
{
    //INFINITY= Infinity
   int min = 100, min_index;
   for (int v = 0; v < no_of_vertices; v++)
     if (Set[v]==0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
   return min_index;
}

 void dijkstra(int graph[no_of_vertices][no_of_vertices], int start)
{  	 int dist[no_of_vertices];
     int Set[no_of_vertices];
     for (int i = 0; i < no_of_vertices; i++)
        {
            dist[i] = MAX;
             Set[i]=0;
        }
     dist[start-1] = 0;
     for (int count = 0; count < no_of_vertices-1; count++)
     {
       int u = minDistance(dist,Set);
       Set[u]=1;
       for (int v = 0; v < no_of_vertices; v++)
         if (!Set[v] && graph[u][v] && dist[u] != MAX
                                       && ((dist[u]+graph[u][v]) < dist[v]))
            dist[v] = dist[u] + graph[u][v];
     }
     for(int i=0;i<no_of_vertices;i++)
     	printf("Travel Distance from node %d: %d \n",i+1,dist[i]);
     }
int main()
{
	int G[MAX][MAX],i,j,u;
	printf("Enter no. of vertices:");
	scanf("%d",&no_of_vertices);
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<no_of_vertices;i++)
		for(j=0;j<no_of_vertices;j++)
			scanf("%d",&G[i][j]);
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(G,u);
	
	return 0;
}
