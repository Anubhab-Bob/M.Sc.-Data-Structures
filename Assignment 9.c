/*
Problem Statement - Consider a sequence of 'n' elements and construct an AVL tree
					after insertion of each element into the tree. Also perform deletion
					of elements from the AVL tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Define Structure of individual nodes of AVL Tree
typedef struct node
{
	char info[10];      //Maximum length of the nodes is set to 10
	struct node *left;
	struct node *right;
}
node;

//Declare the start pointer
node *start=NULL;

int flag;       //This tells if the nodes are numbers or strings

//Function to compare 2 strings as numbers
int compare(char *s1,char *s2)
{
	int s1_size=strlen(s1), s2_size=strlen(s2);
	int size=s1_size-s2_size;
	
	//Number with more digits is larger
	if(size)
		return size;
		
	int i=0,j=0;
	for(i=0;i<s1_size;i++)
	{
		if(s1[i]!=s2[i])
			return (((int)s1[i])-((int)s2[i]));
	}
	
	//Return 0 if the strings match
	return 0;
}

//Function to create a node of the tree with a given value
node *createNode(char *x)
{
	node *p=(node*)malloc(sizeof(node));
	strcpy(p->info,x);
	p->left=NULL;
	p->right=NULL;
	return p;
}

//Function for inorder traversal of the tree
void inorder(node *head)
{
	if(head!=NULL)
	{
		inorder(head->left);
		printf("%s\t",head->info);
		inorder(head->right);
	}
}

//Function for postorder traversal of the tree
void postorder(node *head)
{
	if(head!=NULL)
	{
		postorder(head->left);
		postorder(head->right);
		printf("%s\t",head->info);
	}
}

//Function to insert a new node in the tree
void insert(node **head,char *val)
{
	if(*head==NULL)
	{
		node *p=createNode(val);
		*head=p;
	}
	
	//Compare using library function if the nodes have strings
	else if(flag)
	{
		if(strcmp(val,(*head)->info)==0)
			return;
		else if(strcmp(val,(*head)->info)<0)
			insert(&(*head)->left,val);
		else
			insert(&(*head)->right,val);
	}
	
	//Compare using self-defined function if the nodes have numbers
	else
	{
		if(compare(val,(*head)->info)==0)
			return;
		else if(compare(val,(*head)->info)<0)
			insert(&(*head)->left,val);
		else
			insert(&(*head)->right,val);
	}
}

//Function to accept input from console
void accept_Console()
{
	int i,choice;
	char val[10];
	printf("Enter the number of nodes : ");
	scanf("%d",&i);
	printf("Enter choice of values : 1:Numbers\t2:Strings\t:");
	scanf("%d",&choice);
	if(choice==1)
		flag=0;
	else if(choice==2)
		flag=1;
	else
	{
	 	printf("Wrong Choice!\n");
		return;
	}
	printf("Enter the values :\n");
	while(i)
	{
		scanf("%s",&val);
		insert(&start,val);
		arrange(&start);
		i--;
		printf("\nInorder : ");
		inorder(start);
		printf("\nPostorder : ");
		postorder(start);
		printf("\n\n");
	}
}

//Function to accept input from console
void accept_File()
{
	//Declaring necessary variables
	int i,choice;
	char val[10];

	//Input from File
	FILE* file = fopen ("AVL.txt", "r");

	//Accept the number of nodes
	fscanf(file,"%d",&i);
	
	//Accept the type of nodes
	fscanf(file,"%d",&choice);
	if(choice==1)
		flag=0;
	else if(choice==2)
		flag=1;
	else
	{
	 	printf("Wrong Choice!\n");
		return;
	}
	
	//Accept the values
	while(i)
	{
		fscanf(file,"%s",&val);
		insert(&start,val);
		arrange(&start);
		i--;
		printf("\nInorder : ");
		inorder(start);
		printf("\nPostorder : ");
		postorder(start);
		printf("\n\n");
	}
}

//Function to find the inorder successor of a node
node** inorder_Successor(node **head)
{
	//The right subtree contains the inorder successor
	node *p=(*head)->right;
	
	while(1)
	{
		if(p->left!=NULL)
			p=p->left;
		else
			return &p;
	}
}

//Function to perform AVL Left Rotate operation
void rotateLeft(node **head)
{
	node *newHead=(*head)->right;
	(*head)->right=newHead->left;
	newHead->left=(*head);
	*head=newHead;
}

//Function to perform AVL Left Rotate operation
void rotateRight(node **head)
{
	node *newHead=(*head)->left;
	(*head)->left=newHead->right;
	newHead->right=(*head);
	*head=newHead;
}

//Function to get height of the subtree having 'head' as the root
int getHeight(node *head)
{
	if(head==NULL)
		return 0;
	else
	{
		//Height f the subtree is the maximum height of its children + 1
		int left=getHeight(head->left);
		int right=getHeight(head->right);
		if(left>right)
			return left+1;
		else
			return right+1;
	}
}

//Function to rearrange the nodes of the tree if the BF goes beyond limit
int arrange(node **head)
{
	if(*(head)==NULL)
		return 0;
		
	//Arrange any subtree before trying to arrange the current node
	int rb=arrange(&(*head)->right);
	int lb=arrange(&(*head)->left);
	int left=getHeight((*head)->left);
	int right=getHeight((*head)->right);
	
	//Calculate the BF
	int balance=left-right;
	
	if(balance<-1)
	{
		printf("balance = %d at Node %s\nLeft Height = %d Right Height = %d\n",balance,(*head)->info,left,right);
		
		//Case of Right High
		if(rb==-1)
		{
			rotateLeft(head);
			return 0; 		//Balance of the node will be 0 after rotation
		}
		
		//Case of Left High
		else if(rb==1)
		{
			rotateRight(&(*head)->right);
			rotateLeft(head);
			return 0; 		//Balance of the node will be 0 after rotation
		}
	}
	else if(balance>1)
	{
		printf("balance = %d at Node %s\nLeft Height = %d Right Height = %d\n",balance,(*head)->info,left,right);
		
		//Case of Right High (mirror image)
		if(lb==1)
		{
			rotateRight(head);
			return 0;
		}
		
		//Case of Left High (mirror image)
		else if(lb==-1)
		{
			rotateLeft(&((*head)->left));
			rotateRight(head);
			return 0;
		}
	}
	return balance;
}

//Function to delete the key and return the new root
node* deleteNode(node* root, char *key)
{
    //Base case
    if (root == NULL)
		return root;

	//Compare using library function if the nodes have strings
    else if (flag)
	{
		//If the key to be deleted is smaller than the root's key,
    	//then it lies in left subtree
		if(strcmp(key,root->info)<0)
			root->left = deleteNode(root->left, key);
			
		//If the key to be deleted is greater than the root's key,
    	//then it lies in right subtree
    	else if (strcmp(key,root->info)>0)
        	root->right = deleteNode(root->right, key);
        	
		//If key is same as root's key, then This is the node
    	//to be deleted
    	else if(strcmp(key,root->info)==0)
    	{
	        //Node with only one child or no child
    	    if (root->left == NULL)
        	{
	            node *temp = root->right;
    	        free(root);
        	    return temp;
	        }
    	    else if (root->right == NULL)
        	{
            	node *temp = root->left;
	            free(root);
    	        return temp;
        	}

	        //Node with two children: Get the inorder successor (smallest in the right subtree)
        	node **temp = inorder_Successor(&(root));

	        //Copy the inorder successor's content to this node
    	    strcpy(root->info, (*temp)->info);

    	    //Delete the inorder successor
        	root->right = deleteNode(root->right, (*temp)->info);
    	}
    	else
			printf("Node doesn't exist!\n'");
	}
	//Compare using self-defined function if the nodes have numbers
	else
	{
		//If the key to be deleted is smaller than the root's key,
    	//then it lies in left subtree
		if(compare(key,root->info)<0)
			root->left = deleteNode(root->left, key);

		//If the key to be deleted is greater than the root's key,
    	//then it lies in right subtree
    	else if (compare(key,root->info)>0)
        	root->right = deleteNode(root->right, key);

		//If key is same as root's key, then This is the node
    	//to be deleted
    	else if(compare(key,root->info)==0)
    	{
	        //Node with only one child or no child
    	    if (root->left == NULL)
        	{
	            node *temp = root->right;
    	        free(root);
        	    return temp;
	        }
    	    else if (root->right == NULL)
        	{
            	node *temp = root->left;
	            free(root);
    	        return temp;
        	}

	        //Node with two children: Get the inorder successor (smallest
    	    //in the right subtree)
        	node **temp = inorder_Successor(&(root));

	        //Copy the inorder successor's content to this node
    	    strcpy(root->info, (*temp)->info);

    	    //Delete the inorder successor
        	root->right = deleteNode(root->right, (*temp)->info);
    	}
    	else
			printf("Node doesn't exist!\n'");
	}
    return root;
}

//Function to delete all nodes of the tree and free all the pointers
void freeAll()
{
	while(start!=NULL)
		start=deleteNode(start,start->info);
}

void main()
{
	//Declaring necessary variables
	int input_choice,deletion,cont;

	while(1)
	{
		//Accept the choice of input
		printf("Enter choice of input : 1:Console\t2:File\t:");
		scanf("%d",&input_choice);
			
		//Creating the AVL Tree as per the choice of input
		switch(input_choice)
		{
			case 1 :    accept_Console();
						break;

			case 2 :    accept_File();
						break;

			default:    printf("Wrong Choice!\n");
						break;
		}

		printf("Do you want to perform deletion? 1:Yes\t2: No \t : ");
		scanf("%d",&deletion);
		if(deletion==1)
		{
			char rem[10];

			//Accept the node to delete
			printf("Enter the node to delete : ");
			scanf("%s",&rem);
			
			//Hold the new root node in 'start' after deletion
			start=(deleteNode(start,rem));
			
			//Display the tree
			printf("\nInorder : ");
			inorder(start);
			printf("\nPostorder : ");
			postorder(start);
		}
		printf("\n\n\n'");
		
		//Accept the choice for repetition
		printf("Do you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
			
  		// Free all the nodes for restating the operations
		freeAll();
		printf("\n\n\n'");
	}
}
