#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
/* Code to perform matrix multiplication
 * We are trying to take advantage of blocking here 
 */

int n,k,m;

void input_matrix( float *a,int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			a[i*c+j]=rand() % 20;
		}
	}
	
}

void initialise_matrix( float *a,int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			a[i*c+j]=0;
		}
	}
	
}

void print_matrix( float *a,int r ,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%f ",a[i*c+j]);
		}
		printf("\n");
	}	
}

void multiply_matrices (float *a, float *b, float *c , int ra,int ca,int rb,int cb)
{
	int i,j,p;
	omp_set_num_threads(10);
	#pragma omp parallel
	{ 
	
	#pragma omp for private(i,j,p)
	for(i=0; i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			for(p=0;p<k;p++)
			{
				c[i*cb+j]+= a[i*ca +p]*b[p*cb + j];
				/* Number of columns in c will be equal to the number of columns in b*/ 
			}
		}
	}
	//printf("threads=%d",omp_get_num_threads());
	}

}	 

int main()
{
	/*
	  n- no of rows in first matrix
	  k- no of columns in first matrix
	  m- no of columns in second matrix
	 */
	 
	
	printf("Enter the number of rows in the first matrix , number of columns in first and number of columns in second \n");
	scanf("%d%d%d",&n,&k,&m);
	
	
	float * a=(float*)(malloc)(sizeof(float)*n*k);
	float * b=(float*)(malloc)(sizeof(float)*k*m);
	float * c=(float*)(malloc)(sizeof(float)*n*m);
	
	input_matrix(a,n,k);
	input_matrix(b,k,m);
	initialise_matrix(c,n,m);
	
	clock_t t;
    	t = clock();
    	multiply_matrices(a,b,c,n,k,k,m);
    	t = clock() - t;
    	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	
	
	/*printf("\nMatrix A:\n");
	print_matrix(a,n,k);
	printf("\nMatrix B:\n");
	print_matrix(b,k,m);
	printf("\nMatrix C:\n");
	print_matrix(c,n,m);
	*/
	
	printf("\nTime taken = %f\n",time_taken);
}
