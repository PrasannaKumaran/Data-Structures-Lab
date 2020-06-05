#include<stdio.h>
#include<stdlib.h>
# define MAX 5
struct table
{
	int data;
	struct table* next;
};
int hashfunction(int key)
{
	return (key%MAX);
}
void insert(struct table*hash_table[MAX],int id)
{
	int key = id;
	int hash;
	struct table* temp;
	hash = hashfunction(key);
	if (search(key,hash_table)!= -1)
	{
		printf("Duplicate key encountered");
		return;
	}
	else
	{
		temp = malloc(sizeof(struct table));
		temp->data = id;
		temp->next = hash_table[hash];
		hash_table[hash] = temp;
	}
}
void show(struct table*hash_table[MAX])
{
	struct table* temp ;
	for (int i=0;i<MAX;i++)
	{
		if(hash_table[i]!=NULL)
		{
			temp = hash_table[i];
		while(temp)
			{
				printf("%d  " ,temp->data);
				temp = temp->next;
			}
		}
		printf("\n");
	}
}
int search(int key,struct table*hash_table[MAX])
{
	int h;
	struct table* temp;
	h = hashfunction(key);
	temp = hash_table[h];
	while(temp)
	{
		if(temp->data == key)
		{
			return h;
		}
		temp = temp->next;
	}
	return -1;
}
void rem(int key,struct table*hash_table[MAX])
{
	int h;
	struct table* temp,*ptr;
	h = hashfunction(key);
	if(hash_table[h] == NULL)
	{
		printf("Key %d not found",key);
	}
	if(hash_table[h]->data ==key)
	{
	temp = hash_table[h];
	hash_table[h] = hash_table[h]->next;
	free(temp);
	return;
	}
	ptr = hash_table[h];
	while(ptr->next)
	{
		if(ptr->next->data == key)
		{	
			temp = ptr->next;
			ptr->next =temp->next;
			free(temp);
			return;
		}
		ptr = ptr->next;
	}
	printf("Key %d Not found \n",key);
}
void main()
{
	struct table*hash_table[MAX];
	int key,choice;
	for(int i=0;i<MAX;i++)
		hash_table[i] = NULL;
	do
	{
		printf("1.Insert a Record \n");
		printf("2.Search a Record \n");
		printf("3.Delete a Record \n");
		printf("4.Show Table \n");
		printf("5.Exit \n");
		printf("Enter choice \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
				printf("Enter the number \n");
				scanf("%d",&key);
				insert(hash_table,key);
				break;
			case 2:
				printf("Enter the element to search \n");
				scanf("%d",&key);
				int found = search(key,hash_table);
				if(found == -1)
				{
					printf("Element not Found \n");
				}
				else
				{
					printf("Element found in chain %d \n",found);
				}
				break;
			case 3:
				printf("Enter element to delete \n");
				scanf("%d",&key);
				rem(key,hash_table);
				break;
			case 4: 
				show(hash_table);
				break;
		}
	}while(choice!=5);
}
	
		
				

