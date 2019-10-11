/*

Problem Statement - Implementation of DFS for
					a) Undirected, non-weighted graph
					b) Directed, non-weighted graph
					c) Counting the number of components of a graph
					d) Identifying different types of edges of Undirected, non-weighted graph
					e) Identifying different types of edges of Directed, non-weighted graph
					
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structure to hold the DFS# and DFSC# of each node of the graph
//The DFS# and DFSC# are required to classify the different types of edges
typedef struct node
{
	int dfs;
	int dfsc;
}
marker;

//Declaring necessary variables
int **adj,*visited,v=0,e=0,directed=0,action;
char **vertices,v1[20],v2[20];
marker *marked;
int DFS=0,DFSC=0;

void dfs(int node)
{
	int i;
	if(visited[node]==0)
	{
		//Marking the node as visited
		visited[node]=1;
		if(action==3)
			marked[node].dfs=++DFS;
  		else
			printf("%s   ",vertices[node]);
	}
	for(i=0;i<v;i++)
	{
		//Moving to the next adjacent node
		if(visited[i]==0 && adj[node][i]==1)
		{
			if(action==3)
			{
				printf("%s ---> %s\n",vertices[node],vertices[i]);
				adj[node][i]=0;
			}
			dfs(i);
		}
	}
	if(action==3)
		marked[node].dfsc=DFSC++;
}

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
	int i=0,j=0,n1=0,n2=0;

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
		printf("V%d : ",i+1);
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
		printf("Enter the end vertices of edge %d : \n", i+1);
		scanf("%s%s",v1,v2);
		
		n1=map_Vertex(v1);
		n2=map_Vertex(v2);
		if((n1>=0)&&(n2>=0))
		{
			adj[n1][n2]=1;
			if(directed)
				continue;
			adj[n2][n1]=1;
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
	int i=0,j=0,n1=0,n2=0;

	//Matrix Input from File
	FILE* file = fopen ("graph_dfs1.txt", "r");

	//Accepting the number of nodes
	fscanf (file, "%d", &v);

	//Accepting the number edges
	fscanf (file, "%d", &e);

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
		
		fscanf(file, "%s %s" ,v1,v2);
		n1=map_Vertex(v1);
		n2=map_Vertex(v2);
		if((n1>=0)&&(n2>=0))
		{
			adj[n1][n2]=1;
			if(directed)
				continue;
			adj[n2][n1]=1;
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
	printf("\nThe adjacency matrix is :\n\n");
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
}

void main()
{
	//Declaring necessary variables
	int i,j,input_choice,cont,count=0;

	while(1)
	{
		printf("Enter choice of input : 1:Console\t2:File\t:");
		scanf("%d",&input_choice);

		//Creating the matrix as per the choice of input
		switch(input_choice)
		{
			case 1 :    printf("Is the graph directed(1) or non-directed(0) : ");
						scanf("%d",&directed);
						accept_Console();
						break;

			case 2 :    accept_File();
						break;

			default:    printf("Wrong Choice!\n");
						break;
		}
		//Memory Allocation and initialization for auxillary array
		visited=(int*)malloc(sizeof(int)*v);
		for(i=0;i<v;i++)
			visited[i]=0;

		//Displaying the adjacency matrix
		display();
		
  		//Accepting choice of further actions
		printf("Enter choice of action : \n1 : Print DFS Traversal\n2 : Count number of components\n");
		printf("3 : Identify the different types of edges\n4 : Stop\t\t : ");
		scanf("%d",&action);
		
		switch(action)
		{
			case 1 :    //Finding the DFS traversal of the graph
						printf("\nThe DFS traversal sequence is : \n");
						for(i=0;i<v;i++)                                //Loop used to move to next component
						{
							if(visited[i]==0)
							{
								printf("\nComponent %d : ",++count);
								dfs(i);
							}
						}
						printf("\n\n");
						break;
						
			case 2 :    printf("\nThe number of components is : %d",count);
						break;
						
			case 3 :    //Memory allocation for auxillary array
						marked=(marker*)malloc(sizeof(marker)*v);
						printf("\n\nThe Tree Edges are : \n");
						for(i=0;i<v;i++)
						{
							if(visited[i]==0)
								dfs(i);
						}
						
						printf("\n\nThe forward edges are :\n");
						for(i=0;i<v;i++)
						{
							for(j=0;j<v;j++)
							{
								if(adj[i][j]==1)
								{
									if(marked[i].dfs<marked[j].dfs && marked[i].dfsc>marked[j].dfsc)
										printf("%s ---> %s\n",vertices[i],vertices[j]);
								}
							}
						}

						printf("\n\nThe back edges are :\n");
						for(i=0;i<v;i++)
						{
							for(j=0;j<v;j++)
							{
								if(adj[i][j]==1)
								{
									if(marked[i].dfs>marked[j].dfs && marked[i].dfsc<marked[j].dfsc)
										printf("%s ---> %s\n",vertices[i],vertices[j]);
								}
							}
						}

						printf("\n\nThe cross edges are :\n");
						for(i=0;i<v;i++)
						{
							for(j=0;j<v;j++)
							{
								if(adj[i][j]==1)
								{
									if(marked[i].dfs>marked[j].dfs && marked[i].dfsc>marked[j].dfsc)
										printf("%s ---> %s\n",vertices[i],vertices[j]);
								}
							}
						}
						break;
			case 4 :    break;
			default:    printf("Wrong Choice!\n");
						break;
		}
		
		//Memory Deallocation
		for(i=0;i<v;i++)
		{
			free(adj[i]);
			free(vertices[i]);
		}
		free(adj);
		free(vertices);
		free(visited);
		free(marked);
		dist=0;
		
		printf("\n\nDo you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
	}
}
