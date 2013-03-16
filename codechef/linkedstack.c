#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX 100
#define FLAG '#'

//Node of linked list
struct node
{
    int data;
    struct node *link;
};
struct node *top=NULL,*temp;

//Push in Linked Stack
void push(int data)
{
		temp=(struct node *)malloc(sizeof(struct node));
        temp->data=data;
        temp->link=top;
        top=temp;
}

//Pop in Linked Stack
int Pop()
{
	int temp;
	if(top!=NULL)
            {
		temp=top->data;
		top=top->link;                
		return temp;
            }
        else
            {
                printf("\nStack Underflow"); 
				return -1;   
            }
}

//Function to return the value at the top of linked stack
char ReturnTop()
{
	if(top!=NULL)return top->data;	
	else return -1;		
}

//Reverse String
void Reverse(char exp1[],int n)
{
	int i=0;
	char temp;
	while(i!=(n/2))
	{
		temp=exp1[i];		
		exp1[i]=exp1[n-i-1];
		exp1[n-i-1]=temp;	
		i++;
	}
}

//Evaluate Postfix expression
char Evaluate_Postfix(char expression[])
{

	int t,m,i=0;	
	while(expression[i]!='\0')
	{
		if(expression[i]=='+'||expression[i]=='-'||expression[i]=='*'||expression[i]=='/'||expression[i]=='@')
		{
			switch(expression[i])
			{
				case '+':	push(Pop()+Pop());
						break;	
				case '-':	t=-1*Pop();
							m=Pop();
							push(t+m);
						break;
				case '*':	push(Pop()*Pop());
						break;
				case '/':	push((1/Pop())*Pop());
						break;
				case '@':	push(0-Pop());
						break;
				//default:	
			}
		}
		else push(expression[i]-48);
		i++;
	}
	return Pop();
}

//Funtion to convert prefix to postfix
void PrefixtoPostfix(char prefix[],char postfix[],int n)
{
	int i=0,j=0;
	while(prefix[i]!='\0')
	{
		if(prefix[i]=='+'||prefix[i]=='-'||prefix[i]=='*'||prefix[i]=='/')
			push(prefix[i]);
		else 
		{
			if(prefix[i]=='@')
			{
				postfix[j++]=prefix[++i];
				postfix[j++]='@';
			}
			else
				postfix[j++]=prefix[i];
			while(ReturnTop()==FLAG)
			{
				Pop();
				postfix[j]=Pop();
				j++;
			}
			push(FLAG);
		}
		i++;
	}
	postfix[j]='\0';
	Pop();
}
//Main
int main()
{
	int n;
	char postfix_expression[MAX],prefix_expression[MAX],postfix[MAX],converted_postfix[MAX],conversion_prefix[MAX];    
		
	printf("PART I\nEnter the length: ");
	scanf("%d",&n);
	printf("Enter the postfix expression: ");
	scanf("%s",postfix_expression);
	printf("Enter the prefix expression: ");
	scanf("%s",prefix_expression);
	PrefixtoPostfix(prefix_expression,postfix,n);

	printf("The Answer to Prefix is: %d\n",Evaluate_Postfix(postfix));
	printf("The Answer to Postfix is: %d\n",Evaluate_Postfix(postfix_expression));
	
	printf("PART II\nEnter the length: ");
	scanf("%d",&n);
	printf("Enter the prefix expression: ");
	scanf("%s",conversion_prefix);	
	PrefixtoPostfix(conversion_prefix,converted_postfix,n);
	printf("The Converted Prefix to Postfix is: %s\n",converted_postfix);
	printf("The Answer to Postfix is: %d\n",Evaluate_Postfix(converted_postfix));	
	
	return 0;    
}
