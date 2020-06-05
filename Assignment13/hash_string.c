#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define MAX 300
struct table
{
	char data[10];
	struct table* next;
};
int hashfunction(char key[10])
{
	int sum;
	for(int i=0;i<strlen(key);i++)
	{	
		int a = (int)key[i];
		sum+= a*(i+1);
		}
	sum = sum % 2069;	
	return sum;
}
int search(char key[10],struct table*hash_table[MAX])
{
	int h;
	struct table* temp;
	h = hashfunction(key);
	temp = hash_table[h];
	while(temp)
	{
		if(strcmp(temp->data,key)==0)
		{
			return h;
		}
		temp = temp->next;
	}
	return -1;
}

void insert(struct table* hash_table[MAX],char id[10])
{
	char key[10];
	strcpy(key,id);
	int hash;
	struct table* temp;
	hash = hashfunction(id);
	if (search(key,hash_table)!= -1)
	{
		printf("Duplicate key encountered");
		return;
	}
	else
	{
		temp = malloc(sizeof(struct table));
		strcpy(temp->data,id);
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
				printf(" %s" ,temp->data);
				temp = temp->next;
			}
		}
		printf("\n");
	}
}
void rem(char key[10],struct table*hash_table[MAX])
{
	int h;
	struct table* temp,*ptr;
	h = hashfunction(key);
	if(hash_table[h] == NULL)
	{
		printf("Key %s not found",key);
	}
	if(strcmp(hash_table[h]->data,key)==0)
	{
	temp = hash_table[h];
	hash_table[h] = hash_table[h]->next;
	free(temp);
	return;
	}
	ptr = hash_table[h];
	while(ptr->next)
	{
		if(strcmp(ptr->next->data,key)==0)
		{	
			temp = ptr->next;
			ptr->next =temp->next;
			free(temp);
			return;
		}
		ptr = ptr->next;
	}
	printf("Key %s Not found \n",key);
}
void main()
{
	struct table*hash_table[MAX];
	int choice;
	char key[10];
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
				printf("Enter the string \n");
				scanf("%s",key);
				insert(hash_table,key);
				break;
			case 2:
				printf("Enter the element to search \n");
				scanf("%s",key);
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
				scanf("%s",key);
				rem(key,hash_table);
				break;
			case 4: 
				show(hash_table);
				break;
		}
	}while(choice!=5);
}
	
		
				

