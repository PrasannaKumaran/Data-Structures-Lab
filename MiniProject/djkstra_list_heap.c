// ADT FOR DJIKSTRAS ALGORITHM USING ADJACENY LIST AND MIN HEAP !
#include<stdio.h>
#include<stdlib.h>
struct AdjListNode
{
	int distance;
	int destination;
	struct AdjListNode * next;
};
struct Graph
{
	int no_of_nodes;
	struct AdjListNode** AdjList;
};
struct AdjListNode* newAdjListNode(int dest , int dist)
{
	struct AdjListNode* newNode= (struct AdjListNode*)malloc(sizeof(struct AdjListNode*));
	newNode->destination = dest;
	newNode->distance = dist;
	newNode->next = NULL;
	return newNode;
}
struct Graph* createGraph(int nodes)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph*));
	graph->no_of_nodes = nodes;
	graph->AdjList = malloc(sizeof(struct AdjListNode*)* nodes);
	for(int i = 0; i<nodes; i++)
		graph->AdjList[i] = NULL;
	return graph;
}
void addEdge(struct Graph* graph,int source, int destination, int distance)
{
	struct AdjListNode* newNode = newAdjListNode(destination, distance);
	newNode->next = graph->AdjList[source];
	graph->AdjList[source] = newNode;
	
	newNode = newAdjListNode(source, distance);
	newNode->next = graph->AdjList[destination];
	graph->AdjList[destination] = newNode;
}
struct MinHeapNode
{
	int distance;
	int vertex;
};
struct MinHeap
{
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode **array;
};
struct MinHeapNode* newMinHeapNode(int v,int dist)
{
	struct MinHeapNode* newNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	newNode->vertex = v;
	newNode->distance = dist;
	return newNode;
}
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->pos = (int*)malloc(sizeof(int)* capacity); 
	heap->array = (struct MinHeapNode**)malloc(sizeof(struct MinHeapNode*)* capacity);
	return heap;
}
void swapNode(struct MinHeapNode** a , struct MinHeapNode** b)
{
	struct MinHeapNode* temp = *a;
	*a = *b;
	*b = temp;
}
void MinHeapify(struct MinHeap* heap,int index)
{
	int small,left,right;
	small = index;
	left = (2 * index) + 1;
	right = (2* index) + 2;
	if( left < heap->size && heap->array[left]->distance < heap->array[small]->distance)
		small = left;
	if( right <heap->size && heap->array[right]->distance < heap->array[small]->distance)
		small = right;
	if(small != index)
	{
		struct MinHeapNode *smallestNode = heap->array[small];
		struct MinHeapNode *indexNode = heap->array[index];
		heap->pos[smallestNode->vertex] = index;
		heap->pos[indexNode->vertex] = small;
		swapNode(&heap->array[small], &heap->array[index]);
		MinHeapify(heap,small);
	}
}
int isEmpty(struct MinHeap* heap)
{
	return heap->size == 0;
}
struct MinHeapNode* extractMin(struct MinHeap* heap)
{
	if(isEmpty(heap))	
		return NULL;
	struct MinHeapNode* root = heap->array[0];
	struct MinHeapNode* last = heap->array[heap->size - 1];
	heap->array[0] = last;
	heap->pos[root->vertex] = heap->size -1 ;
	heap->pos[last->vertex] = 0;
	--heap->size;
	MinHeapify(heap, 0);
	return root;
}
void DecreaseKey(struct MinHeap* heap ,int vertex, int dist)
{
	int i = heap->pos[vertex];
	heap->array[i]->distance = dist;
	while(i && heap->array[i]->distance < heap->array[(i-1)/2]->distance)
	{
		heap->pos[heap->array[i]->vertex] = (i-1)/2;
		heap->pos[heap->array[(i-1)/2]->vertex] = i;
		swapNode(&heap->array[i], &heap->array[(i-1)/2]);
		i = (i-1)/2;
	}
}
int isInMinHeap(struct MinHeap* heap,int vertex)
{
	if(heap->pos[vertex] < heap->size)
		return 1;
	return 0;
}
void Printresult(int dist[], int n)
{
	printf("Vertex Distance From Source \n");
	for(int i=0; i<n; i++)
		printf("%d \t\t %d \n",i,dist[i]);
}
void Djikstra(struct Graph* graph, int source)
{
	int v =graph->no_of_nodes;
	int dist[v];
	struct MinHeap* heap = createMinHeap(v);
	for(int k=0; k<v;k++)
	{
		dist[k] = 9999;
		heap->array[k] = newMinHeapNode(k,dist[k]);
		heap->pos[k] = k;
	}
	heap->array[source] = newMinHeapNode(source, dist[source]);
	heap->pos[source] = source;
	dist[source] = 0;
	DecreaseKey(heap, source, dist[source]);
	heap->size = v;
	
	while(!isEmpty(heap))
	{
		struct MinHeapNode* minNode = extractMin(heap);
		int u = minNode->vertex;
		struct AdjListNode* traverse = graph->AdjList[u];
		while(traverse != NULL)
		{
			int v = traverse->destination;
			if(isInMinHeap(heap,v) && dist[u]!=9999 && (traverse->distance + dist[u] < dist[v]))
			{
				dist[v] = dist[u] + traverse->distance;
				DecreaseKey(heap,v,dist[v]);
			}
			traverse = traverse->next;
		}
	}
	Printresult(dist,v);
}
int main()
{
	int V = 9;
	struct Graph* graph = createGraph(V);
	addEdge(graph, 0, 1, 4); 
    	addEdge(graph, 0, 7, 19); 
    	addEdge(graph, 1, 2, 83); 
   	addEdge(graph, 1, 7, 41); 
    	addEdge(graph, 2, 3, 67); 
   	addEdge(graph, 2, 8, 27); 
   	addEdge(graph, 2, 5, 48); 
   	addEdge(graph, 3, 4, 91); 
   	addEdge(graph, 3, 5, 134); 
   	addEdge(graph, 4, 5, 120); 
  	addEdge(graph, 5, 6, 24); 
   	addEdge(graph, 6, 7, 16); 
   	addEdge(graph, 6, 8, 26); 
   	addEdge(graph, 7, 8, 117); 
  
    Djikstra(graph, 0); 
  	
    return 0; 
 }
