/*
Problem Statement - Implementation of BFS on an Undirected, non-weighted graph to get shortest path
*/

#include <stdio.h>
#define MAX 10

int adj[MAX][MAX],queue[MAX],visited[MAX],path[MAX],v=0,front=-1,rear=-1,dist=0;

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

void printer(int s,int d)
{
	if(s==d)
	{
		printf("%d",s+1);
		return;		
	}

	else
	{
		printer(s,path[d]);
		printf("---> %d",d+1);
	}
}

int bfs(int start,int d)
{
	int node,i,j;
	insert(start);
	printf("\n\n");
	do
	{
		node=del();
	//	if(visited[node]==0)
	//	{
			visited[node]=1;
			for(i=0;i<v;i++)
			{	
				if(adj[node][i]==1 && visited[i]==0)
				{
					visited[i]=1;
					path[i] = node;
					//printf("  ****   %d\n",node);
					if(i==d)
						return 1;
					dist++;
					insert(i);
				}	
			}
	//	}
		//printf("%d --> ",node);
		
	}
	while(front<=rear);
	return 0;
}



void main()
{
	//Declare necessary variables
	int i=0,j=0,e=0,n1=0,n2=0,node=0,dest=0,source=0;
	
	//Accept the number of nodes
	printf("Enter the no of vertices : ");
	scanf("%d",&v);
	
	//Initializing the adjacent matrix
	for(i=0;i<v;i++)
	{
		visited[i]=0;
		queue[i]=0;
		path[i]=0;
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
			adj[n2][n1]=1;
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
	
	
	printf("Enter the source : ");
	scanf("%d",&source);
	printf("Enter the destination : ");
	scanf("%d",&dest);
	//if(bfs(0)==1)
	//if(visited[dest]==0)
	//	printf("dist does not exist between the given vertices\n");
	//else
	//{
		if(bfs(source-1,dest-1))
		{
			node=dest-1;
			printf("The distance is = %d\n",dist);
			printer(source-1,dest-1);
		}
		else
			printf("Path does not exist\n");
	//}
}

