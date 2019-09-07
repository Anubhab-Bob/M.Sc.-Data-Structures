/*
Problem Statement - Implementation of directed, weighted graph using adjacency matrix
*/

#include <stdio.h>
#define MAX 10

void main()
{
	//Declare necessary variables
	int adj[MAX][MAX],i=0,j=0,v=0,e=0,w=0,n1=0,n2=0;

	//Accept the number of nodes
	printf("Enter the no of vertices : ");
	scanf("%d",&v);

	//Initializing the adjacent matrix
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
			adj[i][j]=0;
	}

	//Accept the number edges
	printf("Enter the no of edges : ");
	scanf("%d",&e);

	//Create the matrix
	for (i=0;i<e;i++)
	{
		printf("Enter the end vertices of edge %d along with the edge weight : ", i+1);
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
			{
				adj[n1][n2]=w;
				//adj[n2][n1]=w;
			}
			else
			{
				printf("Unavailable Vertex. Enter again\n");
				i--;
			}
		}
	}

	//Displaying the adjacent edges
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
}

