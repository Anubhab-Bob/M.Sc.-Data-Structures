/*
Problem Statement - Implementation of Undirected, non-weighted graph using incidence matrix
*/

#include <stdio.h>
#define MAX 10

void main()
{
	//Declare necessary variables
	int inc[MAX][MAX],v,e,i,j,n1,n2;
	
	//Accept the number of vertices
	printf("Enter the number of vertices : ");
	scanf("%d", &v);
	
	//Accept the number of edges
	printf("Enter the number of vertices : ");
	scanf("%d", &e);
	
	//Initializing the incidence matrix
	for(i=0;i<v;i++)
	{
		for(j=0;j<e;j++)
			inc[i][j]=0;
	}
	
	//Create the matrix
	for (i=0;i<e;i++)
	{
		printf("Enter the end vertices of edge %d : ", i+1);
		scanf("%d %d",&n1,&n2);
		n1--;
		n2--;
		if(((n1>=0)&&(n1<v))&&(n2<v)&&(n2>=0))
		{
			inc[n1][i]=1;
			inc[n2][i]=1;
		}
		else 
		{
			printf("Unavailable Vertex. Enter again\n");
			i--;
		}
	}
	
	//Displaying the adjacent matrix
	printf("\n\nThe adjacent matrix is :\n\n   \t");
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

