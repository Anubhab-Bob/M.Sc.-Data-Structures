/*

Devise a scheme to represent a sparse matrix A & transpose this representation of A in lexicographic order.

*/

#include <stdio.h>
#include <stdlib.h>

int **A,r,c,count=0,**sparse,**trans;

void accept_Console()
{
	int i=0,j=0,flag=0;
	printf("Enter no. of rows : ");
	scanf("%d",&r);
	printf("Enter no. of columns : ");
	scanf("%d",&c);

	//Memory Allocation
	A=(int**)malloc(sizeof(int*)*r);
	for(i=0;i<r;i++)
		A[i]=(int*)malloc(sizeof(int)*c);

	//Matrix Input
	printf("Enter the values row-major wise : \n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			scanf("%d",&A[i][j]);
			if(A[i][j])
				count++;
		}
	}
}

void display()
{
	int i, j;

	//Matrix Output
	printf("The Matrix is : \n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
			printf("%d\t",A[i][j]);
		printf("\n");
	}
}

void accept_File()
{
	int i=0,j=0,flag=0;
	
	//Matrix Input from File
	FILE* file = fopen ("matrix.txt", "r");
	if (file==NULL)
	{
		printf("File Not Found!\n");
		return;
	}

	//Accept the number of rows
	fscanf (file, "%d", &r);
	
	//Accept the number of columns
	fscanf (file, "%d", &c);
	
	//Memory Allocation
	A=(int**)malloc(sizeof(int*)*r);
	for(i=0;i<r;i++)
		A[i]=(int*)malloc(sizeof(int)*c);

	//Accept the elements of the matrix
  	while (1)
    {
    	for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				if(feof(file))
				{
					flag=1;
					break;
				}
				fscanf (file, "%d", &A[i][j]);
				if(A[i][j])
					count++;
			}
			if(flag)
				break;
		}
		if(flag)
			break;
    }
    
    //Closing the file
	fclose (file);
}


void sparse_rep()
{
	int i,j,m;
	
	//Memory Allocation
	sparse=(int**)malloc(sizeof(int*)*count);
	for(i=0;i<count;i++)
		sparse[i]=(int*)malloc(sizeof(int)*3);
	
	//Sparse Representation
	for(i=0,m=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(A[i][j])
			{
				sparse[m][0]=i;
				sparse[m][1]=j;
				sparse[m][2]=A[i][j];
				m++;
			}
		}
	}
	
	//Sparse Representation Output
	printf("\nThe Sparse Representation is : \n");
	for(i=0;i<count;i++)
	{
		for(j=0;j<3;j++)
		{
			if(j!=2)
				printf("%d\t",sparse[i][j]+1);
			else
				printf("%d\t",sparse[i][j]);
		}
		printf("\n");
	}
}

void sparse_trans()
{
	int i,j,m;
	
	//Memory Allocation
	trans=(int**)malloc(sizeof(int*)*count);
	for(i=0;i<count;i++)
		trans[i]=(int*)malloc(sizeof(int)*3);
		
	for(j=0,m=0;j<c;j++)
	{
		for(i=0;i<count;i++)
		{
			if(sparse[i][1]==j)
			{
				trans[m][0]=j;
				trans[m][1]=sparse[i][0];
				trans[m][2]=sparse[i][2];
				m++;
			}
		}
	}

	//Sparse Representation Output
	printf("\nThe Ordered Sparse Transpose is : \n");
	for(i=0;i<count;i++)
	{
		for(j=0;j<3;j++)
  		{
			if(j!=2)
				printf("%d\t",trans[i][j]+1);
			else
				printf("%d\t",trans[i][j]);
		}
		printf("\n");
	}
}

void main()
{
	//Declaring necessary variables
	int i,input_choice,cont;
	
	while(1)
	{
		printf("Enter choice of input : 1:Console\t2:File\t:");
		scanf("%d",&input_choice);

		//Creating the matrix as per the choice of input
		switch(input_choice)
		{
			case 1 :	accept_Console();
						break;

			case 2 :    accept_File();
						break;

			default:    printf("Wrong Choice!\n");
						break;
		}
		
		display();
    	sparse_rep();
		sparse_trans();
		
		//Memory Deallocation
		for(i=0;i<r;i++)
			free(A[i]);
		for(i=0;i<count;i++)
		{
			free(sparse[i]);
			free(trans[i]);
		}
		free(A);
		free(sparse);
		free(trans);

		count=0;
		printf("\nDo you want to repeat? : 1:Yes\t2:No:\t");
		scanf("%d",&cont);
		if(cont!=1)
			break;
	}
}
