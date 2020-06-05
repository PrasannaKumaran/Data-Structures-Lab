#include<stdio.h>
#include<stdlib.h>
typedef struct user
{
    char name[40],email[40],uname[40],pwd[40],notify[200];
    int cap,book,demand,v,location;
    float bill;
    long ph;
}user;
typedef struct Queue
{
	int front,rear,size;
	int capacity;
	struct user* user_array;
}Queue;
struct Queue* createQueue(int capacity)
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = 0;
	q->rear = capacity -1;
	q->size = 0;
	q->capacity = capacity;
	q->user_array = (struct user*)malloc(sizeof(struct user)* capacity);
	return q;
}
int isFull(struct Queue* q)
{
	if(q->size == q->capacity)
	{
		printf("Please try again later! Maximum orders reached \n");
		return 1;
	}
	return 0;
}
int isEmpty(struct Queue* q)
{
	return (q->size == 0);
}
void Enqueue(struct Queue* q, struct user* u)
{
	if(isFull(q))
		return;
	q->rear = (q->rear + 1)%q->capacity;
	q->user_array[q->rear] = *u;
	q->size = q->size + 1;
	//printf("Your request is being processed ! Please Wait...\n");
}
struct user* dequeue(struct Queue* q)
{
	if(isEmpty(q))
		printf("Queue Empty ! \n");
	else
	{
		struct user* u = &q->user_array[q->front];
		q->front = (q->front + 1)%q->capacity;
		q->size = q->size -1;
		return u;
	}
	return NULL;
}
struct user* front(struct Queue* q)
{
	if(isEmpty(q))
		printf("All requests have been satsified ! ");
	else
		return &q->user_array[q->front];
	return NULL;
}
