//-----------------------------------------------------------------------------------------------
//		Assignment 2-b (child)
//		Roll no. : 33346
//		Batch	 : M11
//-----------------------------------------------------------------------------------------------

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
void binary_search(int s[],int total)
{
	int n;
	printf("Enter value to search: \n");
	scanf("%d",&n);
	int left=0,right=total-1,middle;
	while(left<=right)
	{
		middle=(left+right)/2;
		if(s[middle]<n) //element in right half
		{
			left=middle+1;
		}
		else if(s[middle]>n) //element in left half
		{
			right=middle-1;
		}
		else //element found
		{
			printf("Found at location %d\n",middle+1);
			return;
		}
	}
	printf("\nNot Found");
	return;
}
int main(int argc,char* argv[], char *envp[]){
	int i, n=0,search;
	int ret[10];
	
	printf("\nCurrent process ID: %d\n", getpid());
	printf("\nParent process ID is %d\n", getppid());
	
	for(i=0; *argv[i]!='\0'; i++) //convert back to integer
	{
		ret[i] = strtol(argv[i+1], NULL, 10);
		n++;
	}
	binary_search(ret, n); //search
	return 0;
}
