
#include<stdlib.h>
#include<string.h>
struct queues
{
	char jno[5];
	int btime;
	int waiting_time;
	struct queues * next;
} * front1 = NULL,* rear1 = NULL, * front2 = NULL ,*rear2 = NULL;
int que1,que2;
struct queues q;
void Insert()
{	int time;
	char no[5];	
	struct queues* new_node =(struct queues*)malloc(sizeof(q));
	printf("Enter job number \n");
	scanf("%s",no);
	printf("Enter burst time");
	scanf("%d",&time);
	strcpy(new_node->jno ,no);
	new_node -> btime = time;
	new_node -> next =NULL;
	if (front1 == NULL)
		{ new_node->waiting_time = 0;
		  front1 = rear1 =new_node;
		}	
	else if (front2 == NULL)
		{ new_node ->waiting_time = 0;
		  front2 = rear2 =new_node;
		}
	else
	    {
	    	if (rear1->waiting_time > rear2 ->waiting_time)
	    		{ 
	    			new_node -> waiting_time = new_node->btime + rear2->waiting_time; 
	    		          rear2->next = new_node;
	    		  	rear2 = new_node;
	    		  	que2++;
	    		  	printf("%d",que2);
	    		}
		else if( rear1->waiting_time < rear2 ->waiting_time)
			{
				new_node ->waiting_time = new_node->btime + rear1->waiting_time;
				rear1->next =new_node;
				rear1 = new_node;
				que1++;
			}
		else 
			{ 	
				new_node ->waiting_time = new_node->btime + rear1->waiting_time;
				rear1->next =new_node;
				rear1 = new_node;
				que1++;
			}
	    }
}
void Display()
{
	int q1_wait_time;
	int q2_wait_time;
	int q1_avg;
	int q2_avg;
	if (front1 == NULL)
		printf("Queue 1 empty \n");
	else
	 {
	   struct queues *temp =front1;
	   printf("Queue 1 : ");
	   while(temp!= NULL)
	   {	
	   	printf("%s%d ",temp->jno,temp->btime);
	   	q1_wait_time += temp ->waiting_time;
	   	temp = temp ->next;
	   }
	 }
	 printf("\n");
	if (front2 == NULL)
		printf("Queue 2 empty \n");
	else
	 {
	   struct queues *temp =front2;
	   printf("Queue 2 : ");
	   while(temp!= NULL)
	   {	
	   	printf("%s%d ",temp->jno,temp->btime);
	   	q2_wait_time += temp ->waiting_time;
	   	temp = temp ->next;
	   }
	 }
	 printf("\n");
	 q1_avg=q1_wait_time /que1;
	 q2_avg=q2_wait_time /que2;
	printf("Average waiting time of queue1: %d \n",q1_avg);
	printf("Average waiting time of queue2: %d \n",q2_avg);
}
	
#include<stdio.h>
#include"queue.h"
void main()
{
 	int choice;
 	do
 	{
 		printf("Main Menu \n");
 		printf("1.Enter new node \n");
 		printf("2.Display \n");
 		printf("3.Exit \n");
 		printf("Enter choice \n");
 		scanf("%d",&choice);
 		switch(choice)
 		{
 			case 1: Insert();
 			        break;
 			case 2: Display();
 			        break;
 	   	}
 	   }while(choice!=3);
 }

