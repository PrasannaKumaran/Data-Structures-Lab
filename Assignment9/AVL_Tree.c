#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct avlnode
{
	char English[30];
	char Tamizh[30];
	char Hindi[30];
	struct avlnode *left ;
	struct avlnode *right ;
	int height;
};
struct avlnode *makeempty(struct avlnode *t)
{
	if(t!=NULL)
	{
		makeempty(t->left);
		makeempty(t->right);
		free(t);
	}
	return NULL;
}
 int height(struct avlnode * p)
{
	if(p==NULL)
		return -1;
	else
		return p->height;
}
int max (int a,int b)
{
	return a>b?a:b;
}
static struct avlnode *singlerotatewithright(struct avlnode * k2)
{
	struct avlnode * k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left),height(k2->right))+1;
	k1->height = max(height(k1->right),height(k2))+1;
	return k1;
}
static struct avlnode *singlerotatewithleft(struct avlnode * k2)
{
	struct avlnode * k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left),height(k2->right))+1;
	k1->height = max(height(k1->left),(k2-> height))+1;
	return k1;
}
 static struct avlnode *doublerotatewithleft(struct avlnode * k3)
{ 
	k3->left = singlerotatewithright(k3->left);
	return singlerotatewithleft(k3);
}
 
static struct avlnode *doublerotatewithright(struct avlnode * k3)
{ 
	k3->right = singlerotatewithleft(k3->right);
	return singlerotatewithright(k3);
}
void inorder(struct avlnode *t)
{
	if (t!= NULL)
	{
		printf("%s" , t->English);
		inorder(t->left);
		inorder(t->right);
	}
}	
			char e[30];
			char ta[30];
			char h[30];

struct avlnode *insert (struct avlnode * t)
{
		
	if (t==NULL)
	{	
		t =(struct avlnode *)malloc(sizeof(struct avlnode));
		if(t==NULL)
			printf("Out of space \n");
		else
		{	
			printf("Enter English word \n");
			scanf(" %[^\n]",e);
			printf("Enter Tamizh Translation \n");
			scanf(" %[^\n]",ta);
			printf("Enter Hindi Translation \n");
			scanf(" %[^\n]",h);
			strcpy(t->English,e);
			strcpy(t->Hindi,h);
			strcpy(t->Tamizh,ta);
			t->height = 0;
			t->left=t->right=NULL;
		}
	}
	else if(strcmp(e,t->English)<0)
	{
		t->left = insert(t->left);
		if(height(t->left) - height(t->right) == 2)
		  {if (strcmp(e,t->left->English)<0)
		  	t = singlerotatewithleft(t);
		  else
		  	t = doublerotatewithleft(t);
		   }
	}

	else if(strcmp(e,t->English)>0)
	{
		t->right = insert(t->right);
		if(height(t->right) - height(t->left) == 2)
		  {if(strcmp(e,t->right->English)>0)
		  	t = singlerotatewithright(t);
		  else
		  	t = doublerotatewithright(t);
		   }
	}
	t->height = max(height(t->left),height(t->right))+1;
	return t;
}
struct avlnode *find(char x[50], struct avlnode * t)
{
	if(strcmp(x,t->English)<0)
		return find(x,t->left);
	else if (strcmp(x,t->English)>0)
		return find(x,t->right);
	return t;
} 
int main()
{
	int choice;
	char se[50];
	struct avlnode *t =NULL;
	do
	{
		printf("1. Insert \n");
		printf("2. Search \n");
		printf("3. Exit \n");
		printf("Enter choice \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 	
				t = insert(t);
				inorder(t);
				printf("\n");
				break;
			case 2: 
					printf("Enter english word to be searched\n");
					scanf(" %[^\n]",se);
					struct avlnode *temp = find(se,t);
					printf("Tamizh: %s  \n",temp->Tamizh);
					printf("Hindi: %s  \n",temp->Hindi);
		}
	}
	while(choice != 3);
	return 0;
}	

