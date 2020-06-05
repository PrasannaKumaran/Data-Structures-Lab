//FUNCTIONS.H

typedef struct
	{
			long int regno;
			char name[20];
			int marks[5];
	} student_records;
	student_records a;
int count;
void Insert_beg(student_records *s,student_records temp)
{
    for (int i=count;i>0;i--)
        s[i]=s[i=1];
    s[0]=temp;
}
void Insert_end(student_records *s,student_records temp)
{   if (count==0)
        s[0]=temp;
    s[count-1]=temp;
}
void Insert_pos(student_records *s,student_records temp,int pos)
{
    for(int i=count;i>pos;i--)
        s[i]=s[i-1];
    s[pos-1]=temp;
}
void Search( student_records  *s,char name[20])
{	int flag=0;
	for(int i=0;i<count;i++)
		if(strcmp(s[i].name,name)==0)
			{
			 printf("Data found in location %d",i+1);
			 flag=1;
			 break;
			}
	if(flag==0)
		printf("Data not found \n");
}
void Display( student_records  *s)
{
	for(int i=0;i<count;i++)
		{
			printf("Name: %s Regno: %ld ",s[i].name,s[i].regno);
			for(int k=0;k<5;k++)
				printf("%d ",s[i].marks[k]);
		}
}
void Display_prev_next( student_records  *s,int pos)
{
	printf("Name: %s Regno: %ld ",s[pos-1].name,s[pos-1].regno);
			for(int k=0;k<5;k++)
				printf("%d ",s[pos-1].marks[k]);
	printf("\nName: %s Regno: %ld ",s[pos+1].name,s[pos+1].regno);
			for(int k=0;k<5;k++)
				printf("%d ",s[pos+1].marks[k]);
}
void Delete( student_records  *s,long int regn)
{
	int position=0;
	for(int i=0;i<count;i++)
	  	if(s[i].regno==regn)
	  	  {
	  	  	position=i;
	  	  	break;
	  	  }
	for(int i=position;i<count;i++)
	   	s[i]=s[i+1];
}

//MAIN FUNCTION

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include"prototype.h"
#include"functions.h"

int capacity;
int count=0;
int main()
{ 	char search_name[20];
	 int del_regno;
	int n;
	 student_records *s;
	 student_records temp;
	int position=0;
	int choice;
	printf("Enter maximum Capacity \n");
	scanf("%d",&capacity);
	s=(student_records *)malloc(sizeof(a)*capacity);
	do
	{
	printf("\nMain Menu \n ");
	printf("1.Insert a record in the begining \n");
	printf("2.Insert a record in the end \n");
	printf("3.Insert a record in any given position \n");
	printf("4.Search a record \n");
	printf("5.Delete a record \n");
	printf("6.Display all the records \n");
	printf("7.Display Previous and Following record \n");
	printf("8.Exit \n");
	printf("Enter choice \n");
	scanf("%d",&choice);
	switch(choice)
		{
		case 1: printf("Enter the details \n ");
				printf("Enter regno \n");
				scanf("%ld",&temp.regno);
				printf("Enter name \n");
				scanf(" %[^\n]",temp.name);
				printf("Enter marks in 5 subjects \n");
				for(int i=0;i<5;i++)
				 	scanf("%d",&temp.marks[i]);
                count++;
				Insert_beg(s,temp);
				break;
		case 2:	printf("Enter the details \n ");
				printf("Enter regno \n");
				scanf("%ld",&temp.regno);
				printf("Enter name \n");
				scanf(" %[^\n]",temp.name);
				printf("Enter marks in 5 subjects \n");
				for(int i=0;i<5;i++)
				 	scanf("%d",&temp.marks[i]);
                count++;
				Insert_end(s,temp);
				break;
		case 3: printf("Enter the details \n ");
				printf("Enter regno \n");
				scanf("%ld",&temp.regno);
				printf("Enter name \n");
				scanf(" %[^\n]",temp.name);
				printf("Enter marks in 5 subjects \n");
				for(int i=0;i<5;i++)
				 	scanf("%d",&temp.marks[i]);
				int pos;
				printf("Enter position \n");
				scanf("%d",&pos);
				count++;
				Insert_pos(s,temp,pos);
				break;
		case 4:	printf("Enter name to be searched \n");
				scanf(" %s",search_name);
				Search(s,search_name);
				break;
		case 5: printf("Enter regno to be deleted \n");
				scanf("%d",&del_regno);
				count--;
				Delete(s,del_regno);
				break;
		case 6: Display(s);
				break;
		case 7:	printf("Enter the position \n");
				scanf("%d",&position);
				Display_prev_next(s,position);
				break;
		}
	}while(choice!=8);
	return 0;
}

