/*
Problem Statement - Implementation of directed, weighted graph using adjacency list
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 4

typedef struct Node
{
	int vertexNum;
	int weight;
	struct Node *next;
}
vertex;

typedef struct List
{
	vertex *head;
}
List;

List *adjList[MAX];

void newEdge(int s,int d,int w)
{
	vertex *dest, *current;
	
	dest=(vertex*)malloc(sizeof(vertex));
	dest->vertexNum=d+1;
	dest->weight=w;
	dest->next=NULL;
	if(adjList[s]->head==NULL)
		adjList[s]->head=dest;
	else
	{
		current=adjList[s]->head;
		while(current->next!=NULL)
			current=current->next;
		current->next=dest;
	}
}

void printList(int size)
{
	int i;
	printf("\n\nThe adjacent matrix is :\n\n   \t");

	for(i=0;i<size;i++)
	{
		vertex *current=adjList[i]->head;
		printf("\n\nV%d --------> ",i+1);
		while(current)
		{
			printf("V%d(%d) \t",current->vertexNum,current->weight);
			current=current->next;
		}
	}
}

void main()
{
	int i,v,e,n1,n2,w;

	//Accept the number of nodes
	do
	{
		printf("Enter the no of vertices : ");
		scanf("%d",&v);
		if((v>0)&&(v<=MAX))
			break;
		printf("Wrong Input. Enter Again.\n");
	}
	while(v>MAX);

	//Accept the number edges
	printf("Enter the no of edges : ");
	scanf("%d",&e);

	//Initializing the adjacent list
	for(i=0;i<v;i++)
	{
		adjList[i]=(List*)malloc(sizeof(List));
		adjList[i]->head=NULL;
	}

	//Create the List
	for (i=0;i<e;i++)
	{
		printf("Enter the end vertices of edge and the weight : ", i+1);
		scanf("%d %d %d",&n1,&n2,&w);
		n1--;
		n2--;
		if(w<1)
		{
			printf("Unacceptable edge weight. Enter again\n");
			i--;
		}
		else
		{
			if(((n1>=0)&&(n1<v))&&(n2<v)&&(n2>=0))
			newEdge(n1,n2,w);
			else
			{
				printf("Unavailable Vertex. Enter again\n");
				i--;
			}
		}
	}

	//Displaying the adjacent list
	printList(v);
}
