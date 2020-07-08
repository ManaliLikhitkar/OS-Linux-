#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
#define READ_END1 0
#define WRITE_END1 1

int main(void)
{
	char write_msg[BUFFER_SIZE]="abc.txt";
	//char read_msg[BUFFER_SIZE];
	//char write_msg1[BUFFER_SIZE]="PICT";
	char read_msg1[BUFFER_SIZE];
	int fd[2],fd1[2];
	pid_t pid;
	
	
	/* create the pipe */
	if (pipe(fd) == -1) 
	{
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	if (pipe(fd1) == -1) 
	{
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	
	/* fork a child process*/
	pid = fork();
	
	if (pid < 0) 
	{ 
		/* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	if (pid > 0) 
	{ 
		/* parent process */
		
		/*1st*/
		/* close the unused end of the pipe*/
		close(fd[READ_END]);
		
		/* write to the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		
		/*close the write end of the pipe*/
		close(fd[WRITE_END]);
		
		sleep(4);
		
		/*2nd*/
		/* close the unused end of the pipe*/
		close(fd1[WRITE_END1]);
		
		/* read from the pipe */
		read(fd1[READ_END1], read_msg1, BUFFER_SIZE);
		
		//printf ("%s", read_msg1) ;
		
		/*close the write end of the pipe*/
		close(fd1[READ_END1]);
		
		FILE *fp;
		char str1[20];
		fp=fopen(read_msg1,"r");
		fscanf(fp,"%s",str1);
		/*while(str1!=EOF)
		{
			printf("%s",str1);
		        fscanf(fp,"%s",str1);		
		}*/
		printf("%s",str1);
		fclose(fp);
	}
	else 
	{ 
		/* child process */
		
		/*1st*/
		/* close the unused end of the pipe*/
		close(fd[WRITE_END]);
		
		/* read from the pipe */
		read(fd[READ_END], read_msg1, BUFFER_SIZE);
		
		/*close the read end of the pipe*/
		close(fd[READ_END]);
		
		
		FILE *fp;
		char str1[20]="Hello";
		fp=fopen(read_msg1,"a");
		fprintf(fp,"%s",str1);
		fclose(fp);		
		
		close(fd1[READ_END1]);
		write(fd1[WRITE_END1], write_msg, strlen(write_msg)+1);
		close(fd1[WRITE_END1]);
	}
	
	return 0;
}

