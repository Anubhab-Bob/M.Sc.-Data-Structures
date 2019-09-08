/*
Problem statement - Implementation of Undirected, weighted graph using Incidence matrix
*/

#include <stdio.h>
#define MAX 10

void main()
{
	//Declare necessary variables
	int inc[MAX][MAX],i=0,j=0,v=0,e=0,w=0,n1=0,n2=0;

	//Accept the number of nodes
	printf("Enter the no of vertices : ");
	scanf("%d",&v);

 	//Accept the number edges
	printf("Enter the no of edges : ");
	scanf("%d",&e);

	//Initializing the incidence matrix
	for(i=0;i<v;i++)
	{
		for(j=0;j<e;j++)
			inc[i][j]=99999;
	}

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
				inc[n1][i]=w;
				inc[n2][i]=w;
			}
			else
			{
				printf("Unavailable Vertex. Enter again\n");
				i--;
			}
		}
	}

	//Displaying the matrix
	printf("\n\nThe incidence matrix is :\n\n   \t");
	for(i=0;i<e;i++)
		printf(" E%d\t",i+1);
	printf("\n\n");
	for(i=0;i<v;i++)
	{
		printf(" V%d\t",i+1);
		for(j=0;j<e;j++)
			printf(" %d\t",inc[i][j]);

		printf("\n\n");
	}
}
