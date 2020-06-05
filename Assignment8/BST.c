#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
struct treenode
{
	char name[20];
	struct treenode * left;
	struct treenode * right;
};
struct treenode * makeempty(struct treenode *t)
{
	if(t!=NULL)
	{
		makeempty(t->left);
		makeempty(t->right);
		free(t);
	}
	return NULL;
}
struct treenode* find(char name[20], struct treenode * t)
{
	if( t == NULL)
		return NULL;
	if(strcmp(name,t->name)<0)
		return find(name, t->left);
	else if(strcmp(name,t->name)>0)
		return find(name , t->right);
	else
		return t;
}
struct treenode* findmin(struct treenode * t)
{
	if(t==NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findmin(t->left);
}
struct treenode * findmax(struct treenode * t)
{
	if(t!=NULL)
		while(t->right !=NULL)
			t = t->right;
	return t;
}
struct treenode * insert(char na[20] , struct treenode * t)
{
	if(t==NULL)
	{
		t = malloc(sizeof(struct treenode));
		if(t==NULL)
			printf("FATAL ERROR");
		else
			{
			strcpy(t->name,na);
			t->left = t->right = NULL;
			}
	}
	else if (strcmp(na,t->name)<0)
		t->left = insert(na, t->left);
	else if (strcmp(na,t->name)>0)
		t->right = insert(na, t->right);
	return t;
}
struct treenode* del (char na[20],struct treenode * t)
{
	struct treenode * temp;
	if (t==NULL)
		printf("Element not found");
	else if (strcmp(na,t->name)<0)
		t->left = del(na, t->left);
	else if(strcmp(na,t->name)>0)
		t->right = del(na, t->right);
	else if(t->left && t->right)
	{
		temp = findmin(t->right);
		strcpy(t->name, temp->name);
		t->right = del(t->name,t->right);
	}
	else
		{
		temp = t;
		if(t->left ==NULL)
			t=t->right;
		else if (t->right ==NULL)
			t = t->left;
		free(temp);
		}
		return t;
	}
struct treenode * findgp(char na[20], struct treenode *t)
{
  if(t->left)
  {
    if(t->left->left)
      if(strcmp(t->left->left->name,na)==0)
        return t;
    if(t->left->right)
      if(strcmp(t->left->right->name,na)==0)
        return t;
  }
  if(t->right)
  {
    if(t->right->left)
      if(strcmp(t->right->left->name,na)==0)
        return t;
    if(t->right->right)
      if(strcmp(t->right->right->name,na)==0)
        return t;
  }
  if(1)
  {
    if(strcmp(na,t->name)<0)
    {
      t=findgp(na,t->left);
      return t;
    }
    else if(strcmp(na,t->name)>0)
    {
      t=findgp(na,t->right);
      return t;
    }
  }
  return t;
}
void printgc(char na[20],struct treenode * t)
{
	while(t!=NULL)
	{
		if(strcmp(t->name,na))
			break;
		else if(strcmp(na,t->name)<0)
			t= t->left;
		else if (strcmp(na,t->name)>0)
			t= t->right;
	}
	if(t==NULL)
  {
    printf("Name not found \n ");
    return;
  }
  printf("Grandchildren are :\n");
  if(t->left)
  {
    if(t->left->left)
      printf("%s\n",t->left->left->name);
    if(t->left->right)
     printf("%s\n",t->left->right->name);
    }
  if(t->right)
  {
    if(t->right->left)
      printf("%s\n",t->right->left->name);
    if(t->right->right)
     printf("%s\n",t->right->right->name);
    }
}

void inorder(struct treenode *t )
{
 if(t!=NULL)
 {
 	inorder(t->left);
 	printf("%s  ",t->name);
 	inorder(t->right);
 }
}



//family.c

#include"bst.h"
#include<stdio.h>
int main()
{
	char name[20];
	struct treenode* t;
	t = makeempty(t);
	for(int i=0;i<12;i++)
	{
		printf("Enter the name of the person \n");
		scanf("%s",name);
		t = insert(name,t);
	}
	inorder(t);
	struct treenode * temp;
	printgc("Charan",t);
	temp = findgp("Lakshmi",t);
	printf("Grand Parent of Lakshmi : %s",temp->name);
	temp = findgp("Karthika" ,t );
	printf("Grand Parent of Karthika : %s",temp->name);
	temp = del("Ram",t);
	printf("Final tree \n");
	inorder(temp);
	return 0;
}

