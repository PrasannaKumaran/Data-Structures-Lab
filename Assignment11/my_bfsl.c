#include<stdio.h>
#include<stdlib.h>
#define size 40
struct node
{
	int data;
	struct node* next;
};
struct Queue
{
 	int data[size];
 	int front ;
 	int rear ;
};
struct Graph
{
	int no_of_vertices;
	int* visited;
	struct node** adjList;
};

int traversal[10];
int l=0;
struct node* createNode(int d)
{
	struct node* n = malloc(sizeof(struct node));
	n->data = d;
	n->next = NULL;
	return n;
}
struct Graph* createGraph(int vertices)
{
	struct Graph* graph =malloc(sizeof(struct Graph));
	graph->no_of_vertices = vertices;
	graph->visited = malloc(sizeof(int)* vertices);
	graph->adjList = malloc(sizeof(struct node*) *vertices);
	for(int i=0; i<vertices; i++)
	{
		graph->adjList[i] = NULL;
		graph->visited[i] = 0;
	}
	return graph;
}
void addEdge(struct Graph * graph,int source, int destination)
{
	struct node* n =createNode(destination);
	n->next = graph->adjList[source];
	graph->adjList[source] = n;
	n = createNode(source);
       	n->next = graph->adjList[destination];
        	graph->adjList[destination] = n;
   
	
}
struct Queue* createQueue()
{
 	struct Queue* q =malloc(sizeof(struct Queue));
 	q->front = -1;
 	q->rear = -1;
 	return q;
}
int isEmpty(struct Queue* q)
{
	if(q->rear == -1)
		return 1;
	else
		return 0;
}
	
void enqueue(struct Queue * q ,int d)
{
	if(q->rear == size-1)
		printf("Queue Full \n");
	else
	{	
		if(q->front == -1)
			q->front = 0;
		q->rear++;
		q->data[q->rear] = d;
	}
}
int dequeue(struct Queue *q)
{
	int d;
	if(isEmpty(q))
		{
		printf("Queue Empty \n");
		}
	else{
	d = q->data[q->front];
	q->front++;
	if(q->front> q->rear)
		{q->front = q->rear = -1;}
	     }
	 return d;
}
void printQueue(struct Queue *q) 
{
        int i = q->front;
        if(isEmpty(q))
            printf("Queue is empty"); 
        else 
        {
            printf("\nQueue contains \n");
            for(i = q->front; i < q->rear + 1; i++) 
            {       printf("%d ", q->data[i]);
          
            }
        }    
}
void bfs(struct Graph*graph,int startvertex)
{
	struct Queue* q = createQueue();
	graph->visited[startvertex] = 1;
	enqueue(q,startvertex);
	while(!isEmpty(q))
	{	
		
		printQueue(q);
		int cur_v = dequeue(q);
		traversal[l] = cur_v;
		l++;
		struct node* temp = graph->adjList[cur_v];
		
		while(temp!=NULL)
		{	
			int adj_v = temp->data;
			if(graph->visited[adj_v]==0)
			{
				graph->visited[adj_v] = 1;
				enqueue(q,adj_v);
			}
			temp=temp->next;
		}
	}
}
int main()
{
	int n;
	printf("Enter no of vertices ");
	scanf("%d",&n);
	struct Graph* graph = createGraph(n);
	addEdge(graph,0,1);
	addEdge(graph,0,3);
	addEdge(graph,1,2);
	addEdge(graph,2,3);
	addEdge(graph,2,4);
	bfs(graph,1);
	printf("\nTraversal order \n");
	for (int i=0;i<l;i++)
		printf("%d ",traversal[i]);
	return 0;
	
}
	
