//-----------------------------------------------------------------------------------------------
//		Assignment 2-b (main)
//		Roll no. : 33346
//		Batch	 : M11
//-----------------------------------------------------------------------------------------------

#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>

void quicksort(int number[],int first,int last)
{
   int i, j, pivot, temp;

   if(first<last)
   {
      pivot=first;
      i=first;
      j=last;

      while(i<j)
      {
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j)
         {
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}

int main()
{
	int pid, ppid, a[10], size, i;
	char *argv[12];
	
	//Dynamic memory allocation
	for(i=0; i<12; i++)
	{
		argv[i] = (char *) malloc(20);
	}

	
	//Total number of elements
	printf("Enter total number of elements: ");
	scanf("%d",&size);
	
	
	//Elements of array
	printf("\nEnter elements : \n");
	
	for(i=0;i<size;i++)
	{
		scanf("%d",&a[i]);
	}
	
	//Sorting array
	quicksort(a,0,size-1);
	
	printf("Sorted array:\n");
	for(i=0;i<size;i++)
	{
		printf("%d	",a[i]);
	}
	
	pid=getpid();
	printf("\nCurrent Process id is:\t%d", pid);
	printf("\nForking...\n");
	
	pid=fork();
		
	if(pid<0)	//creation failed
	{
		printf("\nProcess creation failed!");
		exit(-1);
	}
	else if(pid==0)		//child process
	{
		//printing process IDs
		printf("\nChild Process started!");
		printf("\nProcess ID is: %d", getpid());
		printf("\nParent Process ID is: %d\n", getppid());
		
		
		//converting int to character
		for(i=0; i<size; i++)
		{
			sprintf(argv[i+1], "%d", a[i]);
		}
	
		argv[0] = "./a2";
        	argv[size+2] ='\0';

		execv("./a2", argv);//call exec function
		printf("\nChild is dying now\n\n");
	}
	else		//parent process
	{
		system("wait");
		printf("\nParent Process");
		printf("\nProcess ID is:\t%d", getpid());
		printf("\nParent Process ID is:\t%d\n", getppid());
	}	
	return 0;
}
