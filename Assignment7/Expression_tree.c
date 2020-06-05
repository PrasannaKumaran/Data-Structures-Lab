#include<string.h>
#include<ctype.h>
#include<stdlib.h>
struct stack_dia
{
    char data;
    struct stack_dia * next;
};
typedef struct stack_dia stack;
stack* top = NULL;
struct post_stack
{
    float data;
    struct post_stack *next;
};
typedef struct post_stack s;
s * top_post = NULL;
char post_fix_exp[30];
int k=0;
void push(char ch)
{
    stack * new_entry;
    new_entry=malloc(sizeof(stack));
    new_entry->data=ch;
    if(top == NULL)
        new_entry->next=NULL;
    else
        new_entry->next = top;
    top=new_entry;
}

void pop(char c)
{
    char ch;
    if(top == NULL)
        printf("Stack Empty \n");
    if(c==')')
		  {
              while(top->data != '(')
              {
                  stack *rem_entry= top;
                  ch=rem_entry->data;
                  post_fix_exp[k]=ch;
                  k++;
                  top = rem_entry->next;
                  free(rem_entry);
              }
              stack *rem_entry= top;
              ch=rem_entry->data;
              top = rem_entry->next;
              free(rem_entry);
          }
    else
    {
        stack *rem_entry= top;
        ch=rem_entry->data;
        top=rem_entry->next;
        post_fix_exp[k]=ch;
        k++;
        free(rem_entry);
        
        printf("postfix status : %s",post_fix_exp);
        
    }
}

char peek()
{	char ch;
    if (top == NULL)
        return '0';
    else
        ch=top->data;
    return ch;
}
int isoperator(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
        return 1;
    else
        return 0;
}

void in_to_post(char exp[30])
{
    char ch;
    for(int i=0;i<strlen(exp);i++)
    {
        if(isalnum(exp[i]))
        {
            post_fix_exp[k]=exp[i];
            k++;
        }
        else if(exp[i]=='(')
            push(exp[i]);
        else if (isoperator(exp[i]))
        {
            ch = peek();
            switch(ch)
            {
                case '+': if(exp[i]=='-')
                {
                    pop(exp[i]);
                    push('-');
                }
                else
                    push(exp[i]);
                    break;
                case '-': if(exp[i]=='+')
                {
                    pop(exp[i]);
                    push('+');
                }
                else
                    push(exp[i]);
                    break;
                case '*': if(exp[i]=='/')
                {
                    pop(exp[i]);
                    push('/');
                }
                else
                    push(exp[i]);
                    break;
                case '/': if(exp[i]=='*')
                {
                    pop(exp[i]);
                    push('*');
                }
                else
                    push(exp[i]);
                    break;
                default: push(exp[i]);
            }
        }
        else if (exp[i]==')')
            pop(exp[i]);
    }
}
void push_postfix(float ch)
{
    
    s * new_entry;
    new_entry=malloc(sizeof(s));
    new_entry->data=ch;
    if(top_post == NULL)
        new_entry->next=NULL;
    else	
        new_entry->next = top_post;
    top_post=new_entry;
}
char pop_postfix()
{	
    float ch;
    if (top_post == NULL)
        printf("Stack Empty \n");
    else
    {
        s * rem_entry = top_post;
        ch= rem_entry->data;
        top_post=rem_entry->next;
        free(rem_entry);
    }
  		return ch;
}

//“e_tree.h”

#include<stdlib.h>
#include<string.h>
#include"stack.h"
struct exp_tree
{
	char val;
	struct exp_tree * left;
	struct exp_tree * right;
	struct exp_tree * next;	
};
typedef struct exp_tree e;
struct exp_tree *top_tree_stack = NULL;
e * new_node(char ch)
{
	e * new_entry = malloc(sizeof(struct exp_tree));
	new_entry->val = ch;
	new_entry->left =NULL;
	new_entry->right =NULL;
	return new_entry;
}
void push_node_tree(e* nodes)
{
	if (top_tree_stack == NULL)
		nodes ->next = NULL;
	else
		nodes->next = top_tree_stack;
	top_tree_stack = nodes;
}
e* pop_node_tree()
{
	e* rem_entry = malloc(sizeof(struct exp_tree));
	if (top_tree_stack == NULL)
		printf("Stack Empty \n");
	else
	{
		rem_entry = top_tree_stack;
		top_tree_stack = top_tree_stack ->next;
	}	
	return rem_entry;
}
e* construct_exp_tree(char post_fix[30])
{
	e* t1,*t2,*t3;
	for (int i = 0;i < strlen(post_fix);i++)
	{
		if(!isoperator(post_fix[i]))
		{
			t1 = new_node(post_fix[i]);
			push_node_tree(t1);
		}
		else
		{
			t1 = new_node(post_fix[i]);
			t2 = pop_node_tree();
			t3 = pop_node_tree();
			t1->right = t2;
			t1->left = t3;
			push_node_tree(t1);
		}
	}
	e* t = pop_node_tree();
	return t;
}
void inorder( e* t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		printf(" %c ",t->val);
		inorder(t->right);
	}
}
void pre_order(e* t)
{
	if(t!=NULL)
	{
		printf(" %c ",t->val);
		pre_order(t->left);
		pre_order(t->right);
	}
}
void post_order(e* t)
{
	if(t!=NULL)
	{
		post_order(t->left);
		post_order(t->right);
		printf(" %c ",t->val);
	}
}

//main() - >”et.c”

#include<stdio.h>
#include"e_tree.h"
int main()
{
    char infix_exp[30];
    float post_eval=0.0;
    printf("Enter infix expression \n");
    scanf(" %[^\n]",infix_exp);
    in_to_post(infix_exp);
    if (top != NULL)
        printf("Unbalanced equation \n");
    else
        printf("Postfix expression is : %s \n",post_fix_exp);
    printf("Evaluation of Postfix expression \n");
    for (int i = 0 ; i < strlen(post_fix_exp);i++)
    {
        if(!isoperator(post_fix_exp[i]))
        {
            float n= post_fix_exp[i] -'0';
            push_postfix(n);
        }
        else
        {
            float x= pop_postfix() ;
            float y= pop_postfix();
            switch (post_fix_exp[i])
            {
                case '+' : post_eval = x + y;
                    push_postfix(post_eval);
                    break;
                    
                case '-' : post_eval = x - y;
                    push_postfix(post_eval);
                    break;
                    
                case '*' : post_eval = x * y;
                    push_postfix(post_eval);
                    break;
                    
                case '/' : post_eval = x / y;
                    push_postfix(post_eval);
                    break;
            }
        }
    }
    printf("%f ",post_eval);
    e* t = construct_exp_tree(post_fix_exp);
    printf("Inorder \n");
    inorder(t);
    printf("Preorder \n");
    pre_order(t);
    printf("Postorder \n");
    post_order(t);
    return 0; 
}

