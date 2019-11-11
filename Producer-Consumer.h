 /*
Cade Newell
CPSC 346:02
producer-consumer.h
*/

typedef int buffer_item;
#define BUFFER_SIZE 5

int insert_item(buffer_item item);
int remove_item(buffer_item *item);

void *producer(void *param);
void *consumer(void *param);