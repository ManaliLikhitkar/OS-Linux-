#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main()
{
	printf("Reader Process\n");
	
	key_t key=ftok("shmfile",65);

	int shmid=shmget(key,1024,0666|IPC_CREAT);	

	char *str=(char *)shmat(shmid,(void*)0,0);

	printf("Data Read From Memory-%s\n",str);
	
	shmdt(str);
	
	shmctl(shmid,IPC_RMID,NULL);	

	return 0;
}
