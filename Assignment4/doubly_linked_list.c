#include<stdio.h>
#include"double_linked_list.h"
int main()
{   stud * head;
    stud * tail;
    head=create();
    tail=head->next;
    char se_name[30];
    char sea_name[30];
    int choice;
    do
    {
        printf("\nMain Menu \n");
        printf("1.Insert data Beginning \n");
        printf("2.Insert data End \n");
        printf("3.Insert data after name \n");
        printf("4.Search for a record \n");
        printf("5.Delete a record \n");
        printf("6.Print all student names \n");
        printf("7.Print names in alphabetical order \n");
        printf("8.Exit \n");
        printf("Enter choice \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: Insert_beg(head);
                    break;
            case 2: Insert_end(tail);
                    break;
            case 3: printf("Enter name to be searched \n");
                    scanf(" %[^\n]",se_name);
                    stud *tempo;
                    tempo=(stud *)malloc(sizeof(stud));
                    tempo=Get_position(head,se_name);
                    Insert_mid(tempo);
                    break;
            case 4: printf("Enter name to be searched \n");
                    scanf(" %[\n]",sea_name);
                    Search_stud(head,sea_name);
                    break;
            case 5:
                    printf("Enter name to be deleted \n");
                    scanf(" %[^\n]",se_name);
                    stud *temp;
                    temp=(stud *)malloc(sizeof(stud));
                    temp=Get_position(head,se_name);
                    Delete(temp);
                    break;
            case 6: Display_all(head);
                    break;
            case 7: alpha(head);
                    break;

        }
    }
    while(choice!=8);

    return 0;
}
// FUNCTIONS

#include<stdlib.h>
#include<string.h>
typedef struct student
    {
        char name[30];
        int regno;
        int marks[3];
        struct student *next;
        struct student *prev;
        }  stud;
stud * create()
{   stud *head ;
    stud *tail;
    head=malloc(sizeof(stud));
    tail=malloc(sizeof(stud));
    head->next=tail;
    head->prev=NULL;
    tail->next=NULL;
    tail->prev=head;
    return head;
}
void Insert_beg(stud *head)
{
    stud *new_stud;
    new_stud=malloc(sizeof(stud));
    printf("Enter the student details \n");
    printf("Enter the name \n");
    scanf(" %[^\n]",new_stud->name);
    printf("Enter the registration number \n");
    scanf("%d",&new_stud->regno);
    printf("Enter the marks secured in 3 subjects \n");
    for(int j=0;j<3;j++)
        scanf("%d",&new_stud->marks[j]);
    new_stud->next = head->next;
    new_stud->prev = head;
    head->next->prev = new_stud;
    head->next = new_stud;
}
void Insert_end(stud *tail)
{
    stud *new_stud;
    new_stud=malloc(sizeof(stud));
    printf("Enter the student details \n");
    printf("Enter the name \n");
    scanf(" %[^\n]",new_stud->name);
    printf("Enter the registration number \n");
    scanf(" %d",&new_stud->regno);
    printf("Enter the marks secured in 3 subjects \n");
    for(int j=0;j<3;j++)
        scanf(" %d",&new_stud->marks[j]);
    new_stud->next = tail;
    new_stud->prev = tail->prev;
    tail->prev->next = new_stud;
    tail->prev = new_stud;
}
void Insert_mid(stud * prev_pos)
{   prev_pos=prev_pos->prev;
    stud *new_stud;
    new_stud=(stud *)malloc(sizeof(stud));
    printf("Enter the student details \n");
    printf("Enter the name \n");
    scanf(" %[^\n]",new_stud->name);
    printf("Enter the registration number \n");
    scanf("%d",&new_stud->regno);
    printf("Enter the marks secured in 3 subjects \n");
    for(int j=0;j<3;j++)
        scanf("%d",&new_stud->marks[j]);
    new_stud->next=prev_pos->next;
    new_stud->prev=prev_pos;
    prev_pos->next->prev=new_stud;
    prev_pos->next=new_stud;

}
stud * Get_position(stud * head , char s_name[30])
{
    stud * t= head->next;
    while ( (t->next)!=NULL && strcmp( t->name , s_name)!=0)
        t=t->next;
    return t;
}
void Search_stud(stud * head, char search_name[30])
{
    int flag=0;
    stud *t = head;
    while(t->next !=NULL)
        {
            if (strcmp(t->name, search_name)==0)
                {   printf("Student Data found ! \n");
                    flag=1;
                    break;
                }
            else
                t=t->next;
        }
    if(flag==0)
        printf("Student data not found ! \n");
}
void Display_all(stud * head)
{
    stud * t=head->next;
    printf("Student Details :\n");
    while( t->next!=NULL)
        {
            printf("Name : %s \n",t->name);
            printf("Regno: %d \n",t->regno);
            printf("Marks: %d %d %d ",t->marks[0],t->marks[1],t->marks[2]);
            t=t->next;

        }
}
void Delete(stud * prev_pos)
{
    stud * del_det=prev_pos->next;
    printf("Deleted Details \n");
    printf("Name : %s ",del_det);
    prev_pos->next=prev_pos->next->next;
    prev_pos->next->prev=prev_pos;
    free(del_det);
}
void alpha(stud * head)
{   stud * final= head;
    stud * t1 = head;
    stud * t2 = head->next;
    while (t1!=NULL)
        {
            while(t2!=NULL)
                {
                    if(strcmp(t1->name, t2->name)<0)
                       {
                         strcpy(t1->name,t2->name);
                         t1->regno=t2->regno;
                         t1->marks[0]=t2->marks[0];
                         t1->marks[1]=t2->marks[1];
                         t1->marks[2]=t2->marks[2];
                       }
                    else
                        t2=t2->next;
                }
                t1=t1->next;
        }
    printf("Student list in Alphabetical Order \n");
    while(final!=NULL)
      {
            printf("Name : %s \n",final->name);
            printf("Regno: %d \n",final->regno);
            printf("Marks: %d %d %d ",final->marks[0],final->marks[1],final->marks[2]);
            final=final->next;
      }
}

