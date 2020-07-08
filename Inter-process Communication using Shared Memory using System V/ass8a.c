#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>

int main()
{

	printf("Writer Process\n");
	key_t key=ftok("shmfile",65);

	int shmid=shmget(key,1024,0666|IPC_CREAT);

	char *str=(char*) shmat(shmid,(void*)0,0);

	printf("Write Data :");
	gets(str);
	

	printf("Data Written In Memory -%s\n",str);

	shmdt(str);




	return 0;
}

