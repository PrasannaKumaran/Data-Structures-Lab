	#include<string.h>
	#include<ctype.h>
	#include<stdlib.h>
	struct stack_dia
	{
		char data;
		struct stack_dia * next;
	};
	typedef struct stack_dia stack;
	stack * top = NULL;	
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
  	
#include<stdio.h>
#include"stack.h"
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
    return 0; 
}

