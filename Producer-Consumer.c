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
	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);

	/* initializing the locks */
	printf("pthread_mutex_init: %d\n",pthread_mutex_init(&mutex, NULL));
	sem_init(&empty, 0, 1);
	sem_init(&full, 0, 0);
 
	/* Create the producer and consumer threads */

	for(i = 0; i < producerThreads; i++){
		pthread_t tid;
		pthread_attr_t atr;
		pthread_attr_init(&atr);
		pthread_create(&tid, &atr, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++){
		pthread_t tid;
		pthread_attr_t atr;
		pthread_attr_init(&atr);
		pthread_create(&tid, &atr, consumer, NULL);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	return 0;
}

void *producer(void *param)
{
	buffer_item item;
	int i;	 

	while(TRUE)
	{
		i = rand() % 7;
		sleep(i);
		item = rand();

		if (insert_item(item))
			fprintf(stderr, "Error");
		else 
			printf("Producer produced %d \n", item);
	}
}

void *consumer(void *param)
{
	buffer_item item;
	int i;	
	 
	while(TRUE)
	{
		i = rand() % 7;
		sleep(i);
		item = rand();

		if (remove_item(item))
			fprintf(stderr, "Error");
		else 
			printf("Consumer consumed %d \n", item);
 
	}
}