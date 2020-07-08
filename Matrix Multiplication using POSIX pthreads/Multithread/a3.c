//-----------------------------------------------------------------------------------------------
//				Assignment 3
//	Roll no. : 33346
//	Batch	 : M11
//-----------------------------------------------------------------------------------------------

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int **p, **q,**mul,r1,r2,c1,c2,i,j,k;
int count=0;

int **create(int m,int n);
void input(int **m,int r,int c);
void display(int **m, int r, int c);
void *multiply(void *);

int main()
{	
	pthread_t tid[10];
	 		
	printf("Matrix 1:\n");
	printf("Number of rows:"); scanf("%d",&r1);
	printf("Number of columns:"); scanf("%d",&c1);
	p=create(r1,c1);
	
    	printf("Enter the elements of matrix:\n");
	input(p,r1,c1);
	
        printf("\nMatrix 2:\n");
	printf("Number of rows:"); scanf("%d",&r2);
	printf("Number of columns:"); scanf("%d",&c2);
	q=create(r2,c2);
	
    	printf("Enter the elements of matrix:\n");
	input(q,r2,c2);
				
        mul=create(r1,c2);
        
        if(c1!=r2)
        {
            printf("\n\nMultiplication not possible!!\n");
        }
        else
        {
                        
            printf("\n\nCreating threads!!\n");
            
            for(i=0; i<r1; i++)
            {
            	pthread_create(&tid[i],NULL,multiply,NULL);
            }
	    
            
            /*for(i=0; i<r1; i+=2)
	    {
	       for(j=0; j<c2; j++)
		{
		   *(*(mul+i)+j)=0;
		   for(k=0; k<c1; k++)
		   {
		       *(*(mul+i)+j)+=(*(*(p+i)+k))*(*(*(q+k)+j));
		   }
		}
	    }*/
	    
	    
	    printf("\n\nJoining threads!!\n");
	    for (i=0;i<r1;i++)
	    {
	    	pthread_join(tid[i],NULL);
	    }
	    
	    clock_t t;
    	    t = clock();
    	    t = clock() - t;
    	    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    	    printf("Time required : %f",time_taken);
	    
	    printf("\n\nMultiplication:\n");
            display(mul,r1,c2);
        }      
        return 0;
}

int **create(int m,int n)
{
        int **a,i;
        a=(int **)malloc(m*sizeof(int *));
        for(i=0;i<m;i++)
	   a[i]=(int *)malloc(n*sizeof(int));
        return(a);
}

void input(int **m,int r,int c)
{
	int i, j;
	for(i=0; i<r; i++)
	{
	for(j=0; j<c; j++)
	{
		scanf("%d", (*(m+i)+j));
	}

	}
}

void display(int **m, int r, int c)
{
	int i, j;
	for(i=0; i<r; i++)
	{
		for(j=0; j<c; j++)
		{
			printf("%d    ",*(*(m+i)+j));
		}
		printf("\n");
	}
}

void *multiply(void *para)
{   
   int index=count++;
       for(j=0; j<c2; j++)
        {
           *(*(mul+index)+j)=0;
           for(k=0; k<c1; k++)
           {
               *(*(mul+index)+j)+=(*(*(p+index)+k))*(*(*(q+k)+j));
           }
        }
    //printf("\n\nThread finished ...");
    pthread_exit(NULL);
}
