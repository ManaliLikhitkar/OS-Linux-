//-----------------------------------------------------------------------------------------------
//				Assignment 3
//	Roll no. : 33346
//	Batch	 : M11
//-----------------------------------------------------------------------------------------------

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int **p, **q;
int **mul;
int r1,r2,c1,c2,i,j,k;

int **create(int m,int n);
void input(int **m,int r,int c);
void display(int **m, int r, int c);
void *multiply(void *);

int main()
{	
	pthread_t tid;
	 		
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
                        
            printf("\n\nCreating thread!!\n");
	    pthread_create(&tid,NULL,multiply,NULL);
            
            for(i=0; i<r1; i+=2)
	    {
	       for(j=0; j<c2; j++)
		{
		   *(*(mul+i)+j)=0;
		   for(k=0; k<c1; k++)
		   {
		       *(*(mul+i)+j)+=(*(*(p+i)+k))*(*(*(q+k)+j));
		   }
		}
	    }
	    
	    pthread_join(tid,NULL);
	    
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
    for(i=1; i<r1; i+=2)
    {
       for(j=0; j<c2; j++)
        {
           *(*(mul+i)+j)=0;
           for(k=0; k<c1; k++)
           {
               *(*(mul+i)+j)+=(*(*(p+i)+k))*(*(*(q+k)+j));
           }
        }
    }
    printf("\n\nThread finished ...");
    pthread_exit(NULL);
}
