/*
Problem Statement - Consider a sequence of 'n' elements and construct an AVL tree
					after insertion of each element into the tree. Also perform deletion 
					of elements from the AVL tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int info;
	struct node *left;
	struct node *right;
}
node;

node *start=NULL;

node *createNode(int x)
{
	node *p=(node*)malloc(sizeof(node));
	p->info=x;
	p->left=NULL;
	p->right=NULL;
	return p;
}

void inorder(node *head)
{
	if(head!=NULL)
	{
		inorder(head->left);
		printf("%d\t",head->info);
		inorder(head->right);
	}
}

void postorder(node *head)
{
	if(head!=NULL)
	{
		postorder(head->left);
		postorder(head->right);
		printf("%d\t",head->info);
	}
}

void insert(node **head,int val)
{
	if(*head==NULL)
	{
		node *p=createNode(val);
		*head=p;
	}
	else if(val==(*head)->info)
		return;
	else if(val<(*head)->info)
		insert(&(*head)->left,val);
	else
		insert(&(*head)->right,val);
}



void accept_Console()
{
	int i,val;
	printf("Enter the number of nodes : ");
	scanf("%d",&i);
	printf("Enter the values :\n");
	while(i)
	{
		scanf("%d",&val);
		insert(&start,val);
		arrange(&start);
		i--;
		printf("\nInorder : ");
		inorder(start);
		printf("\nPostorder : ");
		postorder(start);
		printf("\n\n\n");
	}
}

void accept_File()
{
	//Declaring necessary variables
	int i,val;

	//Input from File
	FILE* file = fopen ("AVL.txt", "r");
	
	fscanf(file,"%d",&i);
	
	while(i)
	{
		fscanf(file,"%d",&val);
		insert(&start,val);
		arrange(&start);
		i--;
		printf("\nInorder : ");
		inorder(start);
		printf("\nPostorder : ");
		postorder(start);
		printf("\n\n\n");
	}
}

node** inorder_Successor(node **head)
{
	node *p=(*head)->right;
	while(1)
	{
		if(p->left!=NULL)
			p=p->left;
		else
			return &p;
	}
}

void rotateLeft(node **head)
{
	node *newHead=(*head)->right;
	(*head)->right=newHead->left;
	newHead->left=(*head);
	*head=newHead;
}

void rotateRight(node **head)
{
	node *newHead=(*head)->left;
	(*head)->left=newHead->right;
	newHead->right=(*head);
	*head=newHead;
}

int getHeight(node *head)
{
	if(head==NULL)
		return 0;
	else
	{
		int left=getHeight(head->left);
		int right=getHeight(head->right);
		if(left>right)
			return left+1;
		else
			return right+1;
	}
}

int arrange(node **head)
{
	if(*(head)==NULL)
		return 0;
	int rb=arrange(&(*head)->right);
	int lb=arrange(&(*head)->left);
	int left=getHeight((*head)->left);
	int right=getHeight((*head)->right);
	int balance=left-right;
	if(balance<-1)
	{
		printf("balance = %d at Node %d\nLeft Height = %d Right Height = %d\n",balance,(*head)->info,left,right);
		if(rb==-1)
		{
			rotateLeft(head);
			return 0; 		//Balance of the node will be 0 after rotation
		}
		else if(rb==1)
		{
			rotateRight(&(*head)->right);
			rotateLeft(head);
			return 0; 		//Balance of the node will be 0 after rotation
		}
	}
	else if(balance>1)
	{
		printf("balance = %d at Node %d\nLeft Height = %d Right Height = %d\n",balance,(*head)->info,left,right);

		if(lb==1)
		{
			rotateRight(head);
			return 0;
		}
		else if(lb==-1)
		{
			rotateLeft(&((*head)->left));
			rotateRight(head);
			return 0;
		}
	}
	return balance;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
node* deleteNode(node* root, int key)
{
    // base case
    if (root == NULL)
		return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    else if (key < root->info)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->info)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else if(key == root->info)
    {
        // node with only one child or no child
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

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        node **temp = inorder_Successor(&(root));

        // Copy the inorder successor's content to this node
        root->info = (*temp)->info;

        // Delete the inorder successor
        root->right = deleteNode(root->right, (*temp)->info);
    }
    else
		printf("Node doesn't exist!\n'");
    return root;
}

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
		printf("Enter choice of input : 1:Console\t2:File\t:");
		scanf("%d",&input_choice);

		//Creating the AVL Tree as per the choice of input
		switch(input_choice)
		{
			case 1 :    accept_Console();
						break;

			case 2 :    accept_File();
						break;

			case 3 :    
						break;
						
			default:    printf("Wrong Choice!\n");
						break;
		}

		printf("Do you want to perform deletion? 1:Yes\t2: No \t : ");
		scanf("%d",&deletion);
		if(deletion==1)
		{
			int rem;
			printf("Enter the node to delete : ");
			scanf("%d",&rem);
			start=(deleteNode(start,rem));
			printf("\nInorder : ");
			inorder(start);
			printf("\nPostorder : ");
			postorder(start);
			//
		}
		printf("\n\n\n'");
		printf("Do you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
  		// Free all the nodes for restating the operations
		freeAll();
		printf("\n\n\n'");
	}
}
