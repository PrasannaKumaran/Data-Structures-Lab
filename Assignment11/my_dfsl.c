#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int data;
	struct stack * next;
}*top = NULL;
void push(int d)
{
	struct stack* new_entry;
	new_entry = malloc(sizeof(struct stack));
	new_entry->data =d;
	if (top ==NULL)
		new_entry->next = NULL;
	else
		new_entry->next = top;
	top = new_entry;
}
int pop()
{
	int d;
	if(top == NULL)
		printf("stack empty \n");
	else
	{
		struct stack* rem = top;
		d = rem->data;
		top = top->next;
		free(rem);
	}
	return d;
}
struct node
{
	int data;
	struct node* next;
};
struct Graph
{
	int no_of_vertices;
	struct node** adjlist;
	int* visited;
};
struct node* create_node(int new_data)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node->next = NULL;
	return new_node;
};
struct Graph* create_graph(int vertices)
{
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->no_of_vertices = vertices;
	graph->visited = malloc(sizeof(int)*vertices);
	graph->adjlist = malloc(vertices * sizeof(struct node*));
	for(int i =0 ; i< vertices;i++)
	{
		graph->visited[i] = 0;
		graph->adjlist[i] = NULL;
	}
	return graph;
};
void addedge(struct Graph* graph , int source, int destination)
{
	struct node* new_node = create_node(destination);
	new_node->next = graph->adjlist[source];
	graph->adjlist[source] = new_node;

	new_node = create_node(source);
	new_node->next = graph->adjlist[destination];
	graph->adjlist[destination] = new_node;
	//printf("%c \n",new_node->data);
}
void printGraph(struct Graph* graph)
{
	for(int i=0; i<graph->no_of_vertices; i++)
	{
        printf("Start: %d \t",i);
		struct node *temp = graph->adjlist[i];
		while(temp!=NULL)
		{
			printf(" -> %d", temp->data);
			temp = temp->next;
		}
	printf("\n");

	}
}
void DFS(struct Graph* graph, int vertex)
{
	struct node* new_list = graph->adjlist[vertex];
	struct node* temp = new_list;
	graph->visited[vertex] = 1;
	push(vertex);
	int cur_v = pop();
	temp = graph->adjlist[cur_v];
	while(temp!=NULL)
	{
		int connected = temp->data;
		if(graph->visited[connected] == 0)
		{
			push(connected);
			DFS(graph,connected);
		}
		temp = temp->next;
	}
}
int main()
{
	int no;
	printf("Enter the no of vertices \n");
	scanf(" %d",&no);
	struct Graph* graph = create_graph(5);
	addedge(graph,0,1);
	addedge(graph,0,2);
	addedge(graph,0,4);
	addedge(graph,1,3);
	addedge(graph,1,4);
	DFS(graph,0);
	printGraph(graph);
	return 0;

}
