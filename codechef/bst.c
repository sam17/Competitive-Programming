#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
}Binary_Tree;

Binary_Tree *Createnode(int data)
{
	Binary_Tree *newnode;
	newnode=(Binary_Tree*)malloc(sizeof(Binary_Tree));
	newnode->data=data;
	newnode->left=NULL;	
	newnode->right=NULL;
	newnode->parent=NULL;
	return newnode;
}
void Insert(Binary_Tree *root,int data)
{

	if(data<root->data)
	{
		if(root->left==NULL)
		{
			root->left=Createnode(data);
			root->left->parent=root;
			//printf("Element Inserted\n");
		}
		else
			Insert(root->left,data);
	}
	else
	{
		if(root->right==NULL)
		{
			root->right=Createnode(data);
			root->right->parent=root;
			//printf("Element Inserted\n");
		}
		else
			Insert(root->right,data);		
	}
}

void Delete(Binary_Tree *root,int key)
{
	Binary_Tree *temp=NULL;	
	if(root==NULL)
	{
		printf("\nNo Data to be Deleted");
		return;
	}	
	if(root->data==key)
	{
		if(root->left==NULL && root->right==NULL)
		{
			if(key>root->parent->data)
				root->parent->right=NULL;
			else
				root->parent->left=NULL;
		}
		else if(root->left==NULL && root->right!=NULL)
		{
			root=root->right;
		}
		else if(root->left!=NULL && root->right==NULL)
		{
			root=root->left;
		}
		else if(root->left!=NULL && root->right!=NULL)
		{
			temp=root->right;			
			while(temp->left!=NULL)
			{
				temp=temp->left;
			}
			root->data=temp->data;
			temp->parent->left=NULL;
		}
		printf("\nElement Deleted");

	}
	else if(key<root->data)
		Delete(root->left,key);
	else Delete(root->right,key);	
}

void Visit(Binary_Tree *key)
{
	printf(" %d-> ",key->data);
}

void Tree_Traversal(Binary_Tree *root)
{
	if(root==NULL) return;
	Tree_Traversal(root->left);
	Visit(root);
	Tree_Traversal(root->right);
}

int main()
{
	int n,i,data;
	Binary_Tree *root;
	root=NULL;
	printf("Enter the number of inputs: ");	
	scanf("%d",&n);
	printf("\nEnter the inputs: ");
	scanf("%d",&data);	
	root=Createnode(data);	
	for(i=0;i<(n-1);i++)
	{
		scanf("%d",&data);
		Insert(root,data);
	}
	
	Tree_Traversal(root);

	printf("\nEnter the element to be deleted: ");
	scanf("%d",&data);
	Delete(root,data);

	Tree_Traversal(root);




	return 0;
}


