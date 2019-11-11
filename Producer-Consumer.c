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
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

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
	insertPointer = insertPointer % 5;

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

	*item = buffer[removePointer];
	buffer[removePointer++] = -1;
	removePointer = removePointer % 5;

	/* Release mutex lock and empty semaphore */
	pthread_mutex_unlock(&mutex);
    sem_post(&empty);

	return 0;
}

int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	srand(time(0));

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	/*call atoi to get arguments */
    sleepTime = atoi(argv[1]);
    producerThreads = atoi(argv[2]);
    consumerThreads = atoi(argv[3]);
 
	/* Create the producer and consumer threads */
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for(i = 0; i < producerThreads; i++)
	{
        pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++)
	{
        pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, NULL);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	return 0;
}

void *producer(void *param)
{
    buffer_item item;

	while(TRUE)
	{
        sleep(rand() % 5);
        
        item = rand();
        if (insert_item(item))
            fprintf(stderr, "report error condition, Producer");
        else
            printf("producer produced %d\n",item);
	}

}

void *consumer(void *param)
{
	buffer_item item;

	while(TRUE)
	{
        sleep(rand() % 5);

        if (remove_item(&item))
            fprintf(stderr, "report error condition, Consumer");
        else
            printf("consumer consumed %d\n",item);
	}
}