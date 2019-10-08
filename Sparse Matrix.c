/*

Devise a scheme to represent a sparse matrix A & transpose this representation of A in lexicographic order.

*/

#include <stdio.h>
#include <malloc.h>

int **A,r,c,count=0,**sparse,**trans;

void accept()
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

	//Matrix Input from File
	FILE* file = fopen ("matrix.txt", "r");
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
	fclose (file);

	//Matrix Input
	/*printf("Enter the values row-major wise : \n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			scanf("%d",&A[i][j]);
			if(A[i][j])
				count++;
		}
	}*/
	
	//Matrix Output
	printf("The Matrix is : \n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
			printf("%d\t",A[i][j]);
		printf("\n");
	}
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
			printf("%d\t",sparse[i][j]);
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
			//printf("%d *** %d *** %d *** %d\n",i,j,m,A[i][j]);
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
			printf("%d\t",trans[i][j]);
		printf("\n");
	}
}

void main()
{
	accept();
	sparse_rep();
	sparse_trans();
}
