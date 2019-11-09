/**
Cade Newell
CPSC 346:02
 */

#include "producer-consumer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1

buffer_item buffer[BUFFER_SIZE];
/*define semaphores and mutex*/
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
    /* Acquire Empty Semaphore */
	sem_wait(&empty);
	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&mutex);
	
    buffer[insertPointer++] = item;
    insertPointer = insertPointer % 7;
    /* Release mutex lock and full semaphore */
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
	
	return 0;
}

int remove_item(buffer_item *item)
{
	/* Acquire Full Semaphore */
	sem_wait(&full);
	/* Acquire mutex lock to protect buffer */
	pthread_mutex_lock(&mutex);

	buffer[insertPointer--] = item;
	insertPointer = insertPointer % 7;
	/* Release mutex lock and empty semaphore */
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	return 0;
}


int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	/*call atoi to get arguments */

 

	/* Create the producer and consumer threads */
 

	for(j = 0; j < consumerThreads; j++)
	{
 

	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	return 0;
}

void *producer(void *param)
{
		 

	while(TRUE)
	{


	}

}

void *consumer(void *param)
{
	 
	 

	while(TRUE)
	{
 

	}
}