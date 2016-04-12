#include"stdio.h"
#include"sys/time.h"
#include"stdlib.h"
#define N 4000
#define X 3000
#define Y 2000

int main()
{
	int sum = 0,i,j,k;
	int **mat1; //declared mat1[X][N]
	int **mat2; //declare mat2[N][Y]
 	int **mat_res; //resultant matrix become mat_res[X][Y]
 	struct timeval tim;
 	double t1,t2,result;
 	
 	/*----------------------------------------------------*/
	//create array of pointers(Rows)
 	mat1 =(int **) malloc(X*sizeof(int*));
 	mat2 =(int **)malloc(N*sizeof(int*));
 	mat_res=(int **)malloc(X*sizeof(int*));
 	/*----------------------------------------------------*/
 	
 	
 	/*--------------------------------------------------------------------------------*/
	//allocate memory for each Row pointer
 	for(i=0; i < X; i++)
 	{
 		mat1[i]=(int *)malloc(N*sizeof(int));
 		mat_res[i]=(int *)malloc(Y*sizeof(int));
 	}
 	
 	for(i=0;i<N;i++)
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
	
	gettimeofday(&tim, NULL);
	t1 = tim.tv_sec + (tim.tv_usec/1000000.0);
 	for(i = 0; i < X; i++)
 	{
 		for(j = 0; j < Y;j++)
 		{
 			sum=0;
 			for(k = 0; k < N; k++)
 			{
 				sum = sum + mat1[i][k] * mat2[k][j];
 			}
 			mat_res[i][j] = sum;
 		}
 	}
 	gettimeofday(&tim, NULL);
	t2 = tim.tv_sec + (tim.tv_usec/1000000.0);
	result = t2 - t1;
 	/*for(i = 0; i < X; i++)
 	{
	 	for(j = 0; j < Y; j++)
	 	{
	 		printf("%d\t",mat_res[i][j]);
	 	}
	 	printf("\n");
 	}*/
 	printf("time taken =%f\n",result);
 	return 0;
}
