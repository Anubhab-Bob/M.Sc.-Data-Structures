/*

Problem Statement - Generalised Implementation of adjacency matrix for
					a) Undirected, non-weighted Graph
					b) Undirected, weighted Graph
					c) Directed, non-weighted graph
					d) Directed, weighted graph
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Declaring necessary variables
int **adj,v=0,e=0,weighted=0,directed=0;
char **vertices,v1[20],v2[20];

int map_Vertex(char *x)
{
	int i;
	for(i=0;i<v;i++)
	{
		if(!strcmp(vertices[i], x))
			return i;
	}
	return -1;
}

int find_maxVertex()
{
	int len=0,i;
	for(i=0;i<v;i++)
	{
		if(strlen(vertices[i])>len)
			len=strlen(vertices[i]);
	}
	return len;
}

void accept_Console()
{
	//Declaring necessary variables
	int i=0,j=0,n1=0,n2=0,w;
	
	//Accepting the number of nodes
	printf("Enter the no of vertices : ");
	scanf("%d",&v);
	
	//Accepting the number of edges
	printf("Enter the no of edges : ");
	scanf("%d",&e);
	
	//Memory Allocation considering each vertex name to be of max 20 characters
	vertices=(char**)malloc(sizeof(char*)*v);
	for(i=0;i<v;i++)
		vertices[i]=(char*)malloc(sizeof(char)*20);
	
	//Memory Allocation for matrix
	adj=(int**)malloc(sizeof(int*)*v);
	for(i=0;i<v;i++)
		adj[i]=(int*)malloc(sizeof(int)*v);

	//Accepting the names of the vertices
	for(i=0;i<v;i++)
	{
		printf("V%d : ", i + 1);
		scanf("%s", vertices[i]);
	}
		
	//Initializing the adjacency matrix
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
			adj[i][j]=0;
	}
	
	//Creating the matrix
	for (i=0;i<e;i++)
	{
		if(weighted)
		{
			printf("Enter the end vertices of edge %d along with the edge weight : \n", i+1);
			scanf("%s%s%d",v1,v2,&w);
			if(w<1)
			{
				printf("Unacceptable edge weight. Enter again\n");
				i--;
				continue;
			}
		}
		else
		{
			printf("Enter the end vertices of edge %d : \n", i+1);
			scanf("%s%s",v1,v2);
			w=1;
		}
		
		n1=map_Vertex(v1);
		n2=map_Vertex(v2);
		if((n1>=0)&&(n2>=0))
		{
			adj[n1][n2]=w;
			if(directed)
				continue;
			adj[n2][n1]=w;
		}
		else
		{
			printf("Unavailable Vertex. Enter again\n");
			i--;
		}
	}
}

void accept_File()
{
	//Declaring necessary variables
	int i=0,j=0,n1=0,n2=0,w;
	
	//Matrix Input from File
	FILE* file = fopen ("graph.txt", "r");
	if (file==NULL)
	{
		printf("File Not Found!\n");
		return;
	}
	
	//Accepting the number of nodes
	fscanf (file, "%d", &v);
	
	//Accepting the number edges
	fscanf (file, "%d", &e);
	
	//Checking if the graph is weighted or not
	fscanf (file, "%d", &weighted);
	
	//Checking if the graph is directed or not
	fscanf (file, "%d", &directed);
	
	//Memory Allocation considering each vertex name to be of max 20 characters
	vertices=(char**)malloc(sizeof(char*)*v);
	for(i=0;i<v;i++)
		vertices[i]=(char*)malloc(sizeof(char)*20);
		
	//Memory Allocation
	adj=(int**)malloc(sizeof(int*)*v);
	for(i=0;i<v;i++)
		adj[i]=(int*)malloc(sizeof(int)*v);

	//Accepting the names of the vertices
	for(i=0;i<v;i++)
		fscanf(file,"%s", vertices[i]);
	
	//Initializing the adjacency matrix
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
			adj[i][j]=0;
	}
	
  	//Creating the matrix
	for (i=0;i<e;i++)
	{
		if(feof(file))
		{
			printf("Graph Input is not correct.\n");

			//Closing the file
			fclose (file);

   			//Terminating Program
			exit(0);
		}
		if(weighted)
			fscanf(file, "%s %s %d" ,v1,v2,&w);
  		else
		{
			fscanf(file, "%s %s" ,v1,v2);
			w=1;
		}
		
		n1=map_Vertex(v1);
		n2=map_Vertex(v2);
		if((n1>=0)&&(n2>=0))
		{
			adj[n1][n2]=w;
			if(directed)
				continue;
			adj[n2][n1]=w;
		}
		else
		{
			printf("Graph Input contains an unavailable vertex.\n");
			
			//Closing the file
			fclose (file);
			
   			//Terminating Program
			exit(0);
		}
	}
	
	if(!feof(file))
	{
		printf("Graph Input is not correct.\n");

		//Closing the file
		fclose (file);

  		//Terminating Program
		exit(0);
	}
	
	//Closing the file
	fclose (file);
}

void display()
{
	//Declaring necessary variables
	int i=0,j=0,width=find_maxVertex();
	//Displaying the adjacency matrix
	printf("\n\nThe adjacency matrix is :\n\n");
	for(i=0;i<v;i++)
		printf("\t%*s", width, vertices[i]);
	printf("\n\n");
	for(i=0;i<v;i++)
	{
		printf("%*s\t", width, vertices[i]);
		for(j=0;j<v;j++)
			printf("%*d\t", width, adj[i][j]);

		printf("\n\n");
	}
	
	//Memory Deallocation
	for(i=0;i<v;i++)
	{
		free(adj[i]);
		free(vertices[i]);
	}
	free(adj);
	free(vertices);
}

void main()
{
	//Declaring necessary variables
	int input_choice,cont;
	
	while(1)
	{
		printf("Enter choice of input : 1:Console\t2:File\t:");
		scanf("%d",&input_choice);
		
		//Creating the matrix as per the choice of input
		switch(input_choice)
		{
			case 1 :    printf("Is the graph weighted(1) or non-weighted(0) : ");
						scanf("%d",&weighted);
						printf("Is the graph directed(1) or non-directed(0) : ");
						scanf("%d",&directed);
						accept_Console();
						break;

			case 2 :    accept_File();
						break;

			default:    printf("Wrong Choice!\n");
						break;
		}
		
		//Displaying the matrix
		display();
		
		printf("Do you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
	}
}
