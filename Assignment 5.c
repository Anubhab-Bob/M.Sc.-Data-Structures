/*

Problem Statement - Implementation of BFS on
					a) Undirected, non-weighted graph
					b) Directed, non-weighted graph
					c) Undirected, non-weighted graph to find the shortest path between 2 vertices
					d) Directed, non-weighted graph to find the shortest path between 2 vertices

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Declaring necessary variables
int **adj,*visited,v=0,e=0,directed=0,dist=0;
char **vertices,v1[20],v2[20];
int *path;
int *queue,front=-1,rear=-1;
int action;

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

int bfs(int start,int d)
{
	int node,i;
	insert(start);
	do
	{
		node=del();
		visited[node]=1;
		for(i=0;i<v;i++)
		{
			if(adj[node][i]==1 && visited[i]==0)
			{
				visited[i]=1;
				if(action==2)
				{
					path[i] = node;
					dist++;
					if(i==d)
						return 1;
				}
				insert(i);
			}
		}
		if(action!=2)
			printf("%s   ",vertices[node]);
	}
	while(front<=rear);
	return 0;
}

void printer(int s,int d)
{
	if(s==d)
	{
		printf("%s",vertices[s]);
		return;
	}
	else
	{
		printer(s,path[d]);
		printf(" ---> %s",vertices[d]);
	}
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
	FILE* file = fopen ("graph_bfs1.txt", "r");

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
		//Memory Allocation and initialization for auxillary arrays
		visited=(int*)malloc(sizeof(int)*v);
		queue=(int*)malloc(sizeof(int)*v);
		for(i=0;i<v;i++)
		{
			visited[i]=0;
			queue[i]=0;
		}	

		//Displaying the adjacency matrix
		display();

  		//Accepting choice of further actions
		printf("Enter choice of action : \n1 : Print BFS Traversal\n");
		printf("2 : Identify the Shortest path between 2 nodes\n3 : Stop\t\t : ");
		scanf("%d",&action);

		switch(action)
		{
			case 1 :    //Finding the BFS Traversal of the graph
						for(i=0;i<v;i++)                                //Loop used to move to next component
						{
							if(visited[i]==0)
							{
								printf("\nComponent %d : ",++count);
								bfs(i,v-1);
							}
						}
						break;
						
			case 2 :    printf("Enter the source : ");
						scanf("%s",&v1);
						printf("Enter the destination : ");
						scanf("%s",&v2);
						
						//Memory Allocation and initialization for auxillary array
						path=(int*)malloc(sizeof(int)*v);
						for(i=0;i<v;i++)
							path[i]=0;
							
						//Find shortest path only if path exists between the given nodes
						if(bfs(map_Vertex(v1),map_Vertex(v2)))
						{
       						printf("The distance is = %d\n",dist);
							printer(map_Vertex(v1),map_Vertex(v2));
						}
						else
							printf("Path does not exist\n");

						//Memory Deallocation
						free(path);
						break;
						
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
		free(queue);
		front=-1;
		rear=-1;
		dist=0;

		count=0;
		printf("\n\nDo you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
	}
}
