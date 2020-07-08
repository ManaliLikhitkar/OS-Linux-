//-----------------------------------------------------------------------------------------------
//				Assignment 6
//	Roll no. : 33346
//	Batch	 : M11
//-----------------------------------------------------------------------------------------------


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define left (i+total-1)
#define right (i+1)
#define T 0
#define H 1
#define E 2

sem_t mutex;
sem_t s[10];
int state[10];
int ph_num[10];
int total;

void take(int);
void put(int);
void test(int);

void* philosopher(void* num)
{
	while(1)
	{
		int* i=num;
		sleep(1);
		take(*i);
		put(*i);
	}
}

void take(int i)
{
	sem_wait(&mutex);		//locked
	state[i]=H;			//philosopher hungry
	printf("\nPhilosopher %d is hungry\n",i+1);
	test(i);			//chech if he can eat
	sem_post(&mutex);		//unlocked
	sem_wait(&s[i]);		//chopsticks picked
	sleep(1);
}

void put(int i)
{
	sem_wait(&mutex);		//locked
	state[i]=T;			//philosopher thinking
	printf("\nPhilosopher %d is putting down chopsticks %d and %d\n",i+1,(left%total)+1,i+1);
	test(left%total);		//test if left wants to eat
	test(right%total);		//test if right wants to eat
	sem_post(&mutex);		//unlocked
}

void test(int i)
{
	if(state[i]==H && state[left%total]!=E && state[right%total]!=E)	//if needed resources are free
	{
		state[i]=E;
		sleep(2);
		printf("\nPhilosopher %d takes chopsticks  %d and %d\n",i+1,(left%total)+1,i+1);
		sem_post(&s[i]);		
	}
}

int main()
{
	int i;
	pthread_t* tid[10];
	sem_init(&mutex,0,1);

	printf("\nEnter the number of philosophers:");
	scanf("%d",&total);

	for(i=0;i<total;i++)
	{
		tid[i]=(pthread_t*)malloc(sizeof(pthread_t));
		ph_num[i]=i;
		sem_init(&s[i],0,0);
		pthread_create(tid[i],NULL,philosopher,&ph_num[i]);
		printf("\nPhilosopher %d is thinking...",i+1);
	}

	for(i=0;i<total;i++)
	{
		pthread_join(*tid[i],NULL);
	}

	return 0;
}
