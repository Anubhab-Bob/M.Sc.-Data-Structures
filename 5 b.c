/*
Problem Statement - Implementation of BFS on an Undirected, non-weighted graph
*/

#include <stdio.h>
#define MAX 10

int adj[MAX][MAX],queue[MAX],visited[MAX],v=0,front=-1,rear=-1;

void insert(int x)
{
	if(rear==-1)
		front++;
	queue[++rear]=x;
}

int del()
{
	return(queue[front++]);
}

int bfs(int start)
{
	int node,i,j;
	insert(start);
	printf("\n\n");
	do
	{
		node=del();
		if(visited[node]==0)
		{
			visited[node]=1;
			for(i=0;i<v;i++)
			{	
				if(adj[node][i]==1 && visited[i]==0)
				{
					visited[i]=0;
					insert(i);
				}	
			}
		}
		printf("%d --> ",node);
	}
	while(front<=rear);
}

void main()
{
	//Declare necessary variables
	int i=0,j=0,e=0,n1=0,n2=0,count=0;
	
	//Accept the number of nodes
	printf("Enter the no of vertices : ");
	scanf("%d",&v);
	
	//Initializing the adjacent matrix
	for(i=0;i<v;i++)
	{
		visited[i]=0;
		queue[i]=0;
		for(j=0;j<v;j++)
			adj[i][j]=0;
	}
	
	//Accept the number edges
	printf("Enter the no of edges : ");
	scanf("%d",&e);
	
	//Create the matrix
	for (i=0;i<e;i++)
	{
		printf("Enter the end vertices of edge %d : ", i+1);
		scanf("%d %d",&n1,&n2);
		n1--;
		n2--;
		if(((n1>=0)&&(n1<v))&&(n2<v)&&(n2>=0))
		{
			adj[n1][n2]=1;
			//adj[n2][n1]=1;
		}
		else 
		{
			printf("Unavailable Vertex. Enter again\n");
			i--;
		}
	}
	
	//Displaying the adjacent matrix
	printf("\n\nThe adjacent matrix is :\n\n   \t");
	for(i=0;i<v;i++)
		printf(" V%d\t",i+1);
	printf("\n\n");
	for(i=0;i<v;i++)
	{
		printf(" V%d\t",i+1);
		for(j=0;j<v;j++)
			printf(" %d\t",adj[i][j]);

		printf("\n\n");
	}
	
	for(i=0;i<v;i++)
	{
		if(visited[i]==0)
		{
			printf("\nComponent %d : ",++count);
			bfs(i);
		}
	}
	//bfs(0);
}

