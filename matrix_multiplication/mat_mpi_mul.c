#include"stdio.h"
#include"stdlib.h"
#include"mpi.h"
#define N 400
#define X 300
#define Y 200
int main(int argc , char **argv)
{
	int size,rank,sum=0,i,j,k;
	int **mat1; //declared mat1[X][N]
	int **mat2; //declare mat2[N][Y]
 	int **mat_res; //resultant matrix become mat_res[X][Y]
 	double t1,t2,result;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	/*----------------------------------------------------*/
	//create array of pointers(Rows)
	mat1 =(int **)malloc(X * sizeof(int*));
 	mat2 =(int **)malloc(N * sizeof(int*));
 	mat_res=(int **)malloc(X * sizeof(int*));
	/*----------------------------------------------------*/
	
	
	/*--------------------------------------------------------------------------------*/
	//allocate memory for each Row pointer
	for(i = 0; i < X; i++)
 	{
 		mat1[i]=(int *)malloc(N * sizeof(int));
 		mat_res[i]=(int *)malloc(Y * sizeof(int));
 	}
 	
 	for(i = 0; i < N; i++)
 	mat2[i]=(int *)malloc(Y*sizeof(int));
	/*--------------------------------------------------------------------------------*/
	
	
	for(i = 0; i < X; i++)
	{
		for(j = 0; j < N; j++)
		{
			mat1[i][j] = 1; //initialize 1 to mat1 for all processes
		}
	}
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < Y; j++)
		{
			mat2[i][j] = 2;//initialize 2 to mat2 for all processes
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0)
	t1=MPI_Wtime();
	for(i = rank; i < X; i = i+size) //divide the task in multiple processes
	{
		for(j = 0; j < Y; j++)
		{
			sum=0;
			for(k = 0; k < N; k++)
			{
				sum = sum + mat1[i][k] * mat2[k][j];
			}
			mat_res[i][j] = sum;
		}
	}
	
	if(rank != 0)
	{
		for(i = rank; i < X; i = i+size)
		MPI_Send(&mat_res[i][0], Y, MPI_INT, 0, 10+i, MPI_COMM_WORLD);//send calculated rows to process with rank 0
	}
	
	if(rank == 0)
	{
		for(j = 1; j < size; j++)
		{
			for(i = j; i < X; i = i+size)
			{
				MPI_Recv(&mat_res[i][0], Y, MPI_INT, j, 10+i, MPI_COMM_WORLD, &status);//receive calculated rows from respective process
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank == 0)
	t2 = MPI_Wtime();
	result = t2 - t1;
	/*if(rank == 0)
	{
		for(i = 0; i < X; i++)
		{
			for(j = 0; j < Y; j++)
			{
				printf("%d\t",mat_res[i][j]); //print the result
			}
			printf("\n");
  	   }
	}*/
	if(rank == 0)
	printf("Time taken = %f seconds\n",result); //time taken
	MPI_Finalize();
	return 0;
}
