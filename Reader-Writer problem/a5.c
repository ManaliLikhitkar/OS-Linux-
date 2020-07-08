//-----------------------------------------------------------------------------------------------
//				Assignment 5
//	Roll no. : 33346
//	Batch	 : M11
//-----------------------------------------------------------------------------------------------

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex,wrt;
int readcount=0,data=0;

void *reader(void *arg)
{
       do
       {
       
       	  int rno=(int*) arg;
       	  
	  sem_wait(&mutex);
	  
	  readcount = readcount + 1;
	  
	  if(readcount==1)
	   sem_wait(&wrt);
	   
	  sem_post(&mutex);
	  printf("\nReader %d reads Data: %d\n",rno,data);
	  
	  sem_wait(&mutex);
	  
	  readcount = readcount - 1;
	  
	  if(readcount==0)
	   sem_post(&wrt);
	   
	  sem_post(&mutex);
	  sleep(1);
       }while(1);
}



void *writer(void *arg)
{
     do
     {
     	  int wno=(int*) arg;
     
	  sem_wait(&wrt);
	  
	  data++;
	  printf("\nWriter %d writes Data: %d\n",wno,data);
	  
	  sem_post(&wrt);
	  
	  sleep(1);
     }while(1);
}


int main()
{
	  int i,b; 
	  pthread_t reader_tid[5],writer_tid[5];
	  
	  sem_init(&mutex,0,1);
	  sem_init(&wrt,0,1);
	  
	  
	  for(i=0;i<5;i++)
	  {	   
		pthread_create(&writer_tid[i],NULL,writer,(void*)i);
	    	pthread_create(&reader_tid[i],NULL,reader,(void*)i);
	  }	  
	  
	  for(i=0;i<3;i++)
	  {	    
		pthread_join(writer_tid[i],NULL);
	   	pthread_join(reader_tid[i],NULL);
	  }
	  
	  return 0;
}
