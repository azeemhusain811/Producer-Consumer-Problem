#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int *buf,bufPosition=-1,prodCount,consCount,bufLen;
pthread_t *prod,*cons;
sem_t bufMutex,empCount,fillCount;

void *producer()
{
	printf("\nProducer Function Called");	
}

void *consumer()
{
	printf("\nConsumer Function Called");
}

int main()
{
	int i,error;
	sem_init(&bufMutex,0,1);
	sem_init(&fillCount,0,0);
	
	printf("\nEnter number of Producers:");
	scanf("%d",&prodCount);
	prod = (pthread_t*) malloc(prodCount*sizeof(pthread_t));
	
	printf("\nEnter number of Consumers:");
	scanf("%d",&consCount);
	cons = (pthread_t*) malloc(consCount*sizeof(pthread_t));
	
	printf("\nEnter buffer size :");
	scanf("%d",&bufLen);
	buf = (int*) malloc(bufLen*sizeof(int));
	sem_init(&empCount,0,bufLen);
	
	for(i=0;i<prodCount;i++)
	{
		error = pthread_create(prod+i,NULL,&producer,NULL);
		if(error != 0)
		printf("\nError creating producer %d: %s",i+1,strerror(error));
		else
		printf("\nSuccessfully created producer %d",i+1);
	}
	
	for(i=0;i<consCount;i++)
	{
		error = pthread_create(cons+i,NULL,&consumer,NULL);
		if(error != 0)
		printf("\nError, Consumer %d can't be Created : %s",i+1,strerror(error));
		else
		printf("\nSuccessfully created consumer %d",i+1);
	}
	
	for(i=0;i<prodCount;i++)
	pthread_join(*(prod+i),NULL);
	
	for(i=0;i<consCount;i++)
	pthread_join(*(cons+i),NULL);
	
	return 0;
}
